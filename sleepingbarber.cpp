#include <iostream>
#include <stdlib.h>
#include <pthread.h> 
// make 10 a variable in the end
using namespace std;
void randwait(int secs) {
  int len;
  len = (int) ((drand48() * secs) + 1);
  while(len--);
}

int wait(int);
int signal(int);

void *customer(void *num);
void *barber(void *);
bool sleep = 0;
int waitar = 10;
bool chair = 0;
bool cut = 0;
int count = 0;

int main(){
  int Number[10];
  for (int i=0; i<10; i++) {
    Number[i] = i;
  }
  pthread_t tid[10];
  pthread_t btid;
  pthread_join(btid,NULL);
  printf("\nBarber Entered shop");
  pthread_create(&btid, NULL, barber, NULL);
  for (int i=0; i<10; i++) {
    pthread_create(&tid[i], NULL, customer, (void *)&Number[i]);
  }

  for (int i=0; i<10; i++) {
    pthread_join(tid[i],NULL);
  }
}

void wakebarber(int i){
    sleep = wait(sleep);
    chair = wait(chair);
    printf("\nBarber was woken up by customer %d", i);
  }
void cuthair(int i){
  cut = signal(cut);
  chair = signal(chair); 
  printf("\nBarber is cutting hair of customer %d", i);
  randwait(100000);
  printf("\nBarber finished cutting hair of customer %d", i);
  cut = wait(cut);
  chair = wait(chair);
  count--;
  }
void* barber(void *){
    while(1){
    if((waitar==10)&&(sleep==0)&&(cut==0)&&(count==0)){
    sleep = signal(sleep);
    chair = signal(chair);
    printf("\nBarber has gone to sleep");   
  }
}
}
 


void *customer(void *number){
    int num = *(int *)number;
   
    printf("\nCustomer %d leaving for barber shop.\n", num);
    randwait(20);
    printf("\nCustomer %d arrived at barber shop.\n", num);
    count++;
   
    if(waitar==0){
    printf("\nCustomer cant enter sorry."); 
    count--;
  }
    if(sleep==1){
      wakebarber(num);
      cuthair(num);
    }

  if(cut==1){
    waitar = wait(waitar);
    printf("\nCustomer %d entered waiting room", num);
    while(cut==1);
    if(chair==0&&cut==0)
    cuthair(num);
    waitar = signal(waitar);
     
  }

  }

  


int wait(int S){ 
  while(S<=0);
  S--;
  return S;
}

int signal(int S){
  S++;
  return S;
}


