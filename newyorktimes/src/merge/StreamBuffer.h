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
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class StreamBuffer {
private:
	int buffersize;
	char* mybuffer;
	int offset;
	string filename;
	int filenum;
	int postingsize;
	bool is_sort;
	int total_offset;

public:
//	int offset;
	StreamBuffer();
	StreamBuffer(int size);
	virtual ~StreamBuffer();
	int getsize();
	bool active();
	bool write(const void* buffer, int size);
	bool read(void* buffer, int size);
	char* getcontent(int index);
	template <class type>
	bool write(const type* buffer);
	template <class type>
	bool read(type* buffer);
	bool savetofile();
	void setfilename(string path);
	bool sort(int recsize, int cursize);
	void setpostingsize(int size);
	void set_sort(bool sort);
	int get_offset();
	int get_filenum();

};

template <class type>
bool StreamBuffer::write(const type* buffer){

	if(buffer==NULL){
		return false;
		cout<<"input buffer void pointer"<<endl;
	}
	if(sizeof(type)>buffersize){
		return false;
		cout<<"buffer too small for input buffer"<<endl;
	}
	if(offset+sizeof(type)>buffersize){
		
		//cout<<"2"<<endl;
			savetofile();
			cout<<"During saving uncompressed int, Buffer size not enough, Auto save file, reset offset"<<endl;
//			delete[] mybuffer;
//			mybuffer = new char[buffersize];
			cout<<"buffersize: "<<buffersize<<endl;
			cout<<"input size: "<<sizeof(type)<<endl;
			cout<<"larger than buffer size, offset: "<<offset<<endl;
			cout<<"total offset: "<<total_offset<<endl;
			offset = 0;
			memcpy(mybuffer+offset, buffer, sizeof(type));
			offset = offset + sizeof(type);
			total_offset = total_offset + sizeof(type);
			cout<<"After saving"<<endl;
			cout<<"offset: "<<offset<<endl;
			cout<<"total offset: "<<total_offset<<endl;
			return true;
		}
	if(offset+sizeof(type)<buffersize){
		//cout<<"1"<<endl;
		//cout<<"offset changing:"<<offset<<" "<<buffersize<<endl;
		memcpy(mybuffer+offset, buffer, sizeof(type));
		offset = offset+sizeof(type);
		total_offset = total_offset + sizeof(type);
		
		return true;
	}
	if(offset+sizeof(type)==buffersize){
		//cout<<"3"<<endl;
		//cout<<"offset changing:"<<offset<<" "<<buffersize<<endl;
		cout<<"During saving uncompressed int, Buffer size just enough, Auto save file, reset offset"<<endl;
				cout<<"buffersize: "<<buffersize<<endl;
			    cout<<"input size: "<<sizeof(type)<<endl;
			    cout<<"equal to buffer size, offset: "<<offset<<endl;
			    cout<<"total offset: "<<total_offset<<endl;
				memcpy(mybuffer+offset, buffer, sizeof(type));
				offset = offset+sizeof(type);
				total_offset = total_offset + sizeof(type);
				savetofile();
//				delete[] mybuffer;
//				mybuffer = new char[buffersize];
				offset = 0;
				cout<<"After saving"<<endl;
			    cout<<"offset: "<<offset<<endl;
			    cout<<"total offset: "<<total_offset<<endl;
				return true;
	}
	return false;
}

template <class type>
bool StreamBuffer::read(type* buffer){
		if(offset>=buffersize)
			return false;
		else
		{
		memcpy(buffer, mybuffer+offset, sizeof(type));
		offset = offset + sizeof(type);
		return true;
		}
}
#endif /* STREAMBUFFER_H_ */


