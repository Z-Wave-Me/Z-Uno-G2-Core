#include "Stream.h"
#include "Arduino.h"

#define PARSE_TIMEOUT 1000
#define NO_SKIP_CHAR 1

int32_t Stream::timedRead(){
	int32_t c;
 	_startMillis = millis();
  	do {
    	c = read();
    	if (c >= 0) return c;
  	} while(millis() - _startMillis < _timeout);
  	return -1;
}

int32_t Stream::timedPeek(){
	int32_t c;
  	_startMillis = millis();
  	do {
    	c = peek();
    	if (c >= 0) return c;
  	} while(millis() - _startMillis < _timeout);
  	return -1;  
}

void Stream::setTimeout(uint32_t timeout){
	_timeout = timeout;
}

bool Stream::find(char *target){
	return findUntil(target, strlen(target), (char*)0, 0);
}

bool Stream::find(char *target, size_t length){
	return findUntil(target, length, (char*)0, 0);
}

bool Stream::findUntil(char *target, char *terminator){
	return findUntil(target, strlen(target), terminator, strlen(terminator));
}

bool Stream::findUntil(char *target, size_t targetLen, char *terminator, size_t termLen){
if (!terminator) {
    MultiTarget t[1] = {{target, targetLen, 0}};
    return findMulti(t, 1) == 0 ? true : false;
  } else {
    MultiTarget t[2] = {{target, targetLen, 0}, {terminator, termLen, 0}};
    return findMulti(t, 2) == 0 ? true : false;
  }
}

int32_t Stream::parseInt(){
	return parseInt(NO_SKIP_CHAR);
}

int32_t Stream::parseInt(char skipChar){
	bool isNegative = false;
	long value = 0;
	int c;

	c = peekNextDigit();
	if(c < 0)
		return 0; 

	do{
		if(c == skipChar)
			; 
		else if(c == '-')
		  isNegative = true;
		else if(c >= '0' && c <= '9')        // is c a digit?
		  value = value * 10 + c - '0';
		read();  // consume the character we got with peek
		c = timedPeek();
	}
	while( (c >= '0' && c <= '9') || c == skipChar );

	if(isNegative)
		value = -value;
	return value;
}

float Stream::parseFloat(){
	return parseFloat(NO_SKIP_CHAR);
}

float Stream::parseFloat(char skipChar){
	bool isNegative = false;
    bool isFraction = false;
    int32_t value = 0;
    char c;
    float fraction = 1.0;

    c = peekNextDigit();
  
    // ignore non numeric leading characters
    if(c < 0)
      return 0; // zero returned if timeout

    do{
    	if(c == skipChar)
          ; // ignore
    	else if(c == '-')
        	isNegative = true;
    	else if (c == '.')
    		isFraction = true;
		else if(c >= '0' && c <= '9')  {      // is c a digit?
    		value = value * 10 + c - '0';
        	if(isFraction)
        		fraction *= 0.1;
    }
    read();  // consume the character we got with peek
    c = timedPeek();
  	}
  	while( (c >= '0' && c <= '9')  || c == '.' || c == skipChar );

  	if(isNegative)
    	value = -value;
  	if(isFraction)
    	return value * fraction;
    return value;	
}

size_t Stream::readBytes(char *buffer, size_t length){
	size_t count = 0;
	while (count < length) {
		uint8_t c = timedRead();
		if (c < 0) break;
		*buffer++ = (char)c;
		count++;
	}
	return count;
}

size_t Stream::readBytesUntil(char terminator, char *buffer, size_t length){
	if (length < 1) return 0;
	size_t index = 0;
	while (index < length) {
		uint8_t c = timedRead();
		if (c < 0 || c == terminator) break;
		*buffer++ = (char)c;
		index++;
	}
	return index; 
}

int32_t Stream::findMulti(struct MultiTarget *targets, int32_t tCount){
	for (struct MultiTarget *t = targets; t < targets+tCount; ++t) {
    	if (t->len <= 0)
      		return t - targets;
  }

 	while (1) {
    	int32_t c = timedRead();
    	if (c < 0)
      		return -1;

    	for (struct MultiTarget *t = targets; t < targets+tCount; ++t) {
      		if (c == t->str[t->index]) {
        		if (++t->index == t->len)
          			return t - targets;
        		else
          			continue;
      		}

      // if not we need to walk back and see if we could have matched further
      // down the stream (ie '1112' doesn't match the first position in '11112'
      // but it will match the second position so we can't just reset the current
      // index to 0 when we find a mismatch.
	      	if (t->index == 0)
	        	continue;

	      	int origIndex = t->index;
	      	do {
	        	--t->index;
	        	// first check if current char works against the new current index
	        	if (c != t->str[t->index])
	          		continue;

	        // if it's the only char then we're good, nothing more to check
	        	if (t->index == 0) {
	          		t->index++;
	          		break;
	        	}

	        // otherwise we need to check the rest of the found string
	        	int diff = origIndex - t->index;
	        	size_t i;
	        	for (i = 0; i < t->index; ++i) {
	          		if (t->str[i] != t->str[i + diff])
	            		break;
	        	}

	        // if we successfully got through the previous loop then our current
	        // index is good.
	        	if (i == t->index) {
	          		t->index++;
	          		break;
	        	}

	        // otherwise we just try the next index
	      		} while (t->index);
	    	}
  	}
  // unreachable
  return -1;	
}