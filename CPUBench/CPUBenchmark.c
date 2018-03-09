/*
This program is written by Indranil Thakur and Abhay Nagaraj.
This program performs CPU benchmarking where we use strong scaling to test the system.
*/

//header inclusions//
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<pthread.h>
#include <math.h>
#include <sys/time.h>
//header inclusions//

//variable declarations
int i;
struct timeval start,end;
double start_time, end_time, total_time;
//variable declarations

//function declarations
void integerMultiThreading(int);
void floatingPointMultiThreading(int);
void *integerOperations();
void *floatPointOperations();
//function declarations

//program entry point
int main(int argc,char* argv[])
{	
	int numThreads =atoi(argv[1]) ;
	printf("Thread num %d :\n",numThreads);
	integerMultiThreading(numThreads);
	floatingPointMultiThreading(numThreads);
	return 0;
}

//floating point operation threads generated and joined
void floatingPointMultiThreading(int numThreads)
{
	pthread_t tID[numThreads];
	printf("CPU Benchmarking for FLOPS using %d threads\n",numThreads);
	int i;
	gettimeofday(&start, NULL);
	start_time = start.tv_sec+(start.tv_usec/1000000.0);
	for(i=0;i<numThreads;i++)
		pthread_create(&tID[i],NULL,floatPointOperations,NULL);
	for(i=0;i<numThreads;i++)
		pthread_join(tID[i],NULL);
	gettimeofday(&end, NULL);
	end_time = end.tv_sec+(end.tv_usec/1000000.0);	
	total_time = (end_time-start_time);
	printf("GFLOPS : %lf\n",((15*numThreads)/total_time));
}

//integer point operation threads generated and joined
void integerMultiThreading(int numThreads)
{
	pthread_t tID[numThreads];
	printf(" CPU Benchmarking for IOPS using %d threads\n",numThreads);
	int i;
	gettimeofday(&start, NULL);
	start_time = start.tv_sec+(start.tv_usec/1000000.0);
	for(i=0;i<numThreads;i++){
	pthread_create(&tID[i],NULL,integerOperations,NULL);
	}
	for(i=0;i<numThreads;i++){
		pthread_join(tID[i],NULL);
	}
	gettimeofday(&end, NULL);
	end_time = end.tv_sec+(end.tv_usec/1000000.0);
	total_time = (end_time-start_time);
	printf("GIOPS : %lf\n",((15*numThreads)/total_time));
}


//reuasable function that carries out the integer operations
void *integerOperations()
{//10 Giga ops
	int i,j;
	for(i=0;i < 100000;i++)
	{
		for(j=0;j < 10000;j++)
		{
			10*21/36*81;
			23*100-250*2;
			38+600*11-25;
			45*27/13*11;
			87/2*95*12;
		}
	}
	pthread_exit(NULL);
}

//reuasable function that carries out the floating point operations
void *floatPointOperations()
{//10 Giga ops
	int i,j;
	for(i=0;i < 100000;i++)
	{
		for(j=0;j < 10000;j++)
		{
			10.5f*21.3f/36.3f*81.2f;
			23.4f*100.8f-250.6f*2.3f;
			38.9f+600.7f*11.4f-25.6f;
			45.3f*27.7f/13.4f*11.6f;
			87.9f/2.2f*95.2f*12.6f;
		}
	}
	pthread_exit(NULL);
}