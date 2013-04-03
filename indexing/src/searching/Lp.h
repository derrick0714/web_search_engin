/*
 * Lp.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Adam57
 */

#ifndef __LP_H_
#define __LP_H_
#include<string.h>
#include<vector>
#include<string>
#include<map>
using namespace std;
#define MAXDID 100000000;
#define FILESIZE 1200000;
typedef struct {int chunk_last_wordid; int chunk_last_docid; int filenum; int offset;} chunk;
typedef struct {int doc_num; int chunk_num; int posting_num;} word_inf;
typedef struct {int wordid; int docid; int freq;} posting;

class Lp {

//private:
//	string word;
//	int    word_id;
//	int    start_chunk;
//	int    end_chunk;
//	int    start_posting_num;
//	int    end_posting_num;
//	int    doc_num;
//	FILE*  start_file;
//	int    file_offset;

public:
	int    word_id;
	int    doc_num;
	int	   start_chunk;
	int    start_posting_num;
	int    end_posting_num;
	int    num_of_chunks;
	int    cur_posting_docid;
	int	   cur_posting_freq;
	vector <chunk> chunkvector;
};

#endif /* LP_H_ */

