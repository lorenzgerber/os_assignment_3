/*
 * Benchmarking tool for Linux Schedulers
 * Lorenz Gerber, October 2017
 * GPLv3
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include "timer.h"
#define NUMBER_THREADS 20

// per thread time keeping struct
typedef struct per_thread_time {
  double wall_t_create;
  double wall_t_run;
  double wall_t_finish;
} per_thread_time;

/* Global variables */
void *Pth_empty(void* thread_data);
int array_lengths[NUMBER_THREADS];
char *data_arrays[NUMBER_THREADS];
char *operation[NUMBER_THREADS];
char *read_write[2] = {"w","r"};
char*op;
struct per_thread_time thread_time [NUMBER_THREADS];

char *file_names[20] = {"test0.txt",
			"test1.txt",
			"test2.txt",
			"test3.txt",
			"test4.txt",
			"test5.txt",
			"test6.txt",
			"test7.txt",
			"test8.txt",
			"test9.txt",
			"test10.txt",
			"test11.txt",
			"test12.txt",
			"test13.txt",
			"test14.txt",
			"test15.txt",
			"test16.txt",
			"test17.txt",
			"test18.txt",
			"test19.txt"};


int main(int argc, char* argv[]) {

  /* local variables */
  long       thread;
  pthread_t* thread_handles;
  double start, finish;
  int array_size_large = 10000000;
  int array_size_small = 100;
  int retVal = 0;

  

  thread_handles = malloc(NUMBER_THREADS*sizeof(pthread_t));

  // Create data arrays
  int rank[NUMBER_THREADS];
  for(int i = 0; i < NUMBER_THREADS; i++){
    rank[i] = i;
  }

  for(int i = 0; i < NUMBER_THREADS; i++){
    if (i < NUMBER_THREADS/2){
      array_lengths[i] = array_size_small;
    } else {
      array_lengths[i] = array_size_large;
    }

    if (i < NUMBER_THREADS/2){
	op = read_write[0];
    } else {
	op = read_write[1];
    }

    operation[i] = malloc(sizeof(char));
    operation[i] = op;

    data_arrays[i] = malloc(sizeof(char)*array_lengths[i]);
    for(int j = 0; j < array_lengths[i]; j++){
      data_arrays[i][j] = 'a';
    }
  }

  // Starting Threads
  for(thread = 0; thread < NUMBER_THREADS; thread++){
    retVal = pthread_create(&thread_handles[thread], NULL, Pth_empty, &rank[thread]);
    GET_WALL_TIME(thread_time[thread].wall_t_create);
    if (retVal){
        fprintf(stderr, "return value pthread_create: %d\n", retVal);
        exit(1);
    }
  }

  // Collecting Threads
  for(thread = 0; thread < NUMBER_THREADS; thread++){
    retVal = pthread_join(thread_handles[thread], NULL);
    if (retVal){
      fprintf(stderr, "return value pthread_join: %d\n", retVal);
      exit(1);
    }
  }

    
  for(int i = 0; i < NUMBER_THREADS; i++){
    printf("%d %d %s %e %e\n",
        array_lengths[i],
        i,
	operation[i],
        thread_time[i].wall_t_finish - thread_time[i].wall_t_run,
        thread_time[i].wall_t_finish - thread_time[i].wall_t_create);
	}

  free(thread_handles);

  for(int i = 0; i < NUMBER_THREADS; i++){
    free(data_arrays[i]);
  }

  return 0;
}

/**
 *
 * Thread function
 * Calling bubblesort and doing
 * Benchmarking
 */
void *Pth_empty(void* rank){
  int my_rank = *(int*) rank;

  GET_WALL_TIME(thread_time[my_rank].wall_t_run);
 
  FILE *fp;

  fp = fopen(file_names[my_rank], op);
  if(*op==77){
    fputs(data_arrays[my_rank], fp);
  } else {
    fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
  }
  fclose(fp);
  
  GET_WALL_TIME(thread_time[my_rank].wall_t_finish);

  return NULL;
}
