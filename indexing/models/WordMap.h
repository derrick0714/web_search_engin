/*
 * WordMap.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef WORDMAP_H_
#define WORDMAP_H_
#if __GNUC__>2
#include<ext/hash_set>
#include<ext/hash_map>
using namespace __gnu_cxx;
#else
#include <hash_set>
#include <hash_map>
using namespace stdext;
#endif
using namespace std;


class WordMap {
public:
	WordMap();
	virtual ~WordMap();
private:
	static WordMap instance;
	static int capacity;
	hash_map<string, int> map;
};

#endif /* WORDMAP_H_ */
