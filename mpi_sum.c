#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define MASTER 0

int update(int, int, int);
int data[10];

int main(int argc, char *argv[]) {

  int numtasks, taskid, len, i, chunksize, offset, mysum, sum;
  char hostname[MPI_MAX_PROCESSOR_NAME];
  double Stime, Etime;

  MPI_Status status;

  for(i=0; i<10; i++) {
    data[i] = i;
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Get_processor_name(hostname, &len);

  chunksize = 10/numtasks;

  if(taskid == MASTER) {

    offset = chunksize;

    for(i=1; i<numtasks; i++) {
      MPI_Send(&data[offset], chunksize, MPI_INT, i, 1, MPI_COMM_WORLD);
      printf("Send %d elements to task %d offset=%d\n", chunksize, i, offset);
      offset = offset + chunksize;
    }

    offset = 0;
    mysum = update(offset, chunksize, taskid);

    MPI_Reduce(&mysum, &sum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
    printf("Final sum = %d\n", sum); 
  }

  if(taskid>MASTER) {
    MPI_Recv(&data[offset], chunksize, MPI_INT, MASTER, 1, MPI_COMM_WORLD, &status);

    mysum = update(offset, chunksize, taskid);

    MPI_Reduce(&mysum, &sum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);
  }

  MPI_Finalize();

  return(0);
}

int update(int myoffset, int chunk, int myid) {
  int i, mysum;
  /* Perform addition to each of my array elements and keep my sum */
  mysum = 0;
  for(i=myoffset; i < myoffset+chunk; i++) {
    mysum = mysum + data[i];
  }
  printf("Task %d mysum = %d\n", myid, mysum);
  return(mysum);
}
