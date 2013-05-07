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
    _intermediate = new StreamBuffer(120*1024*1024/4);
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
        
        // parse xml data from file   
        if( !parse_xml(next_file_path, parsed_data, DATA_CHUNK))
        {
            cout<<"parse xml failed:"<<next_file_path<<endl;
            continue; 
        }
        //cout<<parsed_data<<endl;

        //gen a new doc id, store docs' information, and build index of docs
        int doc_id = get_doc_id(next_file_name ,next_file_path );
        cout<<"parsing doc id:"<<doc_id<<"=>"<<next_file_path<<endl;


        //save the data to form intermediate
        save_data(doc_id, parsed_data, DATA_CHUNK);
        
        //break;
    }
  

    //     if( !save_index(index_data, already_len, index, data_set._file_num) )
    //     {
    //         cout<<"save index data error"<<endl;
    //         continue;
    //     }

    //     free(index_data);

    //     //get html data from file
    //     char* html_data = gzip::uncompress_from_file(data_set._data.c_str(), DATA_CHUNK, already_len);
    //     if( html_data == NULL || already_len == 0)
    //     {
    //         cout<<"read html data error :"<<data_set._data.c_str()<<endl;
    //         continue;
    //     }

    //     //parse word from html data 
    //     if(!parse_data(html_data, already_len, index))
    //     {
    //         cout<<"parse index data error"<<endl;
    //         continue;
    //     }

        
    //     free(html_data);
    //     //break;
    //    // cout<<"loop"<<endl;
    // }


   
    StreamBuffer buffer1(50*1024*1024);
    buffer1.setfilename("intermediate/word_map.data");
    buffer1>>_word_map;
    buffer1.savetofile();

      //save docs map;
     StreamBuffer buffer2(50*1024*1024);
     buffer2.setfilename("intermediate/docs_map.data");
     buffer2>>_docs_map;
     buffer2.savetofile();

     //
     
     _intermediate->savetofile();

     cout<<"[finish] time consumed: "<<time(0)-_time_now<<"s"<<endl;
    
}





bool analysis_ctrl::parse_xml(std::string file_path, char* buf, int buf_len)
{
    if( buf == NULL)
        return false;
   // cout<<"1"<<endl;
    ifstream file;
    file.open(file_path.c_str());
    int off_start, off_end;
    string content_start = "<block class=\"full_text\">";
    string temp_title = "temp title";
    if (file.is_open())
    {
        file.seekg (0, file.end);
        int length = file.tellg();
        file.seekg (0, file.beg);
        char * xml_buffer = new char [length];
        string xml_content; 
        // read data as a block:
        file.read(xml_buffer,length);
        xml_content = xml_buffer;

        
        //cout<<line.find("$$$")<<" "<<line.find("<block class=\"full_text\">")<<endl;

        if( (off_start = xml_content.find(content_start)) != string::npos && (off_end = xml_content.find("</block>",off_start+1)) != string::npos)
        {
            //get content
            off_start = off_start + content_start.length();
            int len = off_end - off_start ;
            char* content_buf = new char[len + 1];
            content_buf[len]= '\0';
            memcpy( content_buf, xml_buffer+off_start, len );

            //cout<<content_buf<<endl;
           
            //parsing content
            int ret = parser((char*)temp_title.c_str(), content_buf , buf, buf_len);
            
            delete content_buf;

            //output words and their contexts
            if (ret < 0)
            {
                cout<<"error during the parse"<<endl;
               // printf("%s", pool);
                 //save raw data into rgnized data structer
                // if( !save_data( doc_id , pool, 2*index_val.len+1) )
                // {
                //      cout<<"save index data error"<<endl;
                //     // continue;
                // }
            }
                        
        }

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



// bool analysis_ctrl::parse_data(char* html_data, int len, original_index& index)
// {
//     original_index_content index_val;
//     int doc_id =0;

//     index.set_to_start();


//     // get one doc offset and id from index list 
//     while(index.get_next(doc_id ,index_val))
//     {
      
//         cout<<"parsing: "<<doc_id<<" => "<<index_val.url<<":"<<index_val.offset<<":"<<index_val.len<<endl;

//         char *pool;

//         pool = (char*)malloc(2*index_val.len+1);


//         //parsing page
//         char* page = new char[index_val.len+1];
        
//         memcpy(page, html_data+index_val.offset, index_val.len);
//         page[index_val.len]='\0';
        

//         int ret = parser((char*)index_val.url.c_str(), page , pool, 2*index_val.len+1);
        
//         delete page;

//        // cout<<pool<<endl;
//         //return false;
//         //output words and their contexts
//         if (ret > 0)
//         {
//             //printf("%s", pool);
//              //save raw data into rgnized data structer
//             if( !save_data( doc_id , pool, 2*index_val.len+1) )
//             {
//                 cout<<"save index data error"<<endl;
//                // continue;
//             }

//         }
        
//         free(pool);
        
       
       
//     }
//      return true;
    
// }



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

int analysis_ctrl::get_doc_id(string doc_name, string doc_path )
{

    if(_checker.find(doc_name) != _checker.end())
    {   
        cout<<"doc repeat:"<<doc_name<<"=>"<<_checker[doc_name]<<endl;
        return _checker[doc_name];
    }
    _checker[doc_name]= _doc_id;

    _docs_map[_doc_id].doc_name = doc_name;
    _docs_map[_doc_id].doc_path = doc_path;
    // _docs_map[_doc_id].offset = offset;
    // _docs_map[_doc_id].len = len;
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
