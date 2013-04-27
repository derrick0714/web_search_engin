

#ifndef _DOC_MAP_H
#define _DOC_MAP_H
#include <map>
#include <string>
#include "StreamBuffer.h"
using namespace std;


struct STRU_DOC
{
	string doc_name;
	int file_id;
	int offset;
	int len;
};
class DocMap 
{
public:
	DocMap();
	~DocMap();
	STRU_DOC& operator[](int key){return _data[key];}
	void serialize(  StreamBuffer &stream );
	void deserialize( char* buffer, int size ,int&d_agv, int& N );
	
	//friend StreamBuffer& operator<<(StreamBuffer &stream, DocMap&);
	friend StreamBuffer& operator>>(StreamBuffer &stream, DocMap&);
public:
	map<int, STRU_DOC> _data;
};

#endif /* _DOC_MAP_H */
