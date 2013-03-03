#ifndef __GZIP_H__
#define __GZIP_H__


class gzip
{
public:
	gzip();
	~gzip();
public:
	char* uncompress_from_file(char* file_name, int size, int& already_len );

};


#endif //__GZIP_H__