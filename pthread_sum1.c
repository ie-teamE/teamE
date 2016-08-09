#include <pthread.h>
#include <stdio.h>

void* thread1(void* pParam);
void* thread2(void* pParam); 
int count1=0;
int count2;
int count3;
int i,j;
int n=30; 
pthread_mutex_t mutex; 

int main(int argc, char *argv[]){
  pthread_t tid1, tid2; 

  pthread_mutex_init(&mutex, NULL);

  pthread_create(&tid1, NULL, thread1, NULL);
  pthread_create(&tid2, NULL, thread2, NULL);
  
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);
  
  pthread_mutex_destroy(&mutex);
  count3 =  count1;
  printf("total = %d",count3);
  return 0;
}

/*スレッド１*/
void* thread1(void* pParam)
{
  /*mutex 間は他のスレッドから変数を変更できない*/
      pthread_mutex_lock(&mutex);
      for(i=0;i<n/2;i++){
      count1 = count1 + i;
      printf("thread1 = %d \n",count1);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
return 0;
}

/*スレッド２*/
void* thread2(void* pParam)
{
  /*mutex で  count1 を保護*/
    pthread_mutex_lock(&mutex);
    for(j=n/2;j<n;j++){
      count1 = count1 + j;
      printf("thread2 = %d \n",count1);
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}
