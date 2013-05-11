#include "analysis_ctrl.h"
#include <sys/stat.h>
#include <iostream>
#include <fstream>

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
    _intermediate = new StreamBuffer(12*1024*1024/4);
    mkdir("intermediate", S_IRWXU|S_IRGRP|S_IXGRP);
    _intermediate->setfilename("intermediate/posting");
    _intermediate->setpostingsize(12);
    _intermediate->set_sort(true);
    _time_now = time(0); 

}

analysis_ctrl::~analysis_ctrl()
{
    if(_intermediate != NULL)
        delete _intermediate;
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
    string next_file_name, next_file_path;
    char* parsed_data = new char[DATA_CHUNK];
    int data_len = 0;
    while( _finder.get_next_file(next_file_name,next_file_path))
    {
        string doc_title,doc_url="",doc_location="";
        int doc_date=0;
        // parse xml data from file   
        if( !parse_xml(next_file_path, parsed_data, DATA_CHUNK, doc_title,doc_url,doc_location, doc_date))
        {
            cout<<"parse xml failed:"<<next_file_path<<endl;
            continue; 
        }
        //cout<<parsed_data<<endl;

        //gen a new doc id, store docs' information, and build index of docs
        int doc_id = get_doc_id(next_file_name ,next_file_path ,doc_title,doc_url,doc_location,doc_date);
        cout<<"parsing doc id:"<<doc_id<<"=>"<<next_file_path<<" title:"<<doc_title<<endl;
       // cout<<"url:"<<doc_url<<" location:"<<doc_location<<" date:"<<doc_date<<endl;


        //save the data to form intermediate
        save_data(doc_id, parsed_data, DATA_CHUNK);
        
        //break;
    }
  
   
    StreamBuffer buffer1(50*1024*1024);
    buffer1.setfilename("intermediate/word_map.data");
    buffer1>>_word_map;
    buffer1.savetofile();

      //save docs map;
     StreamBuffer buffer2(200*1024*1024);
     buffer2.setfilename("intermediate/docs_map.data");
     buffer2>>_docs_map;
     buffer2.savetofile();

     //
     
     _intermediate->savetofile();

     cout<<"[finish] time consumed: "<<time(0)-_time_now<<"s"<<endl;
    
}





bool analysis_ctrl::parse_xml(std::string file_path, char* buf, int buf_len,string& title, string& url, string& location,int& date)
{
    if( buf == NULL)
        return false;

    //open file
    ifstream file;
    file.open(file_path.c_str());
    int off_start, off_end;

    if (file.is_open())
    {
        file.seekg (0, file.end);
        int length = file.tellg();
        file.seekg (0, file.beg);
        char * xml_buffer = new char [length];
        // read data as a block:
        file.read(xml_buffer,length);

        int start_pos=0;


        //get title
        if( !get_new_info(xml_buffer,length, start_pos, "<title>", "</title>", title) )
        {
            cout<< "get title failed!"<<endl;
        }

        //get location
        if( !get_new_info(xml_buffer,length, start_pos, "indexing_service\">", "</location>", location) )
        {
            //cout<< "get url failed!"<<endl;
            location = "NULL";
        }


        //get url
        if( !get_new_info(xml_buffer,length, start_pos, "ex-ref=\"", " i", url) )
        {
            cout<< "get url failed!"<<endl;
        }


        //get content & parse
        string content;
        if( !get_new_info(xml_buffer,length, start_pos, "<block class=\"full_text\">\n", "</block>", content) )
        {
            cout<< "get title failed!"<<endl;
        }
        // parse content
        int ret = parser((char*)title.c_str(), (char*)content.c_str() , buf, buf_len);
            
        //output words and their contexts
        if (ret < 0)
        {
            cout<<"error during the parse"<<endl;

        }

        //
        delete[] xml_buffer;
        file.close();

        return true;
    }
    else 
    {
        cout << "Unable to open file:"<<file_path<<endl;
        return false;
    } 
     
    return true;

}

bool analysis_ctrl::get_new_info(char* source, int max, int& start_pos, std::string key_start, std::string key_end, string& content)
{
    int offset_start;
    int offset_end;

    if( (offset_start = find(source, max, start_pos,key_start )) != -1 && (offset_end = find(source, max, offset_start+key_start.length(), key_end)) != -1)
    {
        offset_start = offset_start + key_start.length();
        int len = offset_end - offset_start;
        char* tmp = new char[len + 1];
        tmp[len]= '\0';
        memcpy( tmp, source+offset_start, len );
        content = tmp;

        delete[] tmp;
        //cout<<"$$$"<<content<<endl;
        start_pos = offset_end+key_end.length();
        return true;
    }

    return false;
}

int analysis_ctrl::find(char* source, int max_len, int start, std::string key_words)
{
    if(source == NULL)
        return false;
    
    int same_len = 0;
    int same_max = key_words.length();
    for(int i = start; i< max_len; i++)
    {
        if(source[i] == key_words[same_len]) 
        {
            same_len++;
            if( same_len == same_max)
            {
               // cout<<"find_key:"<<key_words<<endl;
                return (i - same_max+1);
            }
        }
        else
            same_len = 0;
    }

    return -1;
}


bool analysis_ctrl::save_data(int doc_id, char* save_data, int len)
{
    int pos = 0;
    int offset_val =0;

   // int percent = _file_end - _file_start == 0? 100 : ( (float)(_file_now -1 - _file_start) / (float)(_file_end - _file_start) )*100;
    
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
       //new_lexicon.issue_date = 

        //cout<<"[doc:"<<new_lexicon.doc_id<<"] : "<<word<<"=>word_id:"<<new_lexicon.word_id<<" position:"<<new_lexicon.startpos<<endl;

        //save temp Lexicon
        (*_intermediate)>>new_lexicon;
            
        
        
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

int analysis_ctrl::get_doc_id(string doc_name, string doc_path, string doc_title,string doc_url,string doc_location, int doc_time )
{

    if(_checker.find(doc_name) != _checker.end())
    {   
        cout<<"doc repeat:"<<doc_name<<"=>"<<_checker[doc_name]<<endl;
        return _checker[doc_name];
    }
    _checker[doc_name]= _doc_id;

    _docs_map[_doc_id].doc_name = doc_name;
    _docs_map[_doc_id].doc_path = doc_path;
    _docs_map[_doc_id].doc_title = doc_title;
    _docs_map[_doc_id].doc_url = doc_url;
    _docs_map[_doc_id].doc_location = doc_location;
    _docs_map[_doc_id].doc_time = doc_time;
    // _docs_map[_doc_id].offset = offset;
    // _docs_map[_doc_id].len = len;
   // cout<<"doc_title:"<<_docs_map[_doc_id].doc_title<<"doc_time:"<<_docs_map[_doc_id].doc_time<<endl;
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
