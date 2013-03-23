//============================================================================
// Name        : 4ops.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream.h>
#include <map>
using namespace std;

typedef struct {int filenum; int offset;} inf;

int main() {
	std::string file="";
	char filename[50]={0};
	int index_num = 4;
	printf("bye");
	map<int,inf>mapindex;
	for(int i=0; i<index_num; i++){
	sprintf (filename, "index%d", i);
	file = file + filename;
	ifstream myFile (file.c_str(), ios::in | ios::binary);
	int index,filenum,offset;
	char tmp[4];
	while(myFile.peek()!=EOF){
	myFile.read(tmp,sizeof(int));
	memcpy(&index, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&filenum, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&offset, tmp, sizeof(int));
	inf inf1 = {filenum,offset};
	mapindex.insert(pair<int, inf>(index,inf1));
	}
//	int a;
//	printf("%s\n",file.c_str());
//	cin>>a;
//	file = "";
	}
	for ( map<int, inf>::iterator it = mapindex.begin(); it!=mapindex.end(); ++it)
			cout << it->first << " => " << it->second.filenum << " => " << it->second.offset << '\n';
	return 0;
}
