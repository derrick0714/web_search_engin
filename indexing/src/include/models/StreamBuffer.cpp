/*
 * StreamBuffer.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Adam57
 */

#include "StreamBuffer.h"

StreamBuffer::StreamBuffer() {
	// TODO Auto-generated constructor stub
	buffersize = 0;
	mybuffer = new char[buffersize];
	curpoz   = 0;
	curpointer		= mybuffer;
}

StreamBuffer::StreamBuffer(int size) {
	// TODO Auto-generated constructor stub
	buffersize = size;
	mybuffer = new char[buffersize];
	curpointer = mybuffer;
	curpoz 	= 0;
	cout <<"init"<<endl;
	cout << static_cast<const void *>(mybuffer) << endl;
	cout << static_cast<const void *>(curpointer) << endl;
	cout <<"---"<<endl;
}

StreamBuffer::~StreamBuffer() {
	// TODO Auto-generated destructor stub
	if (mybuffer!=NULL)
		delete mybuffer;
}

int StreamBuffer::getsize(){
	return buffersize;
}

int StreamBuffer::getcurpoz(){
	return curpoz;
}

bool StreamBuffer::write(const char* buffer, int size){
	if(buffer!=NULL){
		memcpy(curpointer, buffer, size);
		curpoz=curpoz+size;
		curpointer = curpointer + size;
		cout <<"write"<<endl;
		cout << static_cast<const void *>(mybuffer) << endl;
		cout << static_cast<const void *>(curpointer) << endl;
		cout <<"---"<<endl;
		return true;
	}
	else
		return false;
}

void StreamBuffer::read(char* buffer, int size){
		memcpy(buffer, mybuffer, size);
}

char* StreamBuffer::str(){
	 return mybuffer;
}

char* StreamBuffer::getcontent(int index){
	 return mybuffer+index;
}
