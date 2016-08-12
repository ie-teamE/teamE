#include <pthread.h>
#include <stdio.h>
#include <time.h>

void* thread1(void* pParam);
void* thread2(void* pParam); 
int count1=0;
int count2=0;
int count3;
int i,j;
int n=10000;

int main(int argc, char *argv[]){
  pthread_t tid1, tid2; 
  clock_t start, end;
  start = clock();
  
  pthread_create(&tid1, NULL, thread1, NULL);
  pthread_create(&tid2, NULL, thread2, NULL);
  
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  
  count3 =  count1 + count2;
  printf("total = %d",count3);
  end = clock();
  printf("\nTIME: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
  return (0);
}

/*thread１*/
void* thread1(void* pParam)
{
            for(i=0;i<n/2;i++){
      count1 = count1 + i;
      /*printf("thread1 = %d \n",count1);*/
    }
    printf("\n");
    
return (0);
}

/*thread２*/
void* thread2(void* pParam)
{
        for(j=n/2;j<n;j++){
      count2 = count2 + j;
     /* printf("thread2 = %d \n",count2);*/
    }
        return (0);
}
