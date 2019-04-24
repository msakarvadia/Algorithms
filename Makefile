CC = gcc
CFLAGS = -g -Wall -Wextra -std=gnu99            
LDFLAGS = -lm
binaryHeapPriorityQueue: binaryHeapPriorityQueue.o 
	${CC} ${CFLAGS} binaryHeapPriorityQueue.o ${LDFLAGS} -o binaryHeapPriorityQueue 
open_addressing_hash: open_addressing_hash.o
	${CC} ${CFLAGS} open_addressing_hash.o ${LDFLAGS} -o open_addressing_hash
sepChain_Hash: sepChain_Hash.o
	${CC} ${CFLAGS} sepChain_Hash.o ${LDFLAGS} -o sepChain_Hash
test: test.o
	${CC} ${CFLAGS} test.o ${LDFLAGS} -o test
merge_sort: merge_sort.o
	${CC} ${CFLAGS} merge_sort.o ${LDFLAGS} -o merge_sort
neural_net: neural_net.o
	${CC} ${CFLAGS} neural_net.o ${LDFLAGS} -o neural_net
quicksort: quicksort.o
	${CC} ${CFLAGS} quicksort.o ${LDFLAGS} -o quicksort
rubiks: rubiks.o
	${CC} ${CFLAGS} rubiks.o ${LDFLAGS} -o rubiks
