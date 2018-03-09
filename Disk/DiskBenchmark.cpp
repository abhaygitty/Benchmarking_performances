/*
*This program is written by Indranil Thakur and Abhay Nagaraj. 
*THis program does the benchmarking of the disk operations' perofrmance. 
*/

//headers needed
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
// using namespace std;
//headers needed



float tp,lat;
long double tot_time;
float tp;
float lat;
long blockSize;
int no_of_threads = 4;
//method declarations
void *sequential_write_then_read(void *blockSize);
void *random_write_then_read(void *blockSize);
//method declarations

double totalOperations;
FILE *fp;


int main() {			
    string input;
	blockSize = 1024;
    int i;

    struct timeval start_time, end_time;

    pthread_t pt[no_of_threads];

	gettimeofday(&start_time, NULL);

	for(i=0;i<no_of_threads;i++){
		pthread_create(&pt[i], NULL,sequential_write_then_read, (void*)(long)blockSize);
		pthread_create(&pt[i], NULL,random_write_then_read,(void*)(long)blockSize);
	}

	for(i=0;i<no_of_threads;i++)
		pthread_join(pt[i], NULL);
	gettimeofday(&end_time, NULL);

	tot_time=((end_time.tv_sec - start_time.tv_sec) + ((double)(end_time.tv_usec - start_time.tv_usec)/1000000.0));

	tp=float(1000000000)/tot_time;
	tp=tp/1000000;

	totalOperations=1000000000/blockSize;

	lat = (tot_time /totalOperations)*1000;

	cout << "Elapsed Time:"<< tot_time <<endl<< "tp : "<<tp<<"1000000/sec"<<endl;

	fp= fopen("diskLogs.txt", "ab");

	fprintf(fp,"Sequential Write with BlockSize of %d and thread %d : ms %f",blockSize,no_of_threads,lat);

	cout << "lat in Seconds: "<< lat<<endl;
    return 0;
}

void *sequential_write_then_read(void *blockSize)
{
    int bsze=(int)(long)blockSize;
    int fileOpenReturnVal;
    fileOpenReturnVal=open("test.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    
	//sequential write
    for(int i=0;i<1000000000/bsze;i++){
        char *chPointer = new char[bsze];
        memset(chPointer,'1',bsze);
        write(fileOpenReturnVal,b,bsze);
    }
	//closing the file
    close(fileOpenReturnVal);
	
	//sequential reading of the same file after writing into it
    fileOpenReturnVal=open("test.txt", O_RDONLY, 0666);
	int loopLimit = (1000000000/bsze);
    for(int i=0;i<loopLimit;i++)
    {
        char *chrPointer= new char[bsze];
        read(fileOpenReturnVal,chrPointer,bsze);
    }
	close(fileOpenReturnVal);
}

void *random_write_then_read(void *blockSize){
    int bsze=(int)(long)blockSize;
    
    returnVal=open("test.txt",O_CREAT|O_TRUNC|O_WRONLY, 0666);
    int i, returnVal, r;
	//random write into the disk    
    for(i=0;i<1000000000/bsze;i++)
    {
        r = rand()%(1000000000/bsze);
        char *b = new char[bsze];
        memset(b,'0',bsze);
        lseek(returnVal,r*bsze,SEEK_SET);
        write(returnVal);
    }
    close(returnVal);
	
	//random read followed by random write
    returnVal=open("testfile.txt", O_RDONLY, 0666);
    
    for(i=0;i<1000000000/bsze;i++)
    {
        r = rand()%(1000000000/bsze);
        lseek(returnVal,r*bsze,SEEK_SET);
        char *b = new char[bsze];
        read(returnVal,b,bsze);
    }
    close(returnVal);
}