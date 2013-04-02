#include<iostream>
#include"result_ctrl.h"
using namespace std;


int main(int argc,char** argv)
{

	
	STRU_RESULT test;
	test._url="www.google.com";
	test._title="This is title";
	test._round_text="Search the world's information, including webpages, images, videos and more. Google has many special features to help you find exactly what you're looking";

	ResultCrtl demo;

	for(int i = 0; i < 10;i++)
	{
		test._bm25 = float(i);
		demo.add_one(test);
	}
	demo.print();
	return 0;
}