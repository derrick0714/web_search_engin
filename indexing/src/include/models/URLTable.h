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
using namespace std;

class URLTable {
public:
	URLTable();
	virtual ~URLTable();
	stringbuf& operator<<(stringbuf &stream);
	stringbuf& operator>>(stringbuf &stream);
	ostream&   operator<<(ostream &stream);

private:
	static URLTable instance;
	map<string, int> map;
	void serialize( ostream &stream);
	void deserialize( istream &stream);
};

#endif /* URLTABLE_H_ */
