#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int update(int, int, int);
int n=30;

int main(int argc, char *argv[]) {

  int numtasks, taskid, len, i, chunksize, offset, mysum, sum;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  double Stime, Etime;

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Get_processor_name(hostname, &len);

  chunksize = n/numtasks;

  if(taskid == MASTER) {

    offset = chunksize*taskid;
    mysum = update(offset, chunksize, taskid);

    MPI_Reduce(&mysum, &sum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
    printf("Final sum = %d\n", sum);
  }

  if(taskid>MASTER) {
    offset = chunksize*taskid;
    mysum = update(offset, chunksize, taskid);

    MPI_Reduce(&mysum, &sum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return(0);
}

int update(int myoffset, int chunk, int myid) {
  int i, mysum;
  mysum = 0;

  for(i=myoffset; i < myoffset+chunk; i++) {
    mysum = mysum + i;
  }
  printf("Task %d mysum = %d\n", myid, mysum);
  return(mysum);
}
