#include "CommandQueue.h"
#include "Debug.h"

static ZNLinkedList_t * g_zwpkg_queue = NULL;
static uint32_t last_controller_package_time = 0;
#ifdef LOGGING_UART
void zuno_dbgdumpZWPacakge(const ZUNOCommandCmd_t * cmd);
#endif

void ZWQIncomingStat(const ZUNOCommandCmd_t * pkg){
    if(pkg->src_node == 1){
        last_controller_package_time = millis();
    }
}

static bool _ZWQProcessChecking(ZUNOCommandPacket_t *info);

bool ZWQPushPacket(ZUNOCommandPacket_t * pkg){
    if((pkg->packet.flags & ZUNO_PACKETFLAGS_TEST) == 0) { // Sometimes we need a test pakage that ignores this restriction
        if(zunoNID() == 0) { // We are out of network - don't send anything
            #ifdef LOGGING_DBG
            LOGGING_UART.print(millis());
            LOGGING_UART.println(" Packet was dropped! NodeID==0");
            #endif
            return false;
        }
        if (_ZWQProcessChecking(pkg) == false)
        {
            #ifdef LOGGING_DBG
            LOGGING_UART.print(millis());
            LOGGING_UART.print(" Packet was dropped!\n");
            #endif
            return false;
        }
    }
    ZUNOCommandPacket_t * stored_pck;
    stored_pck = (ZUNOCommandPacket_t *)malloc(sizeof(ZUNOCommandPacket_t));
    if (stored_pck == NULL){
        #ifdef LOGGING_DBG
		LOGGING_UART.print(millis());
		LOGGING_UART.println(" Enqueue: Memory OVF1");
		#endif
        return false;
    }
    memcpy(stored_pck, pkg, sizeof(ZUNOCommandPacket_t));
    // We have to allocated command buffer dynamically too
    // add ZAF offset
    stored_pck->packet.cmd = (uint8_t*)malloc(sizeof(uint8_t)*pkg->packet.len + MAX_ZWTRANSPORT_ENCAP);
    if(stored_pck->packet.cmd == NULL){
        free(stored_pck);
        #ifdef LOGGING_DBG
		LOGGING_UART.print(millis());
		LOGGING_UART.println(" Enqueue: Memory OVF2");
		#endif
        return false;
    }
    memset(stored_pck->packet.cmd, 0, MAX_ZWTRANSPORT_ENCAP);
    stored_pck->packet.cmd += MAX_ZWTRANSPORT_ENCAP;
    // copy command data from the ZAF offset
    memcpy(stored_pck->packet.cmd , pkg->packet.cmd, pkg->packet.len);
    znllPushBack(&g_zwpkg_queue, (void*)stored_pck);
    #ifdef LOGGING_DBG
	LOGGING_UART.print("\n >>> (");
	LOGGING_UART.print(millis());
	LOGGING_UART.print(") ENQUEUED PACKAGE: ");
	zuno_dbgdumpZWPacakge(&pkg->packet);
	#endif
    return true;
}
ZUNOCommandPacket_t * ZWQFindPackage(uint8_t dst_id, uint8_t flags, uint8_t cc, uint8_t cmd){
    ZNLinkedList_t *e;
    ZUNOCommandPacket_t * p;

    zunoEnterCritical();
    for(e=g_zwpkg_queue;e; e=e->next){
        p = (ZUNOCommandPacket_t *) e->data;
        if((flags != 0xFF) && ((p->packet.flags & flags)  !=  flags))
            continue;
        if((dst_id != 0xFF) && (p->packet.dst_node != dst_id))
            continue;
        if((cc != 0xFF) && (p->packet.cmd[0]!= cc))
            continue;
        if((cmd != 0xFF) && (p->packet.cmd[1]!= cmd))
            continue;
        zunoExitCritical();
        return p;
    }
    zunoExitCritical();
    return NULL;
}
bool zunoExtractGroupNode(uint8_t g, uint8_t i, ZUnoAssocNode_t * node){
	 return zunoSysCall(ZUNO_SYSFUNC_ASSOCIATION_NODE, 3, g, i, node) == 0;
}
bool zunoCheckSystemQueueStatus(uint8_t channel){
    static uint8_t count_n = 0;
    (void)count_n;
    uint32_t interval = millis() - g_zuno_sys->rstat_pkgs_hp_time;
    if((channel > 0) && (interval < SYSTEM_PKG_DOMINATION_TIME)){
        // #ifdef LOGGING_DBG
		// LOGGING_UART.print("*** HIGH PRIORITY PKG DOMINATION. INTERVAL:");
        // LOGGING_UART.println(interval);
        // #endif
        return true;
    }
    bool  b_busy = (g_zuno_sys->rstat_priority_counts[channel] > 0);
    #ifdef LOGGING_DBG
    if((b_busy) && ((count_n & 0x3F) == 0)){
	    LOGGING_UART.print("*** QUEUE CHANNEL is BUSY:");
        LOGGING_UART.println(channel);
        count_n ++;
    }
    #endif
    return b_busy;
}

static bool _ZWQSend_test(ZUNOCommandPacket_t *info, ZUNOCommandCmd_t *p, bool multi) {
	if (info->report.valid == false)
		return (true);
	if (info->report.option.supervision == false)
		return (true);
	if (info->report.option.src_node != p->dst_node)
		return (true);
	if (info->report.option.cmd_class != p->cmd[0x0])
		return (true);
	if (info->report.option.multi != multi)
		return (true);
	return (false);
}

static bool _ZWQSend_test_only_outside(ZUNOCommandPacket_t *info) {
	if (ZUNO_CFG_CHANNEL_COUNT == 0x1)
		return (true);
	if (info->report.valid == false)
		return (false);
	if (info->report.outside == true)
		return (true);
	return (false);
}

static bool _ZWQSend_outside(ZUNOCommandPacket_t *info, ZUNOCommandCmd_t *p, bool b_test) {
	if (_ZWQSend_test(info, p, false) == false)
		return (false);
	if (b_test == true)
		return (true);
	uint8_t mapped_channel = p->src_zw_channel;
	p->src_zw_channel = 0;
	zunoSysCall(ZUNO_SYSFUNC_SENDPACKET, 1, p);
	p->src_zw_channel = mapped_channel;
	#if defined(WITH_CC_BATTERY) || defined(WITH_CC_WAKEUP)
	zunoSleepUpdateSendRadioCmd();
	#endif
	return (true);
}

static bool _ZWQSend(ZUNOCommandPacket_t *info, bool b_test){
	ZUNOCommandCmd_t *p;

	p = &info->packet;
	#ifdef LOGGING_DBG
	if (b_test == false)
	{
		LOGGING_UART.print("\n >>> (");
		LOGGING_UART.print(millis());
		LOGGING_UART.print(") OUTGOING PACKET: ");
		zuno_dbgdumpZWPacakge(p);
	}
	#endif
    bool b_plain_assoc = (p->dst_zw_channel == PLAIN_ASSOC_MAP); // It's a plain associtaion 
    p->dst_zw_channel &= ~(PLAIN_ASSOC_MAP); // Remove plain assoc value
	if (_ZWQSend_test_only_outside(info) == true) {
		return (_ZWQSend_outside(info, p, b_test));
	}
    if(p->src_zw_channel & ZWAVE_CHANNEL_MAPPED_BIT){
		if (_ZWQSend_test(info, p, false) == true)
			if (_ZWQSend_outside(info, p, b_test) == true && b_test == true)
				return (true);
	}
	if(b_plain_assoc &&  ((p->dst_zw_channel != 0) || (p->src_zw_channel  != 0)))
		return (false); // do not send association with multichannel encap to plain group
	if (_ZWQSend_test(info, p, true) == false)
		return (false);
	if (b_test == true)
		return (true);
	zunoSysCall(ZUNO_SYSFUNC_SENDPACKET, 1, p);
	#if defined(WITH_CC_BATTERY) || defined(WITH_CC_WAKEUP)
	zunoSleepUpdateSendRadioCmd();
	#endif
	return (true);
}
void _ZWQRemovePkg(ZUNOCommandPacket_t *info){
	ZUNOCommandCmd_t							*p;

	p = &info->packet;
    // revert back cmd addr
    p->cmd -= MAX_ZWTRANSPORT_ENCAP;
    free(p->cmd);
    free(info);
}
bool ZWQIsEmpty(){
    return (znllCount(g_zwpkg_queue) == 0);
}

#if ZUNO_PACKETFLAGS_PRIORITY_MASK > 0xFF
#error "ZUNO_PACKETFLAGS_PRIORITY_MASK size!!!"
#endif

typedef struct ZWQProcessContext_s
{
	int processed_indexes[MAX_PROCESSED_QUEUE_PKTS];
	int processed_indexes_cnt;
	int qi;
	bool test;
	ZUnoAssocNode_t node;
} ZWQProcessContext_t;

static bool _ZWQProcess_sub(ZUNOCommandPacket_t *info, ZUNOCommandCmd_t *p, ZWQProcessContext_t *context_process) {
	bool b_send;

	b_send = false;
	if(p->flags & ZUNO_PACKETFLAGS_GROUP){
		while (true) {
			if(context_process->processed_indexes_cnt >= MAX_PROCESSED_QUEUE_PKTS)
				break;
			// Send that packet to group
			// Extract node from association storage
			zunoExtractGroupNode(p->dst_node, p->dst_zw_channel, &context_process->node);
			if(context_process->node.dest_nodeid == 0){
				p->dst_zw_channel++;
				if (p->dst_zw_channel < ZUNO_MAX_ASSOC_LIFE_LINE)
					continue ;
				// There is no more data for this group
				context_process->processed_indexes[context_process->processed_indexes_cnt++] = context_process->qi;
				break ;
			} 
			#ifdef LOGGING_DBG
			if (context_process->test == false)
			{
				LOGGING_UART.print(millis());
				LOGGING_UART.print("*** GROUP:");
				LOGGING_UART.print(p->dst_node);
				LOGGING_UART.print(" I:");
				LOGGING_UART.print(p->dst_zw_channel);
				LOGGING_UART.println(" PKG");
				LOGGING_UART.print("*** NODE ID:");
				LOGGING_UART.print(context_process->node.dest_nodeid);
				LOGGING_UART.print(" channel:");
				LOGGING_UART.println(context_process->node.dest_channel);
			}
			#endif
			// Save group attributes
			uint16_t tmp = p->dst_node;
			uint8_t tmp_ch = p->dst_zw_channel;
			uint8_t tmp_flags = p->flags;
			uint8_t tmp_zw_rx_secure_opts = p->zw_rx_secure_opts;
			// Copy Node id of specific device
			p->dst_node = context_process->node.dest_nodeid;
			p->dst_zw_channel = context_process->node.dest_channel;
			p->zw_rx_secure_opts = context_process->node.security_level;
			p->flags &= ~(ZUNO_PACKETFLAGS_GROUP);
			// Send package to target device
			if (_ZWQSend(info, context_process->test) == true)
				b_send = true;
			// Restore group attributes 
			p->dst_node = tmp;
			p->dst_zw_channel = tmp_ch + 1;
			p->flags = tmp_flags;
			p->zw_rx_secure_opts = tmp_zw_rx_secure_opts;
		}
	} else {
		if (_ZWQSend(info, context_process->test) == true)
			b_send = true;
		context_process->processed_indexes[context_process->processed_indexes_cnt++] = context_process->qi;
	}
	return (b_send);
}

static bool _ZWQProcessChecking(ZUNOCommandPacket_t *info) {
    ZUNOCommandCmd_t * p;
    ZWQProcessContext_t context_process;
    uint8_t dst_zw_channel;
    bool out;

    context_process.qi = 0;
    context_process.processed_indexes_cnt = 0;
    context_process.test = true;
    p = &info->packet;
    dst_zw_channel = p->dst_zw_channel;
    out = _ZWQProcess_sub(info, p, &context_process);
    p->dst_zw_channel = dst_zw_channel;
    return (out);
}

void ZWQProcess(){
    ZWQProcessContext_t context_process;
    ZNLinkedList_t *e;
    ZUNOCommandCmd_t * p;
    ZUNOCommandPacket_t *info;
    static uint32_t count_n = 0;
    uint8_t queue_bit_mask;
    
    // Walk through the queue
    context_process.qi = 0;
    context_process.processed_indexes_cnt = 0;
    context_process.test = false;
    // Process the packages
    int queue_sz = znllCount(g_zwpkg_queue);
    #ifdef LOGGING_DBG
    if((queue_sz > 0) && ((count_n & 0x3F) == 0)){
	    LOGGING_UART.print("CommandQueue Size:");
        LOGGING_UART.println(queue_sz);
    }
    #endif
    queue_bit_mask = 0x0;
    for(e=g_zwpkg_queue, context_process.qi=0; e!= NULL && context_process.qi < queue_sz; e=e->next, context_process.qi++){
        info = (ZUNOCommandPacket_t *) e->data;
        p = &info->packet;
        #ifdef SYQUEUE_CNT_BARRIER
        uint32_t system_queue_count = g_zuno_sys->rstat_pkgs_queued - g_zuno_sys->rstat_pkgs_processed; //s.pkgs_queued - s.pkgs_processed;
        if(system_queue_count >= MAX_SYS_QUEUE_PKTS){
            #ifdef LOGGING_DBG
		    LOGGING_UART.print("*** SYSTEM QUEUE IS FULL. CNT:");
            LOGGING_UART.println(system_queue_count);
            LOGGING_UART.print("  QUEUED:");
            LOGGING_UART.print(g_zuno_sys->rstat_pkgs_queued);
            LOGGING_UART.print("  PROCESSED:");
            LOGGING_UART.println(g_zuno_sys->rstat_pkgs_processed);
            #endif
            break;
        }
        #endif // SYQUEUE_CNT_BARRIER
        uint8_t q_ch = p->flags & ZUNO_PACKETFLAGS_PRIORITY_MASK; 
        // #ifdef LOGGING_DBG
		// LOGGING_UART.print("*** QCH:");
        // LOGGING_UART.println(q_ch);
        // #endif

        if ((queue_bit_mask & (0x1 << (q_ch))) != 0x0) {
        //    #ifdef LOGGING_DBG
        //    LOGGING_UART.print("Skip queue: ");
        //    LOGGING_UART.println(q_ch);
        //    #endif
           continue ;
        }
        if(((millis() - last_controller_package_time) < CONTROLLER_INTERVIEW_REQUEST_INTERVAL) && 
           ( q_ch !=  0) &&
           (zunoSecurityStatus() == SECURITY_KEY_S0)){
               #ifdef LOGGING_DBG
                LOGGING_UART.print("Waiting for controller.  QCH:");
                LOGGING_UART.println(q_ch);
                #endif
                queue_bit_mask = queue_bit_mask | (0x1 << (q_ch));
                continue; // Skip report packets during interview
           }

        // Check if we have a free channel to send the package
        if(info->report.fast == false && zunoCheckSystemQueueStatus(q_ch)) {
            queue_bit_mask = queue_bit_mask | (0x1 << (q_ch));
            continue; // Needed queue is full for this priority - just skip the package
        }
        _ZWQProcess_sub(info, p, &context_process);
        if(context_process.processed_indexes_cnt >= MAX_PROCESSED_QUEUE_PKTS)
            break;
    }
    #ifdef LOGGING_DBG
    if(context_process.processed_indexes_cnt){
	    LOGGING_UART.print("*** PROCESSED:");
        LOGGING_UART.println(context_process.processed_indexes_cnt);
    }
	#endif
    // Clean queue
    while(context_process.processed_indexes_cnt){
        // The backward order, otherwise it will break the indexes
        context_process.qi = context_process.processed_indexes[context_process.processed_indexes_cnt-1];
        #ifdef LOGGING_DBG
	    LOGGING_UART.print("*** CLEANUP:");
        LOGGING_UART.println(context_process.qi);
	    #endif
        info = (ZUNOCommandPacket_t *)znllRemove(&g_zwpkg_queue, context_process.qi);
        _ZWQRemovePkg(info);
        context_process.processed_indexes_cnt--;
    }
    count_n++;
}