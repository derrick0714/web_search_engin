
#include "Docmap.h"

DocMap::DocMap() {
	// TODO Auto-generated constructor stub

}

DocMap::~DocMap() {
	// TODO Auto-generated destructor stub
}

bool DocMap::isHas(string key)
{
	return _data.find(key) != _data.end();
}

void DocMap::serialize( StreamBuffer &stream )
{
	for ( std::map<string, STRU_DOC>::iterator it = _data.begin(); it!=_data.end(); ++it)
	{
			int tmp = it->first.length();
			stream.write(&tmp);
			stream.write(it->first.c_str(), it->first.length());
			stream.write(&it->second.doc_id);
			stream.write(&it->second.file_id);
			stream.write(&it->second.offset);
			stream.write(&it->second.len);

			//cout<<"url:"<<it->first<<" doc_id:"<<it->second.doc_id<<" file_id:"<<it->second.file_id<<" offset:"<<it->second.offset<<" len:"<<it->second.len<<endl;
	}
				
}


void DocMap::deserialize( StreamBuffer &stream )
{
	_data.clear();
/*	
	while(stream.active())
	{
		int key;
	    stream.read(&key);
	    int length;
	    stream.read(&length);
	    char buffer[length+1];
	    buffer[length]='\0';
	    stream.read(buffer,length);
	    string buf(buffer);

    map.insert(pair<int,string>(key,buf));
	            
	 }*/
}

StreamBuffer& operator<<(StreamBuffer &stream, DocMap &data){
	data.deserialize(stream);
	return stream;
}

StreamBuffer& operator>>(StreamBuffer &stream, DocMap &data) {
    data.serialize(stream);
    return stream;
}



