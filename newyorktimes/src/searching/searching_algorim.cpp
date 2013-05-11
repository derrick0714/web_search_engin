#include "searching_algorim.h"
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
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

void SearchingAlgorim::do_searching(char* words)
{	
	struct timeval start, end;
 
    gettimeofday(&start, NULL);
    
	cout<<"do searching...."<<endl<<" key words:"<<words<<endl;
	//for(int i =0; i< key_words.size();i++)
	//	cout<<key_words[i]<<" ";
	result_count = 0;
	int request_count = 0;
	string word="";
	int pos=0;
	vector<string> request_list;
	while(get_one_word(words,pos,word))
	{
		cout<<"new:"<<word<<endl;
		request_list.push_back(word);
		request_count++;
		word="";

	}
	if(request_count == 0)
		return;

	vector<Lp*> p;
//	_result.print();
	for(int i = 0 ; i < request_list.size();i++)
	{
		int word_id=_word_map[request_list[i]];
		cout<<"word: "<<request_list[i]<<" word_id:"<<word_id<<endl;
		if(word_id == 0)
			continue;
		Lp* tmp = openList(word_id);
		if(tmp == NULL)
			continue;
		p.push_back(tmp);
	}
	if(p.size() == 0)
		return;
	cout<<"p.size:"<<p.size()<<endl;
	cout<<"doc_map_size"<<_doc_map._data.size()<<endl;
	int did = 0;
	while(did < N)
	{
		int d = 0;
	 	did = nextGEQ(p[0],did);
	 	if( did == 0)
 		{	
 			cout<<"did = 0"<<endl; 
 			continue;
 		}
	 	for(int i = 1; (i< p.size())&& ((d=nextGEQ(p[i],did))==did);i++);
	 	if(did> N)
	 		break;
		if(d > did) did = d-1;
		else
		{
			float bm25_all = 0.0;
			STRU_DOC one_doc = _doc_map[did];
			//cout<<"doc_id:"<<did<<"url:"<<one_doc.doc_name<<" file: "<<one_doc.file_id<<" offset:"<<one_doc.offset<<" len:"<<one_doc.len<<endl;
			int target_pos = getPos(p[0]);
			for( int k = 0 ; k<p.size(); k++)
			{
			 	int freq= getFreq(p[k]);

			 	int ft=p[k]->doc_num;
			 	
			 	if(one_doc.doc_name == "")
			 		continue;
			 	//cout<<"doc_id:"<<did<<"url:"<<one_doc.doc_name<<" file: "<<one_doc.file_id<<" offset:"<<one_doc.offset<<" len:"<<one_doc.len<<endl;
			 	//cout<<"req:"<<freq<<" ft:"<<ft<<endl;
			 	//comput bm25
			 	float K = (float)k1 * (float)((1-b) + b* ((float)one_doc.len / (float)d_agv ) );
			 	float bm25 = log ( (float)(N-ft+0.5)/(float)(ft+0.5) ) * ((k1 + 1)*(float)freq)/(float)(K + freq);
			 	//cout<<"bm25:"<<bm25<<endl;
			 	bm25_all+=bm25;
	 		}
		 	if(result_count < 10)
		 	{
		 		
				result_array[result_count]._url =one_doc.doc_url;
				cout<<one_doc.doc_url<<endl;
				result_array[result_count]._bm25=bm25_all;
				result_array[result_count]._doc_id = did;
				result_array[result_count]._pos = target_pos;
 		
		 		result_count++;
		 	}
		 	else if(bm25_all > result_array[0]._bm25)
		 	{
				result_array[0]._url =one_doc.doc_url;
				result_array[0]._bm25=bm25_all;
				result_array[0]._doc_id = did;
				result_array[0]._pos = target_pos;
	
		 	}

	 		sort(result_array,0,result_count-1);
	 	}
	 	//cout<<"list:";
	 	//for(int j =0; j < result_count; j++)
	 	//	cout<<"["<<j<<"] "<<result_array[j]._bm25<<endl;

		did++;
	}
	 gettimeofday(&end, NULL);
	_searching_time  = (end.tv_sec  - start.tv_sec)*1000+ (end.tv_usec - start.tv_usec)/1000.0;

	// cout<<"start to :get around text"<<endl;
	// //around text
	// for(int i =0; i < result_count;i++)
	// {
	// 	cout<<"get around text. doc id:"<<result_array[i]._doc_id<<endl;
	// 	STRU_DOC one_doc = _doc_map[result_array[i]._doc_id];
	// 	char filename[20];
	//  	sprintf(filename,"dataset/%d_data",one_doc.file_id);
	//  	int already_len = 0;
	//  	char* index_data = gzip::uncompress_from_file(filename, INDEX_CHUNK, already_len);
 //        if( index_data == NULL || already_len == 0)
 //        {
 //            cout<<"read index data error: "<<filename<<endl;
 //            continue;
 //        }
 //        char* html = new char[already_len];
 //        memcpy(html,index_data+one_doc.offset,one_doc.len);
 //        char *pool;

 //        pool = (char*)malloc(2*one_doc.len+1);
        

 //        int ret = parser((char*)one_doc.doc_name.c_str(), html , pool, 2*one_doc.len+1);
        
  	
 //  		cout<<"aound text:"<<request_list[0]<<endl;

 //        get_around_text(pool,already_len,result_array[i]._pos,result_array[i]._title,result_array[i]._round_text );
 //       //	cout<<"	aound:"<<result_array[i]._round_text<<" title:"<<result_array[i]._title<<endl;

 //       	free(pool);
 //       	delete[] html;
 // //       cout<<html<<endl;

	// //	result_array[result_count]._round_text=;
	// }

	for(int i =0 ;i <p.size();i++)
		closeList(p[i]);
	gettimeofday(&end, NULL);
	_whole_time  = (end.tv_sec  - start.tv_sec)*1000+ (end.tv_usec - start.tv_usec)/1000.0;
	//cout<<"end.tv_sec:"<<end.tv_sec<<" start.tv_sec:"<<start.tv_sec<<" end.tv_usec:"<<end.tv_usec<<" start.tv_usec:"<<start.tv_usec<<endl;
	 cout<<"-Time Use- "<<" all(searching+surrounding text):"<<_whole_time<<"(ms), just searching:"<<_searching_time<<"(ms)"<<endl;
	cout<<"finsh searching"<<endl;
	cout<<"-------------------"<<endl;
}
void SearchingAlgorim::get_around_text(char* html, int len,int tartget_pos,string& title, string& around_text)
{
	around_text="";
	title = "";
    int pos = 0;
    int offset_val =0;
    int start_colletion = 0;

    cout<<"target_pos:"<<tartget_pos<<endl;
    if(tartget_pos > 10)
    	start_colletion = tartget_pos-7;
    int end_colletion = start_colletion +15;

    int pos_count = 0;
   // cout<<"[-"<<percent<<"\%-][doc:"<<doc_id<<"]"<<endl;
    while(pos < len )
    {
        string word="";
        string context="";
        string positon="";

        if(
            !get_one_word(html , pos, word) ||
            !get_one_word(html , pos, positon) ||
            !get_one_word(html , pos, context)
            )
            break;

        //cout<<"["<<pos<<"]"<<"word=>"<<word<<" pos=>"<<positon<<" context=>"<<context<<endl ;
        
        if(pos_count >= start_colletion && pos_count <= end_colletion)
        {
        	//cout<<word<<" "<<context<<endl;
        	if(around_text=="")
        		around_text+=word;
        	else
        		around_text+=" "+word;
        	
        }
        if(context=="T")
        {
        	if(title=="")
        		title+=word;
        	else
        		title+=" "+word;
        }

        pos_count++;//atoi(positon.c_str()); //atoi(positon.c_str());
         
    }

   // cout<<"title"<<title<<endl;
    //cout<<pos<<"--------------------------------"<<endl<<endl<<endl<<endl<<endl;

   
	
}
void SearchingAlgorim::sort(STRU_RESULT* arr, int left , int right)
{
	if(arr == NULL)
		return;
	float pivot = arr[(left+right)/2]._bm25;
	int i = left, j=right;

	//partition
	while(i <= j)
	{
		while(arr[i]._bm25 < pivot)
			i++;
		while(arr[j]._bm25 > pivot)
			j--;
		if(i <= j)
		{
			STRU_RESULT tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
	if( j > left)
		sort(arr, left ,j);
	if( i < right)
		sort(arr, i , right);
}
char* SearchingAlgorim::get_result()
{

	if(result_count ==0)
		return "";
	
	int offset = 0;
	for(int i = result_count-1; i >=0; i --)
	{
		sprintf(result+offset,"%s\n",result_array[i]._url.c_str());
		offset+=strlen(result+offset);
		sprintf(result+offset,"%f\n",result_array[i]._bm25);
		offset+=strlen(result+offset);
		sprintf(result+offset,"%s\n",result_array[i]._round_text.c_str());
		offset+=strlen(result+offset);
		sprintf(result+offset,"%s\n",result_array[i]._title.c_str());
		offset+=strlen(result+offset);

	}
	//cout<<result<<endl;
	return result;
}
bool SearchingAlgorim::get_one_word(char* source ,int& pos,string& str)
{


    char get_num = 0;
    while( source[pos] != '\0')
    {

        if(source[pos] == '\r' || source[pos]=='\n' || source[pos] == ' ')
        {
                
            if( get_num == 0)
            {
                pos++;

                continue;
            }
            else
            {
                pos++;
                return true;
            }
        }
        else 
        {
            str+=source[pos++];
            get_num++;
            //cout<<str.c_str()<<endl;
        }
    }
    if( source[pos] == '\0' && get_num>0)
    {
    	return true; 
    }
    return false;
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

