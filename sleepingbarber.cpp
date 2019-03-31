#include <iostream>
#include <stdlib.h>
#include <pthread.h> 
#include <queue>
// make 10 a variable in the end
using namespace std;
void randwait(int secs) {
  int len;
  len = (int) ((drand48() * secs) + 1);
  while(len--);
}
void wait(int* S){
  while(*S==0); 
  *S -= 1;
}

void wait(int* S1, int* S2){
  while(*S1==0 || *S2==0); 
  *S1 -= 1;
  *S2 -=1;
}

void signal(int* S){
  *S+=1;
}


void *customer(void *num);
void *barber(void *);
int awake[] = {0};
int waitar= 10;
int chair[] = {0};
int count[] = {0};
int customers[]={0,1,2,3,4,5,6,7,8,9};
queue<int> w;

int main(){
  pthread_t tid[10];
  pthread_t btid;
  pthread_join(btid,NULL);
  printf("\nBarber Entered shop");
  pthread_create(&btid, NULL, barber, NULL);
  for (int i=0; i<10; i++) {
    pthread_create(&tid[i], NULL, customer, (void *)&customers[i]);
  }

  for (int i=0; i<10; i++) {
    pthread_join(tid[i],NULL);
  }
}

void *customer(void *number){
    int num = *(int *)number;
   
    printf("\nCustomer %d leaving for barber shop.\n", num);
    randwait(20);
    printf("\nCustomer %d arrived at barber shop.\n", num);
    if(waitar>0){
    waitar -=1;
    printf("\nCustomer %d entered waiting room", num);
    w.push(num);
    signal(count);
    signal(chair);
    while(awake[0]==0||w.front()!=num);
    wait(awake);
    printf("\nBarber is cutting hair of customer %d", num);
    randwait(100); //haircut
    printf("\nBarber finished cutting hair of customer %d", num);
    }else{
    printf("\nCustomer %d cant enter sorry.",num); 
    }
   while(1);
}
void* barber(void *){
    wait(count);{  //sleeping
    while(1){
    wait(count,chair);
    waitar+=1;
    signal(awake);
    signal(chair);
    randwait(2314);
    w.pop();

  }
}
} 


