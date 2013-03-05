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
	filename 	= "data";
	filenum		= 0;
}

StreamBuffer::StreamBuffer(int size) {
	// TODO Auto-generated constructor stub
	buffersize = size;
	mybuffer = new char[buffersize];
	offset		= 0;
	filename	="data";
	filenum		= 0;
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
	if(buffer==NULL){
		return false;
		cout<<"input buffer void pointer"<<endl;
	}
	if(size>buffersize){
		return false;
		cout<<"buffer too small for input buffer"<<endl;
	}
	if(offset+size>buffersize){
			cout<<"2"<<endl;
			savetofile();
			cout<<"Auto save file, open a new buffer"<<endl;
			delete mybuffer;
			mybuffer = new char[buffersize];
			offset = 0;
			memcpy(mybuffer+offset, buffer, size);
			offset = offset + size;
			return true;
		}
	if(offset+size<buffersize){
		cout<<"1"<<endl;
		cout<<"offset changing:"<<offset<<" "<<buffersize<<endl;
		memcpy(mybuffer+offset, buffer, size);
		offset = offset+size;
		return true;
	}
	if(offset+size==buffersize){
		cout<<"3"<<endl;
		cout<<"offset changing:"<<offset<<" "<<buffersize<<endl;
		memcpy(mybuffer+offset, buffer, size);
		offset = offset+size;
		savetofile();
		delete mybuffer;
		mybuffer = new char[buffersize];
		offset = 0;
		return true;
	}
	return false;
}


char* StreamBuffer::getcontent(int index){
	 return mybuffer+index;
}

bool StreamBuffer::savetofile(){
	try{
	char tmpname[100];
	sprintf(tmpname, "%s%d", filename.c_str(), filenum);
	cout<<"filename: "<<tmpname<<endl;
	ofstream file (tmpname, ios::out | ios::binary);
	file.write(mybuffer,offset);
	file.close();
	filenum++;
	return true;
	}
	catch(char *str){
		cout<<str<<endl;
		return false;
	}
}

void StreamBuffer::setfilename(string path){
	filename = path;
}

