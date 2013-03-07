CS 6913 Spring 2013
Web Search Engine
HomeWork 2

Xu Deng, Qi Wang

[How to run the program:]


[Filelist:]
	
	readme.txt
	makefile files
	include.models.orignal_index.h		store the orignal data from the index file corresponding to the html data
	include.models.streamBuffer.h		a buffer that stores the data can auto save to file when the data reaches a particular size
	include.models.streamBuffer.cpp		function definitions of streamBuffer
	include.models.TempleLexicon.h		intermediate posting data structure
	include.models.WordMap.cpp			use to store the word_id table and url_table
	
	include.utility.display.h			display with user input interaction for program testing
	include.utility.display.cpp			function definitions of display
	include.utility.gizp.h				implement gizp compression
	include.utility.gizp.cpp			function definitions of gizp
	
	include.parser.h					parse posting information from the raw data, adapted from the parser on the website
	include.parser.c					function definitions of parser
	
	merge.heap.h						implement the heap structure and some function definitions of heap and functions used in merge
	merge.merge.cpp						implement the merge process
	
	generating.analysis_ctrl.h			implement simultaneously reading data from index file and raw data file, generating
										data structures of word_id table url_id table and intermediate postings
	generating.analysis_ctrl.h			function definitions of analysis_ctrl
	generating.cpp						run analysis_ctrl
	
[Data Structure:]
	doc_id table						assgin each (string)url(since each url corresponds to a doc) an int id, 
										implemented by Class WordMap
										the store format in memory is int(doc_id) int(url_length) char[](url)
	word_id table 						assgin each (string)word an int id, implemented by Class WordMap
										the store format in memory is int(word_id) int(word_length) char[](word)
	intermediate posting				(int)word_id (int)doc_id (int)postion each intermediate posting takes up 12 bytes
										implemented by Class TempleLexicon
										the store format in memory is int(word_id) int(doc_id) int(postion)
										And all the intermediate postings in a particular file is ordered by word_id then doc_id then postion
	inverted index						the store format in memory is int(word id) int(file_id) int(offset)
	
	final posting lists					the store format in memory is(each element is int, taking up 4 bytes):
										(pos_1_1,pos_1_2,...,pos_1_n, doc_id1, freq), (pos_2_1,pos_2_2,...,pos_2_n, doc_id2,freq),...,
										(pos_m_1,pos_m_2,...,pos_m_n, doc_id2, freq) this list belongs to a word, but we don't write this word into this structure, we mantain an offset and a filenum for each word to fetch this posting list whenever we need it.
[Breif Description:]
	1.Parsing Phase:					According to the index files and raw data files we generate doc_id table and word_id table
										and a set of files of intermediate postings, in each of these files, the postings is ordered as mentioned above
	2.Merge Phase:						All the intermediate postings are feed into the merge module, according to the file numbers 
										we build a min heap of that size, everytime we extract the root of the heap, we fill in another intermediate posting from the file of the root, for each element in the heap, we build a buffer to read data from the correspondin file and another two StreamBuffer objects for writing inverted index and corresponding posting lists, in this way we implement the I/O-efficient mergesort.
										
[Special Features beyond basic requirement:]
	1. gizp compression out of main memory, uncompressed in main memory
	2. add postion info in the inverted index
	
[Statistics & Performance:]
										
	
	