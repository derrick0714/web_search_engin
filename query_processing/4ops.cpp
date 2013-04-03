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
#include "4ops.h"
#include "vbyte.h"
using namespace std;

int main() {
	std::string file="result/";
	char filename[50]={0};
	int index_num = 5;
	int part1,part2,part3,part4,part5,len,test;
	char tmp[4];

	/*load word_index*/
	for(int i=0; i<index_num; i++){
	sprintf (filename, "word_index%d", i);
	file = file + filename;
	ifstream myFile (file.c_str(), ios::in | ios::binary);

	while(myFile.peek()!=EOF){
	myFile.read(tmp,sizeof(int));
	memcpy(&part1, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part2, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part3, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part4, tmp, sizeof(int));
	word_inf inf1 = {part2,part3,part4};
	word_index.insert(pair<int, word_inf>(part1,inf1));
	 }
	file="result/";
	}
	for ( map<int, word_inf>::iterator it = word_index.begin(); it!=word_index.end(); ++it)
			cout << it->first << " => " << it->second.doc_num << " => " << it->second.chunk_num << " => " << it->second.posting_num << '\n';
	printf("the size of word_index map %d\n", word_index.size());

	/*load chunk_index*/
	file="result/";
	char filename1[50]={0};
	for(int i=0; i<2; i++){
	sprintf (filename1, "chunk_index%d", i);
	file = file + filename1;
	ifstream myFile (file.c_str(), ios::in | ios::binary);

	while(myFile.peek()!=EOF){
	myFile.read(tmp,sizeof(int));
	memcpy(&part1, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part2, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part3, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part4, tmp, sizeof(int));
	myFile.read(tmp,sizeof(int));
	memcpy(&part5, tmp, sizeof(int));
	chunk chunk1 = {part2,part3,part4,part5};
	chunk_index.insert(pair<int, chunk>(part1,chunk1));
	 }
	file="result/";
	}
	for ( map<int, chunk>::iterator it = chunk_index.begin(); it!=chunk_index.end(); ++it)
			cout << it->first << " => " << it->second.chunk_last_wordid << " => " << it->second.chunk_last_docid << " => " << it->second.filenum <<" => " <<it->second.offset <<  endl;
	printf("the size of chunk_index map %d\n", chunk_index.size());

	/*load word_map*/
	file="intermediate/";
		char filename2[50]={0};
		for(int i=0; i<1; i++){
		sprintf (filename2, "word_map.data%d", i);
		file = file + filename2;
		ifstream myFile (file.c_str(), ios::in | ios::binary);

		while(myFile.peek()!=EOF){

		myFile.read(tmp,sizeof(int));
		memcpy(&len, tmp, sizeof(int));
		char tmp_buf[len+1];
		tmp_buf[len]='\0';
		myFile.read(tmp_buf,len);
		string mystring(tmp_buf);

		myFile.read(tmp,sizeof(int));
		memcpy(&part2, tmp, sizeof(int));

		word_map.insert(pair<string, int>(mystring, part2));
		 }
		file="intermediate/";
		}
		for ( map<string, int>::iterator it = word_map.begin(); it!=word_map.end(); ++it)
				cout << it->second << " => " << it->first<<endl;
		printf("the size of word_map %d\n", word_map.size());


	Lp* lptest;
	lptest = openList(5622);
	char buf[800];
	int total_len = 0;
	int n = 0;
	unsigned int res;
	unsigned char buffer[800];
	ifstream myFile4 ("result/data1", ios::in | ios::binary);
	myFile4.seekg(889874, ios::beg);
	myFile4.read(buf,692);
	memcpy(buffer, buf, 692);
		while(total_len<692){
				len = readVbyte(buffer+total_len, res);
				total_len = total_len + len;
				printf("%d res=>%d\n", n, res);
	//			cout<<"total_len: "<<total_len<<" len: "<<len<<endl;
	//			cin>>test;
				n++;
//				if(n%10==1)
//					cin>>test;
			}

	cout<<"nextGEQ: "<<nextGEQ(lptest,4168)<<endl;
	cout<<"getFreq: "<<getFreq(lptest)<<endl;
//	cout<<nextGEQ(lptest,0)<<endl;

//	//only for debuging
//    /*This part is used for testing the posting file*/
//	int n=1;
//	int wordid,docid,pos;
//	ifstream myFile1 ("intermediate/posting0", ios::in | ios::binary);
//	while(myFile1.peek()!=EOF){
//
//		myFile1.read(tmp,sizeof(int));
//		memcpy(&wordid, tmp, sizeof(int));
//		myFile1.read(tmp,sizeof(int));
//		memcpy(&docid, tmp, sizeof(int));
//		myFile1.read(tmp,sizeof(int));
//		memcpy(&pos, tmp, sizeof(int));
//		printf("%d posting=>%d=>%d=>%d\n", n,wordid, docid, pos);
//		n++;
//	}

//	/*test data*/
//	int n=1;
//	int data;
//	int a;
//	ifstream myFile2 ("result/data0", ios::in | ios::binary);
//	while(myFile2.peek()!=EOF){
//			myFile2.read(tmp,sizeof(int));
//			memcpy(&data, tmp, sizeof(int));
//			printf("%d data=>%d\n", n,data);
//			cin>>a;
//			n++;
//		}

//	/*test compressed data*/
//	int n=1;
//	unsigned int res;
//	int total_len = 0;
//	int len = 0;
//	char buf[1200000];
//	unsigned char buffer[2400000];
//	ifstream myFile2 ("result/data0", ios::in | ios::binary);
//	myFile2.read(buf,1200000);
//	memcpy(buffer, buf, 1200000);
//	ifstream myFile3 ("result/data1", ios::in | ios::binary);
//	myFile3.read(buf,1200000);
//	memcpy(buffer+1200000, buf, 1200000);
//	while(total_len<1200000){
//			len = readVbyte(buffer+total_len, res);
//			total_len = total_len + len;
//			printf("%d res=>%d\n", n, res);
////			cout<<"total_len: "<<total_len<<" len: "<<len<<endl;
////			cin>>test;
//			n++;
////			if(n%10==1)
////				cin>>test;
//		}

//	/*debug use*/
//		int a;
//		printf("%s\n",file.c_str());
//		cin>>a;
//		file = "";

	return 0;
}
