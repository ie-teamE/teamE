#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int id;
  int i, s, sum=0;

  s = atoi(argv[1]);

  #pragma omp parallel private(id)
  {
    id = omp_get_thread_num();

    #pragma omp for private(i)
    for(i=1; i<=s; ++i) {
      sum = sum + i;
      //printf("thread %d sum = %d\n", id, sum);
    }

    #pragma omp master
    printf("Final sum = %d\n", sum);
  }

  return(0);
}
