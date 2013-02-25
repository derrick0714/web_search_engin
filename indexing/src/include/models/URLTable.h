/*
 * URLTable.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef URLTABLE_H_
#define URLTABLE_H_
#include <map>
using namespace std;

class URLTable {
public:
	URLTable();
	virtual ~URLTable();
private:
	static URLTable instance;
	map<string, int> map;
};

#endif /* URLTABLE_H_ */
