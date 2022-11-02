#include "CommandQueue.h"
#include "Debug.h"

static ZNLinkedList_t * g_zwpkg_queue = NULL;

bool ZWQPushPackage(ZUNOCommandPacket_t * pkg){
    if(zunoNID() == 0) { // We are out of network - don't send anything
		#ifdef LOGGING_DBG
		LOGGING_UART.print(millis());
		LOGGING_UART.println(" Package was dropped! NodeID==0");
		#endif
		return false;
		
	}
    ZUNOCommandPacket_t * stored_pck;
    stored_pck = (ZUNOCommandPacket_t *)malloc(sizeof(ZUNOCommandPacket_t));
    if (stored_pck == NULL)
        return false;
    memcpy(stored_pck, pkg, sizeof(ZUNOCommandPacket_t));
    // We have to allocated command buffer dynamically too
    // add ZAF offset
    stored_pck->cmd = (uint8_t*)malloc(sizeof(uint8_t)*pkg->len + MAX_ZWTRANSPORT_ENCAP);
    if(stored_pck->cmd == NULL){
        free(stored_pck);
        return false;
    }
    memset(stored_pck->cmd, 0, MAX_ZWTRANSPORT_ENCAP);
    stored_pck->cmd += MAX_ZWTRANSPORT_ENCAP;
    // copy command data from the ZAF offset
    memcpy(stored_pck->cmd , pkg->cmd, pkg->len);
    znllPushBack(&g_zwpkg_queue, (void*)stored_pck);
    return true;
}
bool zunoExtractGroupNode(uint8_t g, uint8_t i, ZUnoAssocNode_t * node){
	 return zunoSysCall(ZUNO_SYSFUNC_ASSOCIATION_NODE, 3, g, i, node) == 0;
}
bool zunoRadioStats(ZUNORadioStat_t * p_radio_stat){
    uint32_t w = (uint32_t)zunoSysCall(ZUNO_SYSFUNC_RADIO_STAT, 1, p_radio_stat);
    return w == 0;
}
bool zunoCheckSystemQueueStatus(uint8_t channel){
    ZUNORadioStat_t s;
    if(zunoRadioStats(&s)){
       return (s.queue_busy_flags & (1 << channel)) != 0;
    }
    if((channel > 0) && (s.pkgs_hp_time < SYSTEM_PKG_DOMINATION_TIME)){
        #ifdef LOGGING_DBG
		LOGGING_UART.print("*** HIGH PRIORITY PKG DOMINATOIN. INTERVAL:");
        LOGGING_UART.println(s.pkgs_hp_time);
        #endif
        return true;
    }
    return false;
}
uint32_t zunoPendingRadioMessages(){
    ZUNORadioStat_t s;
    if(zunoRadioStats(&s)){
        return s.pkgs_queued - s.pkgs_processed;
    }
    return 0;
}
#ifdef LOGGING_UART
void zuno_dbgdumpZWPacakge(ZUNOCommandPacket_t * cmd);
#endif
void _ZWQSend(ZUNOCommandPacket_t * p){

    #ifdef LOGGING_DBG
	LOGGING_UART.print("\n >>> (");
	LOGGING_UART.print(millis());
	LOGGING_UART.print(") OUTGOING PACKAGE: ");
	zuno_dbgdumpZWPacakge(p);
	#endif
    if(p->src_zw_channel & ZWAVE_CHANNEL_MAPPED_BIT){
		p->src_zw_channel = 0;
		zunoSysCall(ZUNO_SYSFUNC_SENDPACKET, 1, p);
		p->src_zw_channel &= ~(ZWAVE_CHANNEL_MAPPED_BIT);
	}
    zunoSysCall(ZUNO_SYSFUNC_SENDPACKET, 1, p); 
}
void _ZWQRemovePkg(ZUNOCommandPacket_t * p){
    // revert back cmd addr
    p->cmd -= MAX_ZWTRANSPORT_ENCAP;
    free(p->cmd);
    free(p);
}
bool ZWQIsEmpty(){
    return (znllCount(g_zwpkg_queue) == 0);
}
void ZWQProcess(){
    ZNLinkedList_t *e;
    ZUnoAssocNode_t node;
    ZUNORadioStat_t s;
    // Walk through the queue
    int qi;
    int processed_indexes[MAX_PROCESSED_QUEUE_PKGS];
    int processed_indexes_cnt = 0;
    ZUNOCommandPacket_t * p;
    // Process the packages
    for(e=g_zwpkg_queue, qi=0;e; e=e->next, qi++){
        p = (ZUNOCommandPacket_t *) e->data;
        zunoRadioStats(&s);
        uint32_t system_queue_count = s.pkgs_queued - s.pkgs_processed;
        if(system_queue_count >= MAX_SYS_QUEUE_PKGS){
            #ifdef LOGGING_DBG
		    LOGGING_UART.print("*** SYSTEM QUEUE IS FULL. CNT:");
            LOGGING_UART.println(system_queue_count);
            #endif
            break;
        }
        uint8_t q_ch = p->flags & ZUNO_PACKETFLAGS_PRIORITY_MASK; 
        // Check if we have a free channel to send the package
        if(zunoCheckSystemQueueStatus(q_ch))
            continue; // Needed queue is full for this priority - just skip the package
        #ifdef LOGGING_DBG
		LOGGING_UART.print("*** QCH:");
        LOGGING_UART.println(q_ch);
        #endif
        if(p->flags & ZUNO_PACKETFLAGS_GROUP){
            #ifdef LOGGING_DBG
		    LOGGING_UART.print(millis());
		    LOGGING_UART.print("*** GROUP:");
            LOGGING_UART.print(p->dst_node);
            LOGGING_UART.print(" I:");
            LOGGING_UART.print(p->dst_zw_channel);
            LOGGING_UART.println(" PKG");
		    #endif
            // Send that packet to group
            // Extract node from association storage
            zunoExtractGroupNode(p->dst_node, p->dst_zw_channel, &node);
            #ifdef LOGGING_DBG
		    LOGGING_UART.print("*** NODE ID:");
            LOGGING_UART.print(node.dest_nodeid);
            LOGGING_UART.print(" channel:");
            LOGGING_UART.println(node.dest_nodeid);
		    #endif
            if(node.dest_nodeid == 0){
                // There is no more data for this group
                processed_indexes[processed_indexes_cnt++] = qi;
                if(processed_indexes_cnt >= MAX_PROCESSED_QUEUE_PKGS)
                    break;
                continue;
            } 
            // Save group attributes
            uint16_t tmp = p->dst_node;
            uint8_t tmp_ch = p->dst_zw_channel;
            uint8_t tmp_flags = p->flags;
            // Copy Node id of specific device
            p->dst_node = node.dest_nodeid;
            p->dst_zw_channel = node.dest_channel;
            p->zw_rx_secure_opts = node.security_level;
            p->flags &= ~(ZUNO_PACKETFLAGS_GROUP);
            // Send package to target device
            _ZWQSend(p);
            // Restore group attributes 
            p->dst_node = tmp;
            p->dst_zw_channel = tmp_ch + 1;
            p->flags = tmp_flags;
        } else {
            _ZWQSend(p);
            processed_indexes[processed_indexes_cnt++] = qi;
            if(processed_indexes_cnt >= MAX_PROCESSED_QUEUE_PKGS)
                break;
            break;
        }
    }
    #ifdef LOGGING_DBG
    if(processed_indexes_cnt){
	    LOGGING_UART.print("*** PROCESSED:");
        LOGGING_UART.println(processed_indexes_cnt);
    }
	#endif
    // Clean queue
    while(processed_indexes_cnt){
        // The backward order, otherwise it will break the indexes
        qi = processed_indexes[processed_indexes_cnt-1];
        #ifdef LOGGING_DBG
	    LOGGING_UART.print("*** CLEANUP:");
        LOGGING_UART.println(qi);
	    #endif
        p = (ZUNOCommandPacket_t *)znllRemove(&g_zwpkg_queue, qi);
        _ZWQRemovePkg(p);
        processed_indexes_cnt--;
    }
}