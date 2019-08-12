#include "ringbuffer.h"											        	// include the header file


// initialize the ring buffer
void ringbuffer_init(int buff_size, ringbuffer *a)								
{
	// allocate memory to buffer
	a->buff = malloc(buff_size * sizeof(int));                  
	
    // check for errors 
	if (a->buff == NULL) 
	{												         
		fprintf(stderr, "\n<error> Error allocating memory!\n");
		exit(1);
	}

	// save buff size
	a->buffSize = buff_size;					

	// initialize with zero
	a->buff = NULL;
	a->savedElements = 0;
	a->nrOfRounds = 0;
	a->nose = 0;
	a->head = 0;

	// initialize all buffer values with zero
	for (int i = 0; i < a->buffSize; i++)
	{
		if(a->buff != NULL)		// nullpointer guard
			a->buff[i] = 0;
	}
	printf("\n<info> Ring buffer was initialized.\n\n");

	//return a->buff != NULL;
}

// put data on ring buffer
void ringbuffer_put(int data_in, ringbuffer *a)
{
	// allocte memory
	if (a->savedElements == 0)				                              // if the buffer was emptied
	{
		a->buff = malloc(a->buffSize * sizeof(int));			          // allocate memory to buffer
	}

	// put data on buffer
	if(a->buff != NULL)			                                          // check for null pointer
		a->buff[a->head] = data_in;		      				              // put data on buffer
	a->savedElements++;												      // increment saved elements 
		
	calc_variables(a);							                		  // calculate the variables for tail, head etc.
}	

// get data from ring buffer
int ringbuffer_get(ringbuffer *a)														
{
	if (a->savedElements > 0)								    			  // verify that there is actually data to get
	{	
		// recalculate the variables

		// calculate nr of rounds around ring buffer
		a->nrOfRounds = (a->savedElements - 1) / a->buffSize;                 // nr of rounds around ring buffer

		// calculate the head 
		if (a->savedElements % a->buffSize == 0)							  // if reached last element in array 
			a->head = 0;												      // head = 0
		else
			a->head = abs(a->buffSize * a->nrOfRounds - a->savedElements);    // calculate head

		// figure out the start and last index
		if (a->nrOfRounds <= 0)												  // if nr of rounds is zero ... or less (shouldn't really happen)
		{
			a->tail = 0;
			a->nose = a->savedElements - 1;                                   // the oldest information is the savedElements minus one

		}
		else                                                                  // else nrOfRounds is bigger than zero
		{
			a->tail = a->head;
			a->nose = (a->savedElements - (a->buffSize * a->nrOfRounds) - 1); // index of the oldest information is calculated
		}

		// decrement amount of elements
		a->savedElements--;

		// return the last saved data
		return a->buff[a->nose];										  
	}

	else if (a->savedElements <= 0)											  // guard against getting data when there is none
	{
		fprintf(stderr, "<Error> You used ringbuffer_get() when ring buffer had no elements saved.\n");	 // print error message to file
		return 0;												                                    	 // no data to get, exit
	}
}

// print out the ring buffer for verification
void ringbuffer_print(ringbuffer *a)
{
	//printf("\n<info> Buffer size: %d and saved elements: %d\n", a->buffSize, a->savedElements);
	//printf("\n<info> head: %d and nose: %d and tail: %d and nrOfRounds: %d \n ", a->head, a->nose, a->tail, a->nrOfRounds);
	printf("\n<info> The saved buffer values are:\n");
	

	if( (a->nrOfRounds) == 0)									// if the buffer has not yet gone around
	{
		for (int i = 0; i <= (a->nose)+1; i++)			
		{
			// print the values
			if ( (i != a->nose + 1) /*&& (i != a->nose+1 % a->buffSize)*/ )
				printf("[%i] %i", i, a->buff[i]);				// print array index and the value
			

			// add "tail", "nose", "head" labels
			if (i == 0)											// tail is always index "0" in this case
			{
				if (i == a->nose)
					printf("    tail = nose\n");
				else 
					printf("    tail\n");						// print "tail" text
			}
			else if (i == (a->nose))				        	// head is always "nose - 1" in this case
				printf("    nose\n");					        // "nose" is always one behind "head"

			else if (i == a->nose + 1)
			{
				if ((i % (a->buffSize )) == 0)
					printf("\n");
				else
				{
					printf("[%d] N/A", i);				        // print array index and the value
					printf("  head\n");
				}
					
			}
			else
				printf("\n");									// print new line for formating
		}
	}
	else if ((a->nrOfRounds) > 0)								// if the buffer has gone around 
	{
		// run loop for "buffSize" amount of times
		for (int i = 0; i < (a->buffSize); i++)
		{
			printf("[%i] %i", i, a->buff[i]);					// print array index and the value

			if (i == a->tail)									// tail 
				printf("    tail\n");							// print "tail" text
			else if (i == a->nose)							    // head is always "nose - 1" in this case
				printf("    nose\n");							// "nose" is always one behind "head"
			else
				printf("\n");									// print new line for formating
		}
	}
}

// empty the buffer
void ringbuffer_empty(ringbuffer *a)
{
	a->head          = 0;	  // reset variables
	a->tail          = 0;
	a->nose          = 0;
	a->savedElements = 0;
	a->nrOfRounds    = 0;

	free(a->buff);												          // free the allocated memory
}

// recalculate the variables
void calc_variables(ringbuffer *a)
{
	// calculate nr of rounds around ring buffer
	a->nrOfRounds = (a->savedElements - 1) / a->buffSize;                 // nr of rounds around ring buffer

	// calculate the head 
	if (a->savedElements % a->buffSize == 0)							  // if reached last element in array 
		a->head = 0;												      // head = 0
	  else
		a->head = abs(a->buffSize * a->nrOfRounds - a->savedElements);    // calculate head

	// figure out the start and last index
	if (a->nrOfRounds <= 0)												  // if nr of rounds is zero ... or less (shouldn't really happen)
	{
		a->tail = 0;
		a->nose = a->savedElements - 1;                              // the oldest information is the savedElements minus one

	}
	  else                                                                // else nrOfRounds is bigger than zero
	{
		a->tail = a->head;
		a->nose = (a->savedElements - (a->buffSize * a->nrOfRounds) - 1);    // index of the oldest information is calculated
	}
}

// this is for debug
void ringbuffer_printvar(ringbuffer* a)
{
	if(a->nrOfRounds == 0)
		printf("\n\nHead: [%d] \nTail: [%d]\nNose: [%d]\nSaved elements %d\nNumber of rounds %d\n", 
				 a->head,   a->tail,  a->nose,   a->savedElements, a->nrOfRounds);
	else if(a->nrOfRounds > 0)
		printf("\n\nHead = Tail: [%d]\nNose: [%d]\nSaved elements %d\nNumber of rounds %d\n",
			             a->tail, a->nose, a->savedElements, a->nrOfRounds);
}

void end(void)
{
}
