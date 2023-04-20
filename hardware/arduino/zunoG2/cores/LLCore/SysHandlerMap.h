#ifndef SYS_HANDLER_MAP_H
#define SYS_HANDLER_MAP_H
bool zunoAttachSysHandler(byte type, byte sub_type, void *handler);
bool zunoDetachSysHandler(byte type, byte sub_type, void *handler);
bool zunoDetachSysHandlerAllSubType(byte type, byte sub_type);
void * zunoSysHandlerCall(uint8_t type, uint8_t sub_type, ...);
#endif // SYS_HANDLER_MAP_H