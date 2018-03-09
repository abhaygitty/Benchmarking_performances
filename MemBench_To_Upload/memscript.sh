#!/bin/sh
																																																																																																																																																																																																																																																																																														
make
echo BenchMarking for memory started

for blockSizes in 8B 8KB 8MB 80MB
do
	for threads in 1 2 4 8
	do
		./MEMORY $threads $sizes
	done
done

echo Completed Benchmarking for memory

