#ifndef _ZUNO_STREAM_H
#define _ZUNO_STREAM_H
#include "Print.h"


struct MultiTarget {
	char *str;
	size_t len;
	size_t index;
};


class Stream : public Print
{

public:
	Stream() {_timeout = 1000;}

protected:
	uint32_t _timeout;
	uint32_t _startMillis;
	int32_t timedRead();
	int32_t timedPeek();
	int32_t peekNextDigit();
	int32_t parseInt(char skipChar);
	float parseFloat(char skipChar);
	int32_t findMulti(struct MultiTarget *targets, int32_t tCount);


public:

	virtual size_t available() {return 0; };
	virtual int read() {return 0; };
	virtual	int peek() {return 0; };
	//virtual void flush () {};
	
	void setTimeout(uint32_t timeout);
	bool find(char *target);
    bool find(uint8_t *target) { return find ((char *)target); }
	bool find(char * target, size_t length);
	bool find(uint8_t *target, size_t length) { return find ((char*)target, length) ;}
	bool find(char target) { return find(&target, 1);}
	bool findUntil(char *target, char *terminator);
 	bool findUntil(uint8_t *target, char *terminator) { return findUntil((char *)target, terminator); }
 	bool findUntil(char *target, size_t targetLen, char *terminate, size_t termLen);
 	int32_t parseInt();
 	float parseFloat();
 	size_t readBytes( char *buffer, size_t length); 
  	size_t readBytes( uint8_t *buffer, size_t length) { return readBytes((char *)buffer, length); }
  	size_t readBytesUntil( char terminator, char *buffer, size_t length);
  	size_t readBytesUntil( char terminator, uint8_t *buffer, size_t length) { return readBytesUntil(terminator, (char *)buffer, length); }


};
#endif //_ZUNO_STREAM_H
