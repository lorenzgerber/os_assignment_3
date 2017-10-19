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
struct per_thread_time thread_time [NUMBER_THREADS];

/*
 * generic bubble_sort
 * used as compute work task
 */



int main(int argc, char* argv[]) {

  /* local variables */
  long       thread;
  pthread_t* thread_handles;
  double start, finish;
  int array_size_large = 100000000;
  int array_size_small = 100;
  int retVal = 0;

  thread_handles = malloc(NUMBER_THREADS*sizeof(pthread_t));

  // Create data arrays
  int rank[NUMBER_THREADS];
  for(int i = 0; i < NUMBER_THREADS; i++){
    rank[i] = i;
  }

  for(int i = 0; i < NUMBER_THREADS; i++){
    if (i > NUMBER_THREADS/2){
      array_lengths[i] = array_size_small;
    } else {
      array_lengths[i] = array_size_large;
    }

    data_arrays[i] = malloc(sizeof(char)*array_lengths[i]);
    for(int j = 0; j < array_lengths[i]; j++){
      data_arrays[i][j] = 'a';
    }
  }




  // Time stamp for total runtime
  GET_WALL_TIME(start);

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

  // Time stamp for total runtime
  GET_WALL_TIME(finish);

  // data output to stdout:
  // CPU time, Wall time, Wall time create until run, wall time run until finish

  for(int i = 0; i < NUMBER_THREADS; i++){
    printf("%d %d %e %e\n",
        array_lengths[i],
        i,
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

  char* write = "w";
  char* read = "r";
  char* append = "a";


  FILE *fp;

  if(my_rank == 0){
    fp = fopen("test0.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 1){
    fp = fopen("test1.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 2){
    fp = fopen("test2.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 3){
    fp = fopen("test3.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 4){
    fp = fopen("test4.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 5){
    fp = fopen("test5.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 6){
    fp = fopen("test6.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 7){
    fp = fopen("test7.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 8){
    fp = fopen("test8.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 9){
    fp = fopen("test9.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 10){
    fp = fopen("test10.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 11){
    fp = fopen("test11.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 12){
    fp = fopen("test12.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 13){
    fp = fopen("test13.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 14){
    fp = fopen("test14.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 15){
    fp = fopen("test15.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 16){
    fp = fopen("test16.txt", "w");
    fputs(data_arrays[my_rank], fp);
    //fgets(data_arrays[my_rank], array_lengths[my_rank], fp );
    fclose(fp);
  }

  if(my_rank == 17){
    fp = fopen("test17.txt", "w");
    fputs(data_arrays[my_rank], fp);
    fclose(fp);
  }

  if(my_rank == 18){
    fp = fopen("test18.txt", "w");
    fputs(data_arrays[my_rank], fp);
    fclose(fp);
  }

  if(my_rank == 19){
    fp = fopen("test19.txt", "w");
    fputs(data_arrays[my_rank], fp);
    fclose(fp);
  }


  GET_WALL_TIME(thread_time[my_rank].wall_t_finish);


  return NULL;
}
