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

void URLTable::serialize( ostream &stream) {

	for ( std::map<string, int>::iterator it = map.begin(); it!=map.end(); ++it){
			stream.write(reinterpret_cast <const char*> ( it->first), sizeof(it->first));
			stream.write(reinterpret_cast <const char*> ( it->second), sizeof(it->second));
	}

}

void URLTable::deserialize( istream &stream ){
	for (int i=0; i<map.max_size();i++ ){
		 //std::vector<char> buffer(sizeof())
		 //need to extract the key and value from the stream, no fixed size, using /0?
	}

}

stringbuf& URLTable::operator<<(stringbuf &stream){
	std::istream ibuffer(&stream);
	deserialize(ibuffer);
	return stream;
}

stringbuf& URLTable::operator>>(stringbuf &stream){
	std::ostream obuffer(&stream);
	serialize(obuffer);
	return stream;
}

ostream& URLTable::operator<<(ostream &stream){
	stream << "Container {" << std::endl;
	for ( std::map<string, int>::iterator it = map.begin(); it!=map.end(); ++it){
		stream << it->first << ": " << it->second << std::endl;
	}
	stream << "}" << std::endl << std::endl;
	stream << "}" << std::endl << std::endl;
}
