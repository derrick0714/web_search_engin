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

        original_index index;

        if( !save_index( index_data, already_len, index) )
        {
            cout<<"save index data error"<<endl;
            continue;
        }

        //get html data from file
        char* html_data = gzip::uncompress_from_file(data_set._data.c_str(), DATA_CHUNK, already_len);
        if( html_data == NULL || already_len == 0)
        {
            cout<<"read html data error :"<<data_set._data.c_str()<<endl;
            continue;
        }

        if(!parse_data( html_data, already_len, index))
        {
            cout<<"parse index data error"<<endl;
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

bool analysis_ctrl::save_index(char* index_data , int len ,original_index& index)
{
    if( index_data == NULL || len == 0)
        return false;
    cout<<len<<" "<<strlen(index_data)<<endl;
    int pos = 0;
    int offset_val =0;
    while(pos < len)
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
        index.put(get_new_doc_id(),(host+sub_url).c_str(), offset_val,len_val);
        offset_val+=len_val;
        
    }
    return true;
}

bool analysis_ctrl::parse_data(char* html_data, int len, original_index& index)
{
    original_index_content index_val;
    int index_id =0;

    index.set_to_start();
    index.get_next(index_id ,index_val);
    while(index.get_next(index_id ,index_val))
    {
      
        cout<<"parsing: "<<index_id<<" => "<<index_val.url<<":"<<index_val.offset<<":"<<index_val.len<<endl;

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
            //save pool
            save_data(pool );
        }
       
        
        free(pool);

       
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
}

int analysis_ctrl::get_new_doc_id()
{
    return _doc_id++;
}



