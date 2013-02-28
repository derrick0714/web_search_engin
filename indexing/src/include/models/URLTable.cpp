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
			char buffer[8];
//			for( int i = 0 ; i < 8 ;i++)
//				buffer[i]='w';
			memcpy(buffer,&it->first,sizeof(int));
//			sprintf (buffer,"%d",it->first);
			int tmp = it->second.length();
			memcpy(buffer+sizeof(int),&tmp,sizeof(int));
//			sprintf (buffer+sizeof(int),"%d",it->second.length());
			stream.write(buffer, 8);
			char buffer1[it->second.length()];
//			for( int i = 0 ; i < it->second.length() ;i++)
//				buffer1[i]='w';
			const char * tmpc = it->second.c_str();
			memcpy(buffer1,tmpc,it->second.length());
			stream.write(buffer1, it->second.length());
	}

}

void URLTable::deserialize( StreamBuffer &stream  ){
	map.clear();
	char buffer[4];
			for(int i=0; i<2; ++i){
	            stream.read(buffer, 4);
	            map.insert(pair<int,string>(i,&buffer[0]));
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
