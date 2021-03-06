
#include "Docmap.h"

DocMap::DocMap() {
	// TODO Auto-generated constructor stub

}

DocMap::~DocMap() {
	// TODO Auto-generated destructor stub
}


void DocMap::serialize( StreamBuffer &stream )
{
	for ( std::map<int, STRU_DOC>::iterator it = _data.begin(); it!=_data.end(); ++it)
	{
			stream.write(&it->first);
			int tmp = it->second.doc_name.length();
			stream.write(&tmp);
			stream.write(it->second.doc_name.c_str(), it->second.doc_name.length());

			tmp = it->second.doc_path.length();
			stream.write(&tmp);
			stream.write(it->second.doc_path.c_str(), it->second.doc_path.length());

			tmp = it->second.doc_title.length();
			stream.write(&tmp);
			stream.write(it->second.doc_title.c_str(), it->second.doc_title.length());

			tmp = it->second.doc_url.length();
			stream.write(&tmp);
			stream.write(it->second.doc_url.c_str(), it->second.doc_url.length());

			tmp = it->second.doc_location.length();
			stream.write(&tmp);
			stream.write(it->second.doc_location.c_str(), it->second.doc_location.length());

			//stream.write(&it->second.file_id);
			//stream.write(&it->second.file_id);
			//stream.write(&it->second.offset);
			stream.write(&it->second.doc_time);
			stream.write(&it->second.len);

			//cout<<"url:"<<it->first<<" doc_id:"<<it->second.doc_id<<" file_id:"<<it->second.file_id<<" offset:"<<it->second.offset<<" len:"<<it->second.len<<endl;
	}
				
}


void DocMap::deserialize( char* buffer, int size, int&d_agv, int& N  )
{
	_data.clear();
	//<<"buffer:"<<buffer<<"size:"<<size<<endl;
	int offset = 0;
	unsigned long long tatal_size = 0;
	N=0;
	while(offset < size)
	{
		int key;
		memcpy(&key, buffer+offset, sizeof(int));
		offset += sizeof(int);


		STRU_DOC val;

		int len;
		memcpy(&len, buffer+offset, sizeof(int));
		offset += sizeof(int);

		
	    //cout<<"len:"<<len;
	    char doc_name[len+1];
	    doc_name[len]='\0';
	 	memcpy(doc_name, buffer+offset, len);
	    offset+= len;
	    val.doc_name = doc_name;


		memcpy(&len, buffer+offset, sizeof(int));
		offset += sizeof(int);
		char doc_path[len+1];
	    doc_path[len]='\0';
	 	memcpy(doc_path, buffer+offset, len);
	    offset+= len;
	    val.doc_path = doc_path;

	    memcpy(&len, buffer+offset, sizeof(int));
		offset += sizeof(int);
		char doc_title[len+1];
	    doc_title[len]='\0';
	 	memcpy(doc_title, buffer+offset, len);
	    offset+= len;
	    val.doc_title = doc_title;

	    memcpy(&len, buffer+offset, sizeof(int));
		offset += sizeof(int);
		char doc_url[len+1];
	    doc_url[len]='\0';
	 	memcpy(doc_url, buffer+offset, len);
	    offset+= len;
	    val.doc_url = doc_url;

	    memcpy(&len, buffer+offset, sizeof(int));
		offset += sizeof(int);
		char doc_location[len+1];
	    doc_location[len]='\0';
	 	memcpy(doc_location, buffer+offset, len);
	    offset+= len;
	    val.doc_location = doc_location;



	    memcpy(&val.doc_time, buffer+offset, sizeof(int));
	    offset+= sizeof(int);

	  
	    // memcpy(&val.file_id, buffer+offset, sizeof(int));
	    // offset+= sizeof(int);
	    // memcpy(&val.offset, buffer+offset, sizeof(int));
	    // offset+= sizeof(int);
	     memcpy(&val.len, buffer+offset, sizeof(int));
	     offset+= sizeof(int);
	   
	   	tatal_size+=val.len;
	   	//cout<<
	    N++;
    	_data[key]=val;

    	//cout<<"doc_id:"<<key<<" doc_name:"<<val.doc_name<<" len:"<<val.len<<" location:"<<val.doc_location<<" time:"<<val.doc_time<<" path:"<<doc_path<<endl;	            
	 }
	 d_agv = tatal_size/N;
}



StreamBuffer& operator>>(StreamBuffer &stream, DocMap &data) {
    data.serialize(stream);
    return stream;
}



