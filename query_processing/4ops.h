/*
 * 4ops.h
 *
 *  Created on: Mar 24, 2013
 *      Author: Adam57
 */

/**/
#include "Lp.h"
#include "vbyte.h"
using namespace std;

Lp* openList(int wordid){
   Lp* mylp = new Lp;
   chunk mychunk;
   mylp->word_id = wordid;
   mylp->doc_num = word_index[wordid].doc_num;
   mylp->start_chunk = word_index[wordid].chunk_num;
   mylp->start_posting_num = word_index[wordid].posting_num;
   mylp->end_posting_num = word_index[wordid+1].posting_num-1;
   mylp->cur_posting_docid = mylp->start_posting_num;
   mylp->num_of_chunks = word_index[wordid+1].chunk_num - word_index[wordid].chunk_num+1;
   int chunk_num = word_index[wordid].chunk_num;
   for (int i=0;i<mylp->num_of_chunks;i++){
	   mychunk.chunk_last_docid = chunk_index[chunk_num+i].chunk_last_docid;
	   mychunk.chunk_last_wordid = chunk_index[chunk_num+i].chunk_last_wordid;
	   mychunk.filenum = chunk_index[chunk_num+i].filenum;
	   mychunk.offset = chunk_index[chunk_num+i].offset;
	   mylp->chunkvector.push_back(mychunk);
   }
   cout<<"word_id: "<<mylp->word_id<<endl;
   cout<<"doc_num: "<<mylp->doc_num<<endl;
   cout<<"start_chunk: "<<mylp->start_chunk<<endl;
   cout<<"start_posting_num: "<<mylp->start_posting_num<<endl;
   cout<<"end_posting_num: "<<mylp->end_posting_num<<endl;
   cout<<"cur_posting: "<<mylp->cur_posting_docid<<endl;
   cout<<"num_of_chunks: "<<mylp->num_of_chunks<<endl;
   cout<<"size of chunkvector: "<<mylp->chunkvector.size()<<endl;
   for(int s = 0; s<mylp->chunkvector.size(); s++){
   cout<<"chunk_id: "<<mylp->start_chunk+s<<" chunk_last_wordid: "<<mylp->chunkvector.at(s).chunk_last_wordid<<" chunk_last_docid: "<<mylp->chunkvector.at(s).chunk_last_docid<<" filenum: "<<mylp->chunkvector.at(s).filenum<<" offset: "<<mylp->chunkvector.at(s).offset<< " chunk_size: "<<chunk_index[mylp->start_chunk+s+1].offset-chunk_index[mylp->start_chunk+s].offset<<endl;
   }
   return mylp;
}

void closeList(Lp* mylp){
	delete mylp;
}

int nextGEQ(Lp* mylp, int search_docid){
	int docid = 0;
	int start_chunk_num;
	int start_posting_num = 1;
	int end_posting_num = 128;
	int posting_num = 1;
	int filenum;
	int offset;
	int i;
	int chunk_size;
	int total_len = 0;
	int len = 0;
	int n;
	int test;
	unsigned int res1;
	unsigned int res2;
	unsigned int res3;
	unsigned int* res_arr;
	int last_docid = 0;
	string file="result/";
	char filename[50]={0};
	char* chunk;
	unsigned char* uchunk;

	start_chunk_num = mylp->start_chunk;

	for (i=0; i< mylp->num_of_chunks-1;i++){
		if(mylp->chunkvector.at(i).chunk_last_docid>=search_docid){
			start_chunk_num = mylp->start_chunk + i;
			break;
		}
		end_posting_num = mylp->end_posting_num;
		start_chunk_num = mylp->start_chunk + i;
	}
		start_posting_num = mylp->start_posting_num;

		if(chunk_index[start_chunk_num].filenum == chunk_index[start_chunk_num+1].filenum){
			chunk_size = chunk_index[start_chunk_num+1].offset - chunk_index[start_chunk_num].offset;
			chunk = new char[chunk_size];
			uchunk = new unsigned char[chunk_size];
			sprintf (filename, "data%d", chunk_index[start_chunk_num].filenum);
			file = file + filename;
			ifstream myFile (file.c_str(), ios::in | ios::binary);
			myFile.seekg(chunk_index[start_chunk_num].offset, ios::beg);
			myFile.read(chunk,chunk_size);
			memcpy(uchunk, chunk, chunk_size);
		}

		if(chunk_index[start_chunk_num].filenum < chunk_index[start_chunk_num+1].filenum){
			int num_of_files = chunk_index[start_chunk_num+1].filenum - chunk_index[start_chunk_num].filenum-1;
			chunk_size = (1200000 - chunk_index[start_chunk_num].offset) + chunk_index[start_chunk_num+1].offset + 1200000*num_of_files;
			chunk = new char[chunk_size];
			uchunk = new unsigned char[chunk_size];
			sprintf (filename, "data%d", chunk_index[start_chunk_num].filenum);
			file = file + filename;
			ifstream myFile1 (file.c_str(), ios::in | ios::binary);
			myFile1.seekg(chunk_index[start_chunk_num].offset, ios::beg);
			myFile1.read(chunk,1200000 - chunk_index[start_chunk_num].offset);
			file = "result/";
			int chunk_offset = 1200000 - chunk_index[start_chunk_num].offset;

			for(int k=0; k<num_of_files; k++){
				sprintf (filename, "data%d", chunk_index[start_chunk_num].filenum+1+k);
				file = file + filename;
				ifstream myFile2 (file.c_str(), ios::in | ios::binary);
				myFile2.read(chunk+chunk_offset,1200000);
				chunk_offset = chunk_offset + 1200000;
				file = "result/";
			}

			sprintf (filename, "data%d", chunk_index[start_chunk_num+1].filenum);
			file = file + filename;
			ifstream myFile3 (file.c_str(), ios::in | ios::binary);
			myFile3.read(chunk+chunk_offset,chunk_index[start_chunk_num+1].offset);
			chunk_offset = chunk_offset + chunk_index[start_chunk_num+1].offset;
			file = "result/";
			memcpy(uchunk, chunk, chunk_size);
		}

		cout<<"start_posting_num: "<<start_posting_num<<endl;
		cin>>test;
		while(posting_num<=128){
		 if(posting_num<start_posting_num){
		 len = readVbyte(uchunk+total_len, res1);
		 total_len = total_len + len;
		 cout<<"docid diff: "<<res1<<endl;
		 len = readVbyte(uchunk+total_len, res2);
		 total_len = total_len + len;
		 cout<<"freq: "<<res2<<endl;

		 for(int h = 0; h<res2; h++){
			 len = readVbyte(uchunk+total_len, res3);
			 total_len = total_len + len;
			 cout<<"pos diff: "<<res3<<endl;
		 }
		 }

		 if(posting_num>=start_posting_num){
			 len = readVbyte(uchunk+total_len, res1);
			 total_len = total_len + len;
			 last_docid = last_docid + res1;
			 cout<<"docid: "<<last_docid<<endl;
			 len = readVbyte(uchunk+total_len, res2);
			 total_len = total_len + len;
			 cout<<"freq: "<<res2<<endl;

			 for(int h = 0; h<res2; h++){
			 	len = readVbyte(uchunk+total_len, res3);
			 	total_len = total_len + len;
			 	cout<<"pos diff: "<<res3<<endl;
			 }

		 if (last_docid>=search_docid){
			 mylp->cur_posting_docid = last_docid;
			 mylp->cur_posting_freq = res2;
			 return mylp->cur_posting_docid;
		 }
		}
//		 res_arr = new unsigned int[res2];
		 cout<<"posting_num: "<<posting_num<<endl;
		 posting_num++;
	    }


//	filenum = chunk_index[start_chunk_num].filenum;
//	offset = chunk_index[start_chunk_num].offset;
//	cout<<"start_chunk_num: "<<start_chunk_num<<" filenum: "<<filenum<<" offset: "<<offset<<" chunk_size: "<<chunk_size<<endl;
//	return docid;

		return 100000000;
}

int getFreq(Lp* mylp){
   return mylp->cur_posting_freq;
}
