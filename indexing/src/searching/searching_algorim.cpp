#include "searching_algorim.h"
#include <stdio.h>
#include <math.h>
using namespace std;
#define INDEX_CHUNK 409600 //50KB
#define DATA_CHUNK 20971520 //2.5MB

SearchingAlgorim::SearchingAlgorim()
{
	init_data();
}

SearchingAlgorim::~SearchingAlgorim()
{

}

void SearchingAlgorim::init_data()
{
	k1 = 1.2;
	b = 0.75;
	//read doc map
	 
	int size = 0;
	char* buffer = init_buffer_from_file("intermediate/docs_map.data0",size);
	if( buffer == NULL)
		return;
	//cout<<buffer<<size;
	_doc_map.deserialize(buffer,size,d_agv,N);
	cout<<"d:"<<d_agv<<"N:"<<N<<endl;

	delete buffer;

	//read word map
	buffer = init_buffer_from_file("intermediate/word_map.data0",size);
	if( buffer == NULL)
		return;
	//cout<<buffer<<size;
	_word_map.deserialize(buffer,size);
	
	delete buffer;
/*
	int offset;
	for(map<string, STRU_DOC>::iterator it=_doc_map._data.begin(); it != _doc_map._data.end(); it++)
	{
		if(it->second.doc_id == 4167)
		{
			cout<<"file_id:"<<it->second.file_id<<"offset:"<<it->second.offset<<endl;

		}
	}

	ifstream file ("/intermediate" , ios::in|ios::binary);
	if (file.is_open())
	{
		file.seekg(5043003, ios::beg);
		size = file.tellg();
	}
*/
	std::string file="result/";
	char filename[50]={0};
	int index_num = 5;
	int part1,part2,part3,part4,part5,len,test;
	char tmp[4];

	/*load word_index*/
	for(int i=0; i<index_num; i++){
	sprintf (filename, "word_index%d", i);
	file = file + filename;
	ifstream myFile (file.c_str(), ios::in | ios::binary);

	while(myFile.peek()!=EOF){
	myFile.read(tmp,sizeof(int));
	memcpy(&part1, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part2, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part3, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part4, tmp, sizeof(int));
	word_inf inf1 = {part2,part3,part4};
	word_index.insert(pair<int, word_inf>(part1,inf1));
	 }
	file="result/";
	}
	//for ( map<int, word_inf>::iterator it = word_index.begin(); it!=word_index.end(); ++it)
	//		cout << it->first << " => " << it->second.doc_num << " => " << it->second.chunk_num << " => " << it->second.posting_num << '\n';
	printf("the size of word_index map %d\n", word_index.size());

	/*load chunk_index*/
	file="result/";
	char filename1[50]={0};
	for(int i=0; i<2; i++){
	sprintf (filename1, "chunk_index%d", i);
	file = file + filename1;
	ifstream myFile (file.c_str(), ios::in | ios::binary);

	while(myFile.peek()!=EOF){
	myFile.read(tmp,sizeof(int));
	memcpy(&part1, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part2, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part3, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part4, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part5, tmp, sizeof(int));
	chunk chunk1 = {part2,part3,part4,part5};
	chunk_index.insert(pair<int, chunk>(part1,chunk1));
	 }
	file="result/";
	}
	//for ( map<int, chunk>::iterator it = chunk_index.begin(); it!=chunk_index.end(); ++it)
	//		cout << it->first << " => " << it->second.chunk_last_wordid << " => " << it->second.chunk_last_docid << " => " << it->second.filenum <<" => " <<it->second.offset <<  endl;
	printf("the size of chunk_index map %d\n", chunk_index.size());

	/*load word_map*/
	file="intermediate/";
		char filename2[50]={0};
		for(int i=0; i<1; i++){
		sprintf (filename2, "word_map.data%d", i);
		file = file + filename2;
		ifstream myFile (file.c_str(), ios::in | ios::binary);

		while(myFile.peek()!=EOF){

		myFile.read(tmp,sizeof(int));
		memcpy(&len, tmp, sizeof(int));
		char tmp_buf[len+1];
		tmp_buf[len]='\0';
		myFile.read(tmp_buf,len);
		string mystring(tmp_buf);

		myFile.read(tmp,sizeof(int));
		memcpy(&part2, tmp, sizeof(int));

		word_map.insert(pair<string, int>(mystring, part2));
		 }
		file="intermediate/";
		}
		//for ( map<string, int>::iterator it = word_map.begin(); it!=word_map.end(); ++it)
		//		cout << it->second << " => " << it->first<<endl;
		printf("the size of word_map %d\n", word_map.size());

}

char* SearchingAlgorim::init_buffer_from_file(string file_name, int& size)
{	
	//cout<<file_name<<endl;
	ifstream file (file_name.c_str() , ios::in|ios::binary);
	if (file.is_open())
	{
		file.seekg(0, ios::end);
		size = file.tellg();
		//cout<<size<<endl;
		char *buffer = new char [size];
		file.seekg (0, ios::beg);
		file.read (buffer, size);
		file.close();	

		//cout<<"buf:"<<buffer<<endl;

		//int a;
		/*char *b = new char[55];
		b[54]='\0';
		memcpy(b,buffer+4,54);
		cout<<"b:"<<b<<endl;*/		
		return buffer;
	}
	else
	{
		cout<<file_name<<" open filed"<<endl;
		return NULL;
	}
}

void SearchingAlgorim::do_searching(string words)
{	
	cout<<"do searching...."<<endl<<" key words:"<<words;
	//for(int i =0; i< key_words.size();i++)
	//	cout<<key_words[i]<<" ";
	cout<<endl;
	_result.clear();

	STRU_RESULT test;
	test._url ="http://www.sina.com.cn";
	test._title="sina.com.cn";
	test._round_text = "hahahahah";
	test._bm25=12;


	_result.add_one(test);

//	_result.print();

	int word_id=_word_map[words];
	cout<<"word_id:"<<word_id<<endl;
	Lp *p =openList(word_id);
	int did = 0;
	while(did < N)
	{

	 	did = nextGEQ(p,did);

	 	int freq= getFreq(p);
	 	int ft=p->doc_num;
	 	STRU_DOC one_doc = _doc_map[did];
	 	cout<<"doc_id:"<<did<<"url:"<<one_doc.doc_name<<" file: "<<one_doc.file_id<<" offset:"<<one_doc.offset<<" len:"<<one_doc.len<<endl;
	 	cout<<"req:"<<freq<<" ft:"<<ft<<endl;

	 	//comput bm25
	 	float K = (float)k1 * (float)((1-b) + b* ((float)one_doc.len / (float)d_agv ) );
	 	cout<<"K:"<<K<<endl;
	 	float inlog=(float)(N-ft+0.5)/(float)(ft+0.5);
	 	cout<<"in log:"<<inlog<<endl;
	 	float bm25 = log ( (float)(N-ft+0.5)/(float)(ft+0.5) ) * ((k1 + 1)*(float)freq)/(float)(K + freq);
	 	cout<<"bm25:"<<bm25<<endl;
	 	

		did++;
	}

}

// char filename[20];
// 	 	sprintf(filename,"dataset/%d_data",one_doc.file_id);
// 	 	int already_len = 0;
// 	 	char* index_data = gzip::uncompress_from_file(filename, INDEX_CHUNK, already_len);
//         if( index_data == NULL || already_len == 0)
//         {
//             cout<<"read index data error: "<<filename<<endl;
//             continue;
//         }
//         char* html = new char[already_len];
//         memcpy(html,index_data+one_doc.offset,one_doc.len);
//         cout<<html<<endl;

// float SearchingAlgorim::BM25( int doc_id )
// {

// }

