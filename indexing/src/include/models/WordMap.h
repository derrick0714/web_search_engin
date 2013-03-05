/*
 * WordMap.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef WORDMAP_H_
#define WORDMAP_H_
#include <map>
#include <string>
using namespace std;
#include "StreamBuffer.h"

class WordMap {
public:
	WordMap();
	virtual ~WordMap();
	bool isHas(string key);
	int& operator[](string key){return map[key];}
	void serialize(  StreamBuffer &stream );
	void deserialize( StreamBuffer &stream  );
	
	friend StreamBuffer& operator<<(StreamBuffer &stream, WordMap&);
	friend StreamBuffer& operator>>(StreamBuffer &stream, WordMap&);
private:
	map<string, int> map;
};

#endif /* WORDMAP_H_ */
