#ifndef __RINGBUFFER_H__											 // header guard so the file can't be included more than once
#define __RINGBUFFER_H__
	
#include <stdio.h>												     // include for printf				 
#include <stdlib.h>													 // include standard library 
#include <stdbool.h>

// declare variables in struct
typedef struct Ringbuffer
{
	int* buff;      													  // ring buffer
	int  buffSize;                                                        // ring buffer size
	int  savedElements;                                                   // nr of times elements have been saved to ring buffer
	int  nrOfRounds;                                                      // nr of rounds around ring buffer
	int  nose;                                                            // the index with the newest information
	int  head;                                                            // the index where the new information will be saved
	int  tail;													          // the index where the oldest information resides
}ringbuffer;

// declaration of functions
void ringbuffer_init    (int buffSize, ringbuffer *a);					  // initialize the ring buffer
void ringbuffer_put     (int data_in, ringbuffer *a);					  // put data in ring buffer
int  ringbuffer_get     (ringbuffer *a);	                			  // get data from ring buffer
void ringbuffer_empty   (ringbuffer *a);							      // empty the buffer
void calc_variables	    (ringbuffer *a);								  // recalculate the variables
void ringbuffer_print   (ringbuffer* a);								  // print the buffer for debug
void ringbuffer_printvar(ringbuffer* a);                                  // print info about the variables for debug
 
#endif
 