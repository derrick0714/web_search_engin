/*
 * LexiconDic.h
 *
 *  Created on: Feb 25, 2013
 *      Author: Adam57
 */

#ifndef LEXICONDIC_H_
#define LEXICONDIC_H_
#include <map>
using namespace std;
#include "StreamBuffer.h"

class TempLexicon 
{
public:
	int		word_id;
//	long	startpos;
	int		doc_id;

	TempLexicon(){word_id = 0; doc_id= 0;}

	void serialize(StreamBuffer &stream )
	{
		stream.write(&word_id);
		stream.write(&doc_id);

	}
	void deserialize( StreamBuffer &stream  )
	{
		stream.read(&word_id);
		stream.read(&doc_id);

	}
	
	friend StreamBuffer& operator<<(StreamBuffer &stream, TempLexicon& obj)
	{
		obj.deserialize(stream);
	}
	friend StreamBuffer& operator>>(StreamBuffer &stream, TempLexicon& obj)
	{
		 obj.serialize(stream);
	}
};


#endif /* LEXICONDIC_H_ */
