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
#include "StreamBuffer.h"
#ifdef __APPLE__
#  define off64_t off_t
#  define fopen64 fopen
#endif



/* data structure for one input/output buffer */
typedef struct {FILE *f; char* buf; int curRec; int numRec;} buffer;
typedef struct {int *arr; char *cache; int size; } heapStruct;
#define WORD(z) (*(int *)(&(heap.cache[heap.arr[(z)]*recSize])))
#define DOC(z) (*(int *)(&(heap.cache[heap.arr[(z)]*recSize+sizeof(int)])))

buffer *ioBufs;          /* array of structures for in/output buffers */
heapStruct heap;         /* heap structure */
int recSize;             /* size of record (in bytes) */
int bufSize;             /* # of records that fit in each buffer */


/*************************************************************************/
/* mergephase.c implements the merge phase of an I/O-efficient mergesort */
/*      It is assumed that the first 4 bytes of each record contain an   */
/*      integer key by which sorting occurs, and that records are of a   */
/*      fixed size that is a multiple of 4 bytes. It reads the names of  */
/*      the files that have to be merged from a file, and then merges    */
/*      each group of up to d consecutive files into one, where d is     */
/*      given as part of the command line input. Output files again have */
/*      filenames created by adding a running number to a given prefix,  */
/*      and the list of these filenames is written to another file.      */
/*                                                                       */
/* usage:  ./mergephase recsize memsize finlist outfileprefix foutlist   */
/*             where                                                     */
/*               recsize:  size of a record in bytes - must be mult(4)   */
/*               memsize:  size of available memory in bytes             */
/*               degree:   merge degree d: max # files merged into one   */
/*               finlist:  name of file containing a list of input files */
/*               outfileprefix:  prefix (including path and name) used   */
/*                               to generate numbered temp output files  */
/*               foutlist:  file to which names of temp files written    */
/*************************************************************************/


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


/* copy i-th record from heap cache to out buffer; write to disk if full */
/* If i==-1, then out buffer is just flushed to disk (must be last call) */
void writeRecord(buffer *b, int i, StreamBuffer &stream, StreamBuffer &stream1)

{
	int wordid,docid;
	int lastwordid = -1;
	int lastdocid = -1;
	int filenum = 0;
	int offset = 0;
	int freq=1;
    int j;

  /* flush buffer if needed */
  if ((i == -1) || (b->curRec == bufSize))
  {
    for (j = 0; j < b->curRec; j++) {

    	memcpy(&wordid,&(b->buf[j*recSize]),sizeof(int));
    	memcpy(&docid,&(b->buf[j*recSize])+sizeof(int),sizeof(int));
    	cout<<"#"<<j<<" wordid: "<<wordid<<" docdid: "<<docid<<endl;
    	if(lastwordid==-1){
    	lastwordid = wordid;
    	lastdocid =  docid;
    	stream1.write(&wordid);
    	stream1.write(&filenum);
    	stream1.write(&offset);
//      fwrite(&(b->buf[j*recSize]), recSize, 1, b->f);
//      stream.write(false,&(b->buf[j*recSize]),recSize);
    	continue;
    	}

    	if(wordid==lastwordid){
    		if (docid == lastdocid){
    		freq++;
    		continue;
    		}
    		if (docid != lastdocid){
    		stream.write(&lastdocid);
    		stream.write(&freq);
    		freq = 1;
    		lastdocid = docid;
    		continue;
    		}

    	}

    	if(wordid!=lastwordid){
    		stream.write(&lastdocid);
    		stream.write(&freq);
    		filenum = stream.get_filenum();
    		offset  = stream.get_offset();
    		stream1.write(&wordid);
    		stream1.write(&filenum);
    		stream1.write(&offset);
    	    freq = 1;
    	    lastwordid = wordid;
    	    lastdocid  = docid;
    	}

//      fwrite(&(b->buf[j*recSize]), recSize, 1, b->f);
//    	stream.write(&(b->buf[j*recSize]),recSize);
    }
    b->curRec = 0;
  }

  if (i != -1)
    memcpy(&(b->buf[(b->curRec++)*recSize]), heap.cache+i*recSize, recSize);
}


#endif /* HEAP_H_ */
