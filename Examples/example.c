#include "ringbuffer.h"
//#define true  1						
//#define false 0

const int BUFFER_SIZE  = 5;		    // change the buffer size of ringbuf
const int nrOfData1    = 6;		    // change to simulate the amount of "received" data
const int getData1     = 5;			// how many "datas" to get


int main(void)
{
	// make instance
	ringbuffer* buff1 = malloc(sizeof(ringbuffer));

	// initialize ring buffer
	ringbuffer_init(BUFFER_SIZE, buff1);

	// put data in buffer
	for (int i = 0; i < nrOfData1; i++)
		ringbuffer_put(i + 1, buff1);

	// print the buffer values
	ringbuffer_print(buff1);
	ringbuffer_printvar(buff1);

	// get data from ring buffer
	printf("\n<Get> %d\n", ringbuffer_get(buff1));
	printf("\n<Get> %d\n", ringbuffer_get(buff1));
	ringbuffer_print(buff1);
	ringbuffer_printvar(buff1);

	// put data on ring buffer
	ringbuffer_put(150, buff1);
	printf("\n<put data in buffer!>\n");
	ringbuffer_print(buff1);
	ringbuffer_printvar(buff1);

	// get from buffer
	printf("\n<Get> %d\n", ringbuffer_get(buff1));

	// free the buffer memory
	free(buff1);

	while(true){}

	return 0;
}