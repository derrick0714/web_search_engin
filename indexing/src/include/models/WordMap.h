/*
 * WordMap.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef WORDMAP_H_
#define WORDMAP_H_
using namespace std;


class WordMap {
public:
	WordMap();
	virtual ~WordMap();
private:
	static WordMap instance;
	static int capacity;
	std::list<Word> list;
};

#endif /* WORDMAP_H_ */
