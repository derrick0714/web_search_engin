#include "searching_algorim.h"
using namespace std;

SearchingAlgorim::SearchingAlgorim()
{
	init_data();
}

SearchingAlgorim::~SearchingAlgorim()
{

}

void SearchingAlgorim::init_data()
{
	//read doc map
	StreamBuffer* buffer = NULL;
	if( !init_buffer_from_file("intermediate/word_map.data0",buffer))
		return;


}

bool SearchingAlgorim::init_buffer_from_file(string file_name, StreamBuffer* buffer)
{
	ifstream file (file_name.c_str() , ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		int size = file.tellg();
		char* memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();

		buffer = new StreamBuffer(size);
		buffer->read(memblock,size);
		
		delete[] memblock;
	}
	else
	{
		cout<<file_name<<" open filed"<<endl;
	}
}