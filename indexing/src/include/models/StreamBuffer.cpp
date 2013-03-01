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
	offset	  = 0;
}

StreamBuffer::StreamBuffer(int size) {
	// TODO Auto-generated constructor stub
	buffersize = size;
	mybuffer = new char[buffersize];
	offset		= 0;
}

StreamBuffer::~StreamBuffer() {
	// TODO Auto-generated destructor stub
	if (mybuffer!=NULL)
		delete mybuffer;
}

int StreamBuffer::getsize(){
	return buffersize;
}

bool StreamBuffer::active(){
	if(offset<buffersize)
//	if(offset<28)
		return true;
	else
		return false;
}

bool StreamBuffer::read(void* buffer, int size){
		if(offset>=buffersize)
			return false;
		else
		{
		memcpy(buffer, mybuffer+offset, size);
		offset = offset + size;
		return true;
		}
}

bool StreamBuffer::write(const void* buffer, int size){
	if(buffer==NULL)
		return false;
	if(offset>=buffersize){
			cout<<"buffer is dumped, no more using"<<endl;
			return false;
		}
	if(offset+size<buffersize){
		cout<<"offset changing:"<<offset<<" "<<buffersize<<endl;
		memcpy(mybuffer+offset, buffer, size);
		offset = offset+size;
		return true;
	}
	else if(offset+size==buffersize){
		cout<<"offset changing:"<<offset<<" "<<buffersize<<endl;
		memcpy(mybuffer+offset, buffer, size);
		offset = offset+size;
		savetofile();
		return true;
	}
	else{
		savetofile();
		cout<<"save to file:"<<offset<<endl;
		offset = buffersize;
		return false;
	}
}


char* StreamBuffer::getcontent(int index){
	 return mybuffer+index;
}

bool StreamBuffer::savetofile(){
	try{
	ofstream file ("data.bin", ios::out | ios::binary);
	file.write(mybuffer,offset);
	file.close();
	return true;
	}
	catch(char *str){
		cout<<str<<endl;
		return false;
	}
}

