/*
 * LexiconDic.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef LEXICONDIC_H_
#define LEXICONDIC_H_
using namespace std;


class LexiconDic {
public:
	LexiconDic();
	virtual ~LexiconDic();
private:
	static LexiconDic instance;
	std::list<Lexicon> list;


};

#endif /* LEXICONDIC_H_ */
