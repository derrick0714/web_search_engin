/*
 * heap.h
 *
 *  Created on: Mar 6, 2013
 *      Author: Adam57
 */

#ifndef HEAP_H_
#define HEAP_H_
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include "StreamBuffer.h"
//#ifdef __APPLE__
#  define off64_t off_t
#  define fopen64 fopen
//#endif
using namespace std;

  static int lastwordid = -1;
  static int lastdocid = -1;
  static int lastfilenum = -1;
  static int lastoffset = -1;
  static int doc_num = 1;
  static int freq = 1;
  static list<int> mylist;

/* data structure for one input/output buffer */
typedef struct {FILE *f; char* buf; int curRec; int numRec;} buffer;
typedef struct {int *arr; char *cache; int size; } heapStruct;
//Compare the word ID part
#define WORD(z) (*(int *)(&(heap.cache[heap.arr[(z)]*recSize])))
//Compare the doc ID part
#define DOC(z) (*(int *)(&(heap.cache[heap.arr[(z)]*recSize+sizeof(int)])))

buffer *ioBufs;          /* array of structures for in/output buffers */
heapStruct heap;         /* heap structure */
int recSize;             /* size of record (in bytes) */
int bufSize;             /* # of records that fit in each buffer */

/* standard heapify on node i. Note that minimum is node 1. */
void heapify(int i)

{
  int s, t;

  s = i;
  while(1)
  {
    /* find minimum key value of current node and its two children */
    if (((i<<1) <= heap.size) && (WORD(i<<1) < WORD(i)))  s = i<<1;
    if (((i<<1) <= heap.size) && (WORD(i<<1) == WORD(i)) && (DOC(i<<1) < DOC(i)))  s = i<<1;
    if (((i<<1)+1 <= heap.size) && (WORD((i<<1)+1) < WORD(s)))  s = (i<<1)+1;
    if (((i<<1)+1 <= heap.size) && (WORD((i<<1)+1) == WORD(s)) && (DOC((i<<1)+1) < DOC(s)))  s = (i<<1)+1;


    /* if current is minimum, then done. Else swap with child and go down */
    if (s == i)  break;
    t = heap.arr[i];
    heap.arr[i] = heap.arr[s];
    heap.arr[s] = t;
    i = s;
  }
}


/* get next record from input file into heap cache; return -1 if EOF */
int nextRecord(int i)

{
  buffer *b = &(ioBufs[i]);

  /* if buffer consumed, try to refill buffer with data */
  if (b->curRec == b->numRec)
    for (b->curRec = 0, b->numRec = 0; b->numRec < bufSize; b->numRec++)
    {
      fread(&(b->buf[b->numRec*recSize]), recSize, 1, b->f);
      if (feof(b->f))  break;
    }

  /* if buffer still empty, return -1; else copy next record into heap cache */
  if (b->numRec == 0)  return(-1);
  memcpy(heap.cache+i*recSize, &(b->buf[b->curRec*recSize]), recSize);
  b->curRec++;
  return(i);
}


void writeRecord(buffer *b, int i, StreamBuffer &stream, StreamBuffer &stream1)

{
  int wordid,docid,pos,j;

  /* flush buffer if needed */
  if ((i == -1) || (b->curRec == bufSize))
  {
    for (j = 0; j < b->curRec; j++) {

      /*intermidiate postings are coming in the order of increasing wordid docid and pos, divide each of them in to wordid docid pos*/
      memcpy(&wordid,&(b->buf[j*recSize]),sizeof(int));
      memcpy(&docid,&(b->buf[j*recSize])+sizeof(int),sizeof(int));
      memcpy(&pos,&(b->buf[j*recSize])+2*sizeof(int),sizeof(int));
      cout<<"#"<<j<<" wordid: "<<wordid<<" docdid: "<<docid<<" pos: "<<pos<<endl;

      /*If this is the first record coming in*/
      if(lastwordid==-1){

      lastwordid = wordid;
      lastdocid =  docid;
      lastfilenum = 0;
      lastoffset = 0;

//      fwrite(&(b->buf[j*recSize]), recSize, 1, b->f);
//      stream.write(false,&(b->buf[j*recSize]),recSize);

//      stream.write(&pos);
      mylist.push_back(pos);

      continue;
      }

      /*If this record's wordid is the same as the previous one*/
      if(wordid==lastwordid){
        if (docid == lastdocid){
        /*when docid and wordid remains the same, store all the position data in to a list*/
        freq++;

//        stream.write(&pos);
        mylist.push_back(pos);

        continue;
        }
        if (docid != lastdocid){
        doc_num++;
        /*when docid changes, write docid and freq into file*/
        stream.write(&lastdocid);
        stream.write(&freq);
        /*add all the position data belongs to this doc to the back*/
        while(!mylist.empty()){
          stream.write(&mylist.front());
          mylist.pop_front();
        }
        freq = 1;
        lastdocid = docid;
//        cout<<mylist.size()<<endl;
//        mylist.clear();

//        stream.write(&pos);
        mylist.push_back(pos);

        continue;
        }

      }

      /*If this record's wordid is different from the previous one*/
      if(wordid!=lastwordid){
        /*when wordid changes, write docid and freq into file*/
        stream.write(&lastdocid);
        stream.write(&freq);
        /*add all the position data belongs to this doc to the back*/
        while(!mylist.empty()){
          stream.write(&mylist.front());
          mylist.pop_front();
        }

        /*when wordid changes, write last word's info into index table*/
        /*here we need to do sth with the last incoming posting to write the last word*/
        stream1.write(&lastwordid);
        stream1.write(&doc_num);
        stream1.write(&lastfilenum);
        stream1.write(&lastoffset);

        freq = 1;
        doc_num = 1;
        lastwordid = wordid;
        lastdocid  = docid;
        lastfilenum = stream.get_filenum();
        lastoffset = stream.get_offset();
//          cout<<mylist.size()<<endl;
//          mylist.clear();

//          stream.write(&pos);
          mylist.push_back(pos);

      }
//      fwrite(&(b->buf[j*recSize]), recSize, 1, b->f);
//      stream.write(&(b->buf[j*recSize]),recSize);
    }
    b->curRec = 0;
  }

  if (i != -1)
    memcpy(&(b->buf[(b->curRec++)*recSize]), heap.cache+i*recSize, recSize);
}


#endif /* HEAP_H_ */
