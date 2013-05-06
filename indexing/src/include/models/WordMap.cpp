/*
 * WordMap.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#include "WordMap.h"

WordMap::WordMap() {
	// TODO Auto-generated constructor stub

}

WordMap::~WordMap() {
	// TODO Auto-generated destructor stub
}

bool WordMap::isHas(string key)
{
	return map.find(key) != map.end();
}

void WordMap::serialize( StreamBuffer &stream )
{
	for ( std::map<string, int>::iterator it = map.begin(); it!=map.end(); ++it)
	{
			int tmp = it->first.length();
			stream.write(&tmp);
			stream.write(it->first.c_str(), it->first.length());
			stream.write(&it->second);
	}
				
}


void WordMap::deserialize( char* buffer, int size )
{
	map.clear();
	//cout<<"buffer:"<<buffer<<"size:"<<size<<endl;
	int offset = 0;
	char key[1000];

	while(offset < size)
	{
		int len;
		memcpy(&len, buffer+offset, sizeof(int));
		offset += sizeof(int);

	    
	    key[len]='\0';
	 	memcpy(key, buffer+offset, len);
	    offset+= len;

	    int val;
	    memcpy(&val, buffer+offset, sizeof(int));
	    offset += sizeof(int);
	    

    	map[key]=val;

    	//cout<<"word:"<<key<<"=>id:"<<val<<endl;
   // 	cout<<"url:"<<key<<" doc_id:"<<val.doc_id<<" file_id:"<<val.file_id<<" offset:"<<val.offset<<" len:"<<val.len<<endl;	            
	 }
}



StreamBuffer& operator>>(StreamBuffer &stream, WordMap &map) {
    map.serialize(stream);
    return stream;
}



