

#ifndef _DOC_MAP_H
#define _DOC_MAP_H
#include <map>
#include <string>
#include "StreamBuffer.h"
using namespace std;


struct STRU_DOC
{
	int doc_id;
	int file_id;
	int offset;
	int len;
};
class DocMap 
{
public:
	DocMap();
	~DocMap();
	bool isHas(string key);
	STRU_DOC& operator[](string key){return _data[key];}
	void serialize(  StreamBuffer &stream );
	void deserialize( StreamBuffer &stream  );
	
	friend StreamBuffer& operator<<(StreamBuffer &stream, DocMap&);
	friend StreamBuffer& operator>>(StreamBuffer &stream, DocMap&);
private:
	map<string, STRU_DOC> _data;
};

#endif /* _DOC_MAP_H */
