/*
 * Lexicon.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef LEXICON_H_
#define LEXICON_H_
using namespace std;

class Lexicon {
public:
	Lexicon();
	virtual ~Lexicon();
private:
	int 	word_id;
	long	startpos;
	long	endpos;
	int		numofdoc;
};

#endif /* LEXICON_H_ */
