#include "gzip.h"
#include <zlib.h>
#include <iostream>
using namespace std;
gzip::gzip()
{

}

gzip::~gzip()
{

}

char* gzip::uncompress_from_file(const char* file_name, int size, int& already_len )
{
	if( file_name == NULL)
		return NULL;

	gzFile *p_file;
    p_file=(gzFile *)gzopen(file_name,"r");
    if(p_file == NULL)
    {	
    	cout<<"gzip::uncompress - open file fail -"<<endl;
    	return NULL;
    }
    already_len = 0;
    char *buffer=(char *)malloc(size);
    int oldSize=size;
    while (!gzeof(p_file))
    {       
        already_len+=gzread(p_file, buffer+already_len, oldSize);   
        if (already_len==size)                    // Reallocate when buffer is full
        {
            oldSize=size;
            size*=2;
            buffer=(char *)realloc(buffer,size);
        }
    }

   return buffer;
}

bool gzip::compress_to_file(const char* file_name, char* data, int len)
{
    if( file_name == NULL || data == NULL || len ==0)
        return false;
    gzFile *fi = (gzFile *)gzopen(file_name,"wb");

    if( fi == NULL)
        return false;

    gzwrite(fi, data,len);
    gzclose(fi);

}
