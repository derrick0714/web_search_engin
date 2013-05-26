#include "path_finder.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

using namespace std;
static int DAYS[12]={31,28,31,30,31,30,31,31,30,31,30,31};
PathFinder::PathFinder()
{
	now_year = 1987;
	end_year = 2007;
	now_month = 1;
	now_day = 1;
	load_folder();
}

PathFinder::~PathFinder()
{

}

void PathFinder::load_folder()
{
	while( now_year <= end_year)
	{	
		char path_now[255];
		sprintf( path_now, "./data/%d/%02d/%02d",now_year,now_month, now_day);
		//cout<<"folder:"<<path_now<<endl;
		add_files(path_now);

		now_day++;
		if(now_day > DAYS[now_month-1])
		{
			now_day = 1;
			now_month++;
		}
		if(now_month > 12)
		{
			now_month=1;
			now_year++;
		}
	}
	
}

int PathFinder::add_files(string dir)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) 
    {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) 
    {
    	string tmpName = string(dirp->d_name);
  		//cout<<tmpName<<endl;

    	if( tmpName != "." && tmpName != "..")
    	{
    		STRU_PATH path;
    		path.name = tmpName;
    		path.path = dir+"/"+tmpName;
       		_files.push_back( path );
       	}
    }
    closedir(dp);
    return 0;
}

bool PathFinder::get_next_file(std::string& file_name, std::string& file_path)
{
	if(_files.size() == 0)
		return false;

	file_path = _files.front().path;
	file_name = _files.front().name;
	
	_files.pop_front();
	return true;
}
