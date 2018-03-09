/*
*Done by Indranil Thakur and Abhay Nagaraj
*The program is used to benchmard the memory read write accesses of the system it runs on. 
*Being used to benchmark the chameleon cloud instances for the Cloud computing CS55 assignment
*/

//headers to be imported//
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
//headers to be imported//

//method declarations
void* sequential_memory_access();
void* random_memory_access();
void* seq_mem();
void* ran_mem();
void* startTime();
//method declarations

//500 MB memory space allocated
long int total_memory_space_allocated = 1024*1024*1000;
long int blockSize = 0;
struct timeval st, et;
																																																																																																																																																																																																																																																																			
int main(int argc, char *argv[])
{
	int num_Threads = atoi(argv[1]);//atoi converts string to integer 
    char* input_block_size = argv[2];
	
	pthread_t threads[num_Threads];

	//checking the block sizes to be used for hte iteration
	if(strcmp(input_block_size,"8B")==0)
		blockSize = 8;
	else if(strcmp(input_block_size,"8KB")==0)
		blockSize = (8*1024);
	else if(strcmp(input_block_size,"8MB")==0)
		blockSize = (8*1024*1024);
	else if(strcmp(input_block_size, "80MB") == 0)
		blockSize = (80*1024*1024);
	//checking the block sizes to be used for hte iteration
	
	//time variables
	double stime;
	double etime;
	double ttime;
	//time variables
	
	//loop variables
	int i;
	int j;
	//loop variables
	
	printf("Memory benchmarking for ***%s*** with %d threads\n",argv[2],num_Threads);
	seq_mem();
	ran_mem();
	
	return 0;
}

void* startTime()
{
	stime = st.tv_sec+(st.tv_usec/1000000.0);//start time computed with Microsecond precision
}

void* seq_mem()
{
	gettimeofday(&st, NULL);//get current time stamp
	startTime();
    
	//threads being created but not started yet
	for(i=0; i<num_Threads; i++)
	{
		//ptherad_create(threadID, NUll , routine ot be executed by the thread, could be a void cher pointer)
		pthread_create(&threads[i],NULL,sequential_memory_access, NULL);
	}
	
	//invoking join on each of the threads created
	for(j=0; j<num_Threads; j++)
	{
		pthread_join(threads[j],NULL);
	}
	
	//record the end time of the oprations carried out
	gettimeofday(&et, NULL);
	//end time in microseconds
	etime = et.tv_sec+(et.tv_usec/1000000.0);
	ttime = (etime-stime);
	long int tot_memory = num_Threads*total_memory_space_allocated;
	long int denominator = tot_memory*blockSize;
	
	//printing the outputs to the conosle
	printf("Latency is: %0.1f ms\n", (ttime*1000)/(denominator));
	printf("Throughput is: %lf MBPS\n", ((tot_memory)/ttime)/(1024*1024));
	printf("Time elapsed: %lf\n", ttime);
}

void* ran_mem()
{
	
	gettimeofday(&st, NULL);
	startTime();
	for(i=0; i<num_Threads; i++)
	{
		pthread_create(&threads[i],NULL,random_memory_access, NULL);
	}
	for(j=0; j<num_Threads; j++)
	{
		pthread_join(threads[j],NULL);
	}
	
	//record the current time
	gettimeofday(&et, NULL);
	//end time in microseconds
	etime = et.tv_sec+(et.tv_usec/1000000.0);
	//total time
	ttime = (etime-stime);
	
	long int tot_memory = num_Threads*total_memory_space_allocated;
	long int denominator = tot_memory*blockSize;
	//printing the outputs to the conosle
	printf("Latency is: %0.1f\n",(ttime*1000)/(denominator));
	printf("Throughput is: %lf\n",((tot_memory)/ttime)/(1024*1024));
	printf("Time taken: %lf\n",ttime);
	
}
void* sequential_memory_access()
{
	long int block_length = blockSize;
	int no_of_blocks = total_memory_space_allocated/block_length;
	int i=0;
	
	long int j;
	char *TotalMemoryBlockPointer = (char*)malloc(total_memory_space_allocated*sizeof(char));
	char *BlockSizeMemoryPointer = (char*)malloc(block_length*sizeof(char));
	
	memset(TotalMemoryBlockPointer,'s',block_length*sizeof(char));
	int skip_distance = 0;
	for(j =0; j<(1024*1024*1024); j++)
	while(i < no_of_blocks)
	{
		memset(TotalMemoryBlockPointer+skip_distance,'t',no_of_blocks);
		memcpy(BlockSizeMemoryPointer,TotalMemoryBlockPointer+skip_distance,block_length);
		//increment for every block of memory operated with
		i++;
		//hop the pointer for the next iteration to the next block of memory
		skip_distance+=block_length;
	}
	
	//release the memory blocks 
	free(TotalMemoryBlockPointer);
	free(BlockSizeMemoryPointer);
	//release the memory blocks 
	
	//exit the threads
	pthread_exit(NULL);
	//exit the threads
}

void* random_memory_access()
{
	long int block_length = blockSize;
	//printf("%d",block_length);
	int no_of_blocks = total_memory_space_allocated/block_length;
	int i=0, skip_distance = 0, ran_loc=0;
	long int j;
	char *ranBlock1 = (char*)malloc(total_memory_space_allocated*sizeof(char));
	char *ranBlock2 = (char*)malloc(block_length*sizeof(char));
	
	while(i < no_of_blocks)
	{
		ran_loc = rand()%(total_memory_space_allocated/block_length);
		memset(ranBlock1+ran_loc,'t',no_of_blocks);
		memcpy(ranBlock2,ranBlock1+ran_loc,block_length);
		i++;
	}
	
	//release the memory blocks 
	free(ranBlock1);
	free(ranBlock2);
	//release the memory blocks 
	
	//exit the threads
	pthread_exit(NULL);
	//exit the threads
}
