/*
 * StreamBuffer.h
 *
 *  Created on: Feb 27, 2013
 *      Author: Adam57
 */

#ifndef STREAMBUFFER_H_
#define STREAMBUFFER_H_
#include <iostream>
#include <cstring>
using namespace std;

class StreamBuffer {
private:
	int buffersize;
	int curpoz;
	char* mybuffer;
	char* curpointer;

public:
	StreamBuffer();
	StreamBuffer(int size);
	virtual ~StreamBuffer();
	int getsize();
	int getcurpoz();
	bool write(const char* buffer, int size);
	void read(char* buffer, int size);
	char* str();
	char* getcontent(int index);
};

#endif /* STREAMBUFFER_H_ */
