#include "analysis_ctrl.h"
#include <iostream>
using namespace std;

#define INDEX_CHUNK 409600 //50KB
#define DATA_CHUNK 20971520 //2.5MB

analysis_ctrl::analysis_ctrl()
{
    _dataset_path = "./dataset/";

    _file_start = 1800;
    _file_end = 1820;
    _file_now = _file_start;
    _doc_id = 1;
    _word_id =1;
    buffer = new StreamBuffer(2*1024*1024);
    buffer->setfilename("ip");
    buffer->setpostingsize(8);
    buffer->set_sort(true);

}

analysis_ctrl::~analysis_ctrl()
{
    if(buffer != NULL)
        delete buffer;
}

bool analysis_ctrl::start()
{
   	//set display call back
    //display::get_instance()->set_input_call_back(this);
    
    do_it();

    return true;
}

void analysis_ctrl::stop()
{
   	//stop display
    display::get_instance()->stop();

}

void analysis_ctrl::input_event( char* key )
{

	if( strcmp(key,"quit") == 0)
		stop();
	else
		cout<<"press 'quit' to exit"<<endl;
}

// core algorithm
void analysis_ctrl::do_it()
{
    DataSet data_set(_dataset_path);
    while( get_next_file_name(data_set) )
    {
        //cout<<"loop"<<endl;
        int already_len = 0;

        //get index data from file
        char* index_data = gzip::uncompress_from_file(data_set._index.c_str(), INDEX_CHUNK, already_len);
        if( index_data == NULL || already_len == 0)
        {
            cout<<"read index data error: "<<data_set._index.c_str()<<endl;
            continue;
        }

        

        //cout<<"doc_id:"<<doc_id<<endl;
        //save raw data into orgnized data structer
        original_index index;

        if( !save_index(index_data, already_len, index ) )
        {
            cout<<"save index data error"<<endl;
            continue;
        }

        free(index_data);

        //get html data from file
        char* html_data = gzip::uncompress_from_file(data_set._data.c_str(), DATA_CHUNK, already_len);
        if( html_data == NULL || already_len == 0)
        {
            cout<<"read html data error :"<<data_set._data.c_str()<<endl;
            continue;
        }

        //parse word from html data 
        if(!parse_data(html_data, already_len, index))
        {
            cout<<"parse index data error"<<endl;
            continue;
        }

        
        free(html_data);
        cout<<"loop"<<endl;
    }

    //save word map;
    //_word_map

   
     StreamBuffer buffer1(1*1024*1024);
     buffer1.setfilename("word_map.data");
     buffer1>>_word_map;
     buffer1.savetofile();

      //save docs map;
     StreamBuffer buffer2(1*1024*1024);
     buffer2.setfilename("docs_map.data");
     buffer2>>_docs_map;
     buffer2.savetofile();

     //
     
     buffer->savetofile();

     cout<<"ok!finish!"<<endl;
    
}

bool analysis_ctrl::get_next_file_name(DataSet& data_set)
{

    if( _file_now <= _file_end)
    {


        data_set.set_num(_file_now);
  
        _file_now++;
        return true;
    }
    return false;
}


bool analysis_ctrl::parse()
{

}



bool analysis_ctrl::parse_data(char* html_data, int len, original_index& index)
{
    original_index_content index_val;
    int doc_id =0;

    index.set_to_start();

    while(index.get_next(doc_id ,index_val))
    {
      
        cout<<"parsing: "<<doc_id<<" => "<<index_val.url<<":"<<index_val.offset<<":"<<index_val.len<<endl;

        char *pool;

        pool = (char*)malloc(2*index_val.len+1);

        //parsing page
        char* page = new char[index_val.len];
        
        memcpy(page, html_data+index_val.offset, index_val.len);
        

        int ret = parser((char*)index_val.url.c_str(), page , pool, 2*index_val.len+1);
        delete page;


        //output words and their contexts
        if (ret > 0)
        {
            //printf("%s", pool);
             //save raw data into rgnized data structer
            if( !save_data( doc_id , pool, 2*index_val.len+1) )
            {
                cout<<"save index data error"<<endl;
               // continue;
            }

        }
        
        free(pool);

       
    }
     return true;
    
}

bool analysis_ctrl::save_index(char* index_data , int len ,original_index& index)
{
    if( index_data == NULL || len == 0)
        return false;
    cout<<len<<" "<<strlen(index_data)<<endl;
    int pos = 0;
    int offset_val =0;
    while(pos < len && pos != -1)
    {
        string host ="", ip="", port="", sub_url="",state="",len="";  
        //get host
        get_one_word(index_data,pos,host);     
        get_one_word(index_data,pos,ip);
        get_one_word(index_data,pos,port);
        get_one_word(index_data,pos,sub_url);
        get_one_word(index_data,pos,state);
        get_one_word(index_data,pos,len);
        int len_val = atoi(len.c_str());

        // if exit doc id, return it else create new id 
        int doc_id = get_doc_id((host+sub_url).c_str());
        index.put(doc_id,(host+sub_url).c_str(), offset_val,len_val);
        offset_val+=len_val;
        
    }

    return true;
}

bool analysis_ctrl::save_data(int doc_id, char* save_data, int len)
{
    int pos = 0;
    int offset_val =0;
    int count = 0;
    int percent =( (float)(_file_now -1 - _file_start) / (float)(_file_end - _file_start) )*100;
    
    while(pos < len && pos != -1)
    {
        string word="";
        get_one_word(save_data , pos, word);
        if( pos == -1)
        {
           //cout<< "save_data::get_one_word finish"<<endl;
            break;
        }
        //if it is word 
        if( count++ % 2 == 0)
        {
            TempLexicon new_lexicon;

            new_lexicon.word_id = get_word_id(word);
            new_lexicon.doc_id = doc_id;

            cout<<"[-"<<percent<<"\%-][doc:"<<new_lexicon.doc_id<<"] : "<<word<<"=>"<<new_lexicon.word_id<<endl;

            //save temp Lexicon
            (*buffer)>>new_lexicon;
            
        }
        
    }

    return true;
}

//get on word from file
void analysis_ctrl::get_one_word(char* source ,int& pos,string& str)
{
    
    char get_num = 0;
    while( source[pos] != 0)
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
                //cout<<temp<<endl;
                return ;
            }
        }
        else 
        {
            str+=source[pos++];
            get_num++;

            //cout<<str.c_str()<<endl;
        }
    }
    if( source[pos] == '\0')
        pos = -1;
}

int analysis_ctrl::get_doc_id(string doc_name)
{
     if(_docs_map.isHas(doc_name))
    {   
        cout<<"doc repeat:"<<doc_name<<"=>"<<_docs_map[doc_name]<<endl;
        return _docs_map[doc_name];
    }

    _docs_map[doc_name] = _doc_id;

    return _doc_id++;
}

int analysis_ctrl::get_word_id(string word)
{
    if(_word_map.isHas(word))
    {   
      //  cout<<"word repeat:"<<word<<"=>"<<_word_map[word]<<endl;
        return _word_map[word];
    }

    _word_map[word] = _word_id;
    return _word_id++;

}   

