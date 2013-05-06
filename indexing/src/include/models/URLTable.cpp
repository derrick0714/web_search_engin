/*
 * URLTable.cpp
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#include "URLTable.h"

URLTable::URLTable() {
	// TODO Auto-generated constructor stub

}

URLTable::~URLTable() {
	// TODO Auto-generated destructor stub
}

void URLTable::serialize(  StreamBuffer &stream ) {
	for ( std::map<int, string>::iterator it = map.begin(); it!=map.end(); ++it){

			stream.write(&it->first);
			int tmp = it->second.length();
			stream.write(&tmp);
			stream.write(it->second.c_str(), it->second.length());
	}

}

void URLTable::deserialize( StreamBuffer &stream  ){
	map.clear();

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
	 		}
}

void URLTable::addentry(int doc_id, string url){

	map.insert(pair<int, string>(doc_id,url));
}

StreamBuffer& operator<<(StreamBuffer &stream, URLTable &table){
	table.deserialize(stream);
	return stream;
}

StreamBuffer& operator>>(StreamBuffer &stream, URLTable &table) {
    table.serialize(stream);
    return stream;
}



std::ostream& operator<<(std::ostream &stream, URLTable &table) {
    stream << "map {" << std::endl;
    for( std::map<int, string>::iterator it = table.map.begin(); it!=table.map.end(); ++it){
        stream << it->first << ": " << it->second<< std::endl;
    }
    stream << "}" << std::endl;
    return stream;
}
