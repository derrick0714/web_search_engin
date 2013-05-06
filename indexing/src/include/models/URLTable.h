/*
 * URLTable.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef URLTABLE_H_
#define URLTABLE_H_
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include "StreamBuffer.h"
using namespace std;

class URLTable {

private:
	map<int, string> map;

public:
	URLTable();
	virtual ~URLTable();
	void  	addentry(int doc_id, string url);
	void 	serialize( StreamBuffer &stream);
	void 	deserialize( StreamBuffer &stream);
	friend StreamBuffer& operator<<(StreamBuffer &stream, URLTable&);
	friend StreamBuffer& operator>>(StreamBuffer &stream, URLTable&);
	friend ostream&	  operator<<(ostream &stream, URLTable&);

};

#endif /* URLTABLE_H_ */
