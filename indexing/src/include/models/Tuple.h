/*
 * Tuple.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef TUPLE_H_
#define TUPLE_H_

using namespace std;

class Tuple {
public:
	Tuple();
	virtual ~Tuple();

private:
	string 	word;
	int		word_id;
	int		doc_id;
	int		freq;
	int		pos;
	string  content;

};

#endif /* TUPLE_H_ */
