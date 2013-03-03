#include "analysis_ctrl.h"
#include <iostream>
using namespace std;

#define INDEX_CHUNK 409600 //50KB
#define DATA_CHUNK 20971520 //2.5MB

analysis_ctrl::analysis_ctrl()
{
    _dataset_path = "./dataset/";
    _file_num = 1800;
    _doc_id = 0;
}

analysis_ctrl::~analysis_ctrl()
{

}

bool analysis_ctrl::start()
{
   	//set display call back
    display::get_instance()->set_input_call_back(this);
    
    do_it();

    
    /*int already_len = 0;
   
    if(data == NULL)
    {
    	cout<<"error";
    	return false;
    }
    cout<<"read:"<<already_len<<endl;
    cout<<data;*/
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
        int already_len = 0;
        //get index data from file
        char* index_data = gzip::uncompress_from_file(data_set._index.c_str(), INDEX_CHUNK, already_len);
        if( index_data == NULL || already_len == 0)
        {
            cout<<"read index data error: "<<data_set._index.c_str()<<endl;
            continue;
        }


        if( !save_index( index_data,  already_len) )
        {
            cout<<"save index data error"<<endl;
            continue;
        }

        _original_index.show();


        //get html data from file
        char* html_data = gzip::uncompress_from_file(data_set._data.c_str(), DATA_CHUNK, already_len);
        if( html_data == NULL || already_len == 0)
        {
            cout<<"read html data error :"<<data_set._data.c_str()<<endl;
            continue;
        }

        if(!save_data( html_data ))
        {
            cout<<"save index data error"<<endl;
            continue;
        }
    }
    
}

bool analysis_ctrl::get_next_file_name(DataSet& data_set)
{
    if( _file_num <= 1800)
    {
        data_set.set_num(_file_num);
        _file_num++;
        return true;
    }
    return false;
}


bool analysis_ctrl::parse()
{

}

bool analysis_ctrl::save_index(char* index_data , int len )
{
    if( index_data == NULL || len == 0)
        return false;
    cout<<len<<" "<<strlen(index_data)<<endl;
    int pos = 0;
    int offset_val =0;
    while(pos < len)
    {
        string host ="", ip="", port="", sub_url="",state="",offset="";  
        //get host
        get_one_word(index_data,pos,host);     
        get_one_word(index_data,pos,ip);
        get_one_word(index_data,pos,port);
        get_one_word(index_data,pos,sub_url);
        get_one_word(index_data,pos,state);
        get_one_word(index_data,pos,offset);
        offset_val += atoi(offset.c_str());

        _original_index.put(get_new_doc_id(),(host+sub_url).c_str(), offset_val);
       
        
    }
    return true;
}

bool analysis_ctrl::save_data(char* html_data)
{
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
}

int analysis_ctrl::get_new_doc_id()
{
    return _doc_id++;
}



