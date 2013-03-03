#ifndef __MAKE_LEXICON_H__
#define __MAKE_LEXICON_H__

#include <string>
using namespace std;
class make_lexicon
{
public:
	make_lexicon(string path= "./dataset/sample.html");
	~make_lexicon();
	bool parse();

private:
	string _path;	//data_set folder 
};



#endif