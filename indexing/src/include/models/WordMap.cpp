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


void WordMap::deserialize( StreamBuffer &stream )
{
	map.clear();
	/*
	 		while(stream.active()){
				int key;
	            stream.read(&key);
	            int length;
	            stream.read(&length);
	            char buffer[length+1];
	            buffer[length]='\0';
	            stream.read(buffer,length);
	            string buf(buffer);
	            map.insert(pair<int,string>(key,buf));
	            
	 }*/
}

StreamBuffer& operator<<(StreamBuffer &stream, WordMap &map){
	map.deserialize(stream);
	return stream;
}

StreamBuffer& operator>>(StreamBuffer &stream, WordMap &map) {
    map.serialize(stream);
    return stream;
}



