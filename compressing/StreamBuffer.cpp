/*
 * StreamBuffer.cpp
 *
 *  Created on: Feb 27, 2013
 *      Author: Adam57
 */

#include "StreamBuffer.h"

int intCompare(const void *r1, const void *r2)
{
	if (*(int *)r1 > *(int *)r2)
		return(1);
	if (*(int *)r1 < *(int *)r2)
		return(-1);
	if (*(int *)r1 == *(int *)r2){
		if(*(int *)((int *)r1+1) > *(int *)((int *)r2+1))
			return (1);
		if(*(int *)((int *)r1+1) < *(int *)((int *)r2+1))
			return (-1);
	}
	if(*(int *)((int *)r1+1) == *(int *)((int *)r2+1)){
		if(*(int *)((int *)r1+2) > *(int *)((int *)r2+2))
			return (1);
		if(*(int *)((int *)r1+2) < *(int *)((int *)r2+2))
			return (-1);
	}
	return(0);
}
StreamBuffer::StreamBuffer() {
	// TODO Auto-generated constructor stub
	buffersize = 0;
	mybuffer = new char[buffersize];
	offset	  = 0;
	filename 	= "data";
	filenum		= 0;
	postingsize		= 12;
	is_sort		= false;
}

StreamBuffer::StreamBuffer(int size) {
	// TODO Auto-generated constructor stub
	buffersize = size;
	mybuffer = new char[buffersize];
	offset		= 0;
	filename	="data";
	filenum		= 0;
	postingsize		= 12;
	is_sort		= false;
}

StreamBuffer::~StreamBuffer() {
	// TODO Auto-generated destructor stub
	if (mybuffer!=NULL)
		delete[] mybuffer;
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
void StreamBuffer::set_sort(bool sort)
{
	is_sort = sort;
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
			//cout<<"2"<<endl;
		cout<<"Auto save file, reset offset"<<endl;
	
			savetofile();
//			delete[] mybuffer;
//			mybuffer = new char[buffersize];
			cout<<"Auto save file, reset offset"<<endl;
			offset = 0;
			memcpy(mybuffer+offset, buffer, size);
			offset = offset + size;

			

			return true;
		}
	if(offset+size<buffersize){
		//cout<<"1"<<endl;
		//cout<<"offset changing:"<<offset<<" "<<buffersize<<endl;
		memcpy(mybuffer+offset, buffer, size);
		offset = offset+size;
		return true;
	}
	if(offset+size==buffersize){
		//cout<<"3"<<endl;
		//cout<<"offset changing:"<<offset<<" "<<buffersize<<endl;
		memcpy(mybuffer+offset, buffer, size);
		offset = offset+size;
		savetofile();
//		delete[] mybuffer;
//		mybuffer = new char[buffersize];
		
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
	if(is_sort==true)
		sort(postingsize, offset);
	/*
	for (int i=0; i<32;i+=4){
		int tmp=0;
		memcpy(&tmp,mybuffer+i,4);
    	printf("%x",tmp);
    	cout<<endl;
		}
		int i ;
		cin>>i;
	*/

	file.write(mybuffer,offset);
	file.close();
	filenum++;
	}
	catch(char *str){
		cout<<str<<endl;
		return false;
	}
	return true;
}

void StreamBuffer::setfilename(string path){
	filename = path;
}

bool StreamBuffer::sort(int recsize, int cursize){
	cout<<"sorting now..."<<endl;
	qsort(mybuffer, cursize/recsize , recsize ,intCompare);
	return true;

}

void StreamBuffer::setpostingsize(int size){
	postingsize = size;
}

int StreamBuffer::get_offset(){
	return offset;
}

int StreamBuffer::get_filenum(){
	return filenum;
}
