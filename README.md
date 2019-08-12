# Ring Buffer Libary written for C
 A ring buffer library for C. This library can be used when you want to save a certain amount of data and only care about the newest "x" amount of it.
 
 <img src="https://upload.wikimedia.org/wikipedia/commons/f/fd/Circular_Buffer_Animation.gif" width="500">

 ##### Table of Contents  
[Getting Started](#GettingStarted)  
[Installing](#Installing)  
[Usage](#Usage)


## Getting Started
<a name="GettingStarted"/>
get started.

## Installing
<a name="Installing"/>

Install like this.

## Usage
<a name="Usage"/> 

### Functions
* #### void ringbuffer_init (int buffSize, ringbuffer *a)
This is the initializer function for the ring buffer. Call this once in the start of the code to initalize the buffer size. 
The second parameter is the "object name" of the buffer.

* #### void ringbuffer_put (int data_in, ringbuffer *a)
Puts data into the buffer one at a time. Send the data you want to store in the buffer as the first parameter and the name of the buffer in the second. If the buffer is full, the oldest data will be overwritten.

* #### int ringbuffer_get (ringbuffer *a)
Gets data from the buffer one at a time. Will return the newest data and remove it. If ringbuffer_put() is used after ringbuffer_get(), then ringbuffer_put() will put the new data in the place where the ringbuffer_get() collected the last from.

* #### void ringbuffer_empty (ringbuffer *a)
Call this to empty the buffer. Everything will be deleted and ready to receive new data.

* #### void ringbuffer_print (ringbuffer* a)					 
Prints the ring buffer data for verification or debug purposes.

* #### void ringbuffer_printvar (ringbuffer* a)                     
Prints the relevant variables for verification or debug purposes.

### Variables
* head
* tail
* nose

### Examples
Examples.

## Contributing

If you want to contribute that's great! Send a pull request and I will review it.

## Authors

* **Marius C. K. Gulbrandsen** 

## License

This project is licensed under the GNU license - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Thanks to [Stig Thomas](https://github.com/ribbreaker) reviewing the code.
