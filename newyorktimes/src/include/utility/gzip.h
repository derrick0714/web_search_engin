#ifndef __GZIP_H__
#define __GZIP_H__


class gzip
{
public:
	gzip();
	~gzip();
public:
	static char* uncompress_from_file(const char* file_name, int size, int& already_len );
	static bool compress_to_file(const char* file_name, char* data, int len);

};


#endif //__GZIP_H__