/*
 * Word.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef WORD_H_
#define WORD_H_
using namespace std;

class Word {
public:
	Word();
	virtual ~Word();
private:
	string	word;
	int		word_id;
};

#endif /* WORD_H_ */
