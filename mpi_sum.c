#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int update(int, int, int);
int n=75000;

int main(int argc, char *argv[]) {

  int numtasks, taskid, len, i, chunksize, offset;
  unsigned long long int mysum, sum;
  char hostname[MPI_MAX_PROCESSOR_NAME];

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Get_processor_name(hostname, &len);

  chunksize = n/numtasks;

  offset = chunksize*taskid+1;
  mysum = update(offset, chunksize, taskid);

  sum = 0;
  MPI_Reduce(&mysum, &sum, 1, MPI_UNSIGNED_LONG_LONG, MPI_SUM, MASTER, MPI_COMM_WORLD);

  if(taskid == MASTER) {
    printf("Final sum = %llu\n", sum);
  }

  MPI_Finalize();

  return(0);
}

int update(int myoffset, int chunk, int myid) {
  unsigned long long int i, mysum;
  mysum = 0;

  for(i=myoffset; i < myoffset+chunk; i++) {
    mysum = mysum + i;
  }
  printf("Task %d mysum = %llu\n", myid, mysum);
  return(mysum);
}
