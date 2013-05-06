#ifndef __PATH_FINDER_H_
#define __PATH_FINDER_H_
#include <string>
#include <deque>
#include <iostream>

class PathFinder
{
public:
	PathFinder();
	~PathFinder();
	bool get_next_file(std::string& file_path);
private:
	void load_folder();
	int  add_files(std::string dir);
private:
	int now_year;
	int now_month;
	int now_day;
	int end_year;
	std::deque<std::string> _files;
	

};

#endif //__PATH_FINDER_H_
