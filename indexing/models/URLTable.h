/*
 * URLTable.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef URLTABLE_H_
#define URLTABLE_H_
using namespace std;

class URLTable {
public:
	URLTable();
	virtual ~URLTable();
private:
	static URLTable instance;
	std::list<URL> list;
};

#endif /* URLTABLE_H_ */
