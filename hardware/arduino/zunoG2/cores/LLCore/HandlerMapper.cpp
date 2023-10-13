#include "HandlerMapper.h"

bool zunoAttachSysHandler(byte type, byte sub_type, void *handler);
bool zunoDetachSysHandler(byte type, byte sub_type, void *handler);

ZMEHandlerMapper::ZMEHandlerMapper(uint32_t event_map){
    _event_map = event_map;
    zunoAttachSysHandler(ZUNO_HANDLER_OBJ_MAPPER, 0xFF, (void*)this);
}
ZMEHandlerMapper::~ZMEHandlerMapper(){
    zunoDetachSysHandler(ZUNO_HANDLER_OBJ_MAPPER, 0xFF, (void*)this);
}