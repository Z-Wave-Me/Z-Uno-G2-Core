#ifndef ZUNO_TIME_H
#define ZUNO_TIME_H

time_t zunoGetTimeStamp(void);
bool zunoIsValidDate(void);
void zunoSetTimeStamp(time_t timeUnix);

void delay(dword ms);
dword millis(void);
dword micros(void);
void delayMicroseconds(dword tdelay);
inline void yield() { delay(1); }

#endif//ZUNO_TIME_H