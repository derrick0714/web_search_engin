#include "analysis_ctrl.h"
#include <sys/stat.h>
#include <iostream>

using namespace std;

#define INDEX_CHUNK 409600 //50KB
#define DATA_CHUNK 20971520 //2.5MB

analysis_ctrl::analysis_ctrl()
{
    _dataset_path = "./dataset/";

    _file_start = 0;
    _file_end = 82;
    _file_now = _file_start;
    _doc_id = 1;
    _word_id =1;
    buffer = new StreamBuffer(12*1024*1024/4);
    mkdir("intermediate", S_IRWXU|S_IRGRP|S_IXGRP);
    buffer->setfilename("intermediate/posting");
    buffer->setpostingsize(12);
    buffer->set_sort(true);
    _time_now = time(0); 

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
        //break;
       // cout<<"loop"<<endl;
    }

    //save word map;
    //_word_map

   
     StreamBuffer buffer1(1*1024*1024);
     buffer1.setfilename("intermediate/word_map.data");
     buffer1>>_word_map;
     buffer1.savetofile();

      //save docs map;
     StreamBuffer buffer2(1*1024*1024);
     buffer2.setfilename("intermediate/docs_map.data");
     buffer2>>_docs_map;
     buffer2.savetofile();

     //
     
     buffer->savetofile();

     cout<<"[finish] time consumed: "<<time(0)-_time_now<<"s"<<endl;
    
}

//read file name
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


    // get one doc offset and id from index list 
    while(index.get_next(doc_id ,index_val))
    {
      
        cout<<"parsing: "<<doc_id<<" => "<<index_val.url<<":"<<index_val.offset<<":"<<index_val.len<<endl;

        char *pool;

        pool = (char*)malloc(2*index_val.len+1);


        //parsing page
        char* page = new char[index_val.len+1];
        
        memcpy(page, html_data+index_val.offset, index_val.len);
        page[index_val.len]='\0';
        

        int ret = parser((char*)index_val.url.c_str(), page , pool, 2*index_val.len+1);
        
        delete page;

       // cout<<pool<<endl;
        //return false;
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
    while(pos < len)
    {
        string url ="", ip="", port="",state="",len="",unknow1="",unknow2="";
        //get host
        if(
        !get_one_word(index_data,pos,url) ||     
        !get_one_word(index_data,pos,unknow1) ||
        !get_one_word(index_data,pos,unknow2) ||
        !get_one_word(index_data,pos,len) ||
        !get_one_word(index_data,pos,ip) ||
        !get_one_word(index_data,pos,port)||
        !get_one_word(index_data,pos,state)
        )
            break; // if read finish, break
        int len_val = atoi(len.c_str());

        // if exit doc id, return it else create new id 
        int doc_id = get_doc_id(url.c_str());
        index.put(doc_id,(url).c_str(), offset_val,len_val);
        offset_val+=len_val;
        
    }

    return true;
}

bool analysis_ctrl::save_data(int doc_id, char* save_data, int len)
{
    int pos = 0;
    int offset_val =0;

    int percent = _file_end - _file_start == 0? 100 : ( (float)(_file_now -1 - _file_start) / (float)(_file_end - _file_start) )*100;
    
    int pos_count = 0;
   // cout<<"[-"<<percent<<"\%-][doc:"<<doc_id<<"]"<<endl;
    while(pos < len )
    {
        string word="";
        string context="";
        string positon="";

        if(
            !get_one_word(save_data , pos, word) ||
            !get_one_word(save_data , pos, positon) ||
            !get_one_word(save_data , pos, context)
            )
            break;

        //cout<<"["<<pos<<"]"<<"word=>"<<word<<" pos=>"<<positon<<" context=>"<<context<<endl ;


        //continue;
        //if it is word 
        
        TempLexicon new_lexicon;

        new_lexicon.word_id = get_word_id(word);
        new_lexicon.doc_id = doc_id;
        new_lexicon.startpos =pos_count++;//atoi(positon.c_str()); //atoi(positon.c_str());

        //cout<<"[-"<<percent<<"\%-][doc:"<<new_lexicon.doc_id<<"] : "<<word<<"=>word_id:"<<new_lexicon.word_id<<" position:"<<new_lexicon.startpos<<endl;

        //save temp Lexicon
        (*buffer)>>new_lexicon;
            
        
        
    }
    
    //cout<<pos<<"--------------------------------"<<endl<<endl<<endl<<endl<<endl;

    return true;
}

//get on word from file
bool analysis_ctrl::get_one_word(char* source ,int& pos,string& str)
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
    //if( source[pos] == '\0')
    return false;
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
