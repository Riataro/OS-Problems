#include <iostream>
#include <stdlib.h>
#include <pthread.h> 
using namespace std;

int fs[] = {1,1,1,1,1};
//1 indicates available
int pid[] = { 0, 1, 2, 3, 4 }; 

void randwait(int secs) {
  int len;
  len = (int) ((drand48() * secs) + 1);
  while(len--);
}

void wait(int* fs1, int* fs2){

  while(*fs1 == 0 || *fs2 == 0); 
  *fs1 -= 1;
  *fs2 -= 1;
}

void signal(int* fs1, int* fs2){
  *fs1 += 1;
  *fs2 += 1;
}
void* philospher(void* num) 
{ 
  int *ID = (int*)num;
  int i = *ID;
  //i is Philosopher ID
    while (1) {
        cout<<"Philosopher "<<i<<" is Hungry"<<endl;
        wait(fs+i, fs+((i-1)%5));
        cout<<"Philosopher "<<i<<" is Eating"<<endl;
        randwait(100);        

        signal(fs + i,fs+((i-1)%5));
        cout<<"Philosopher "<<i<<" has finished Eating"<<endl;
        cout<<"Fork "<<i<<" & "<<(i-1)%5<<" are free"<<endl;
        cout<<"Philosopher "<<i<<" is Thinking"<<endl;
        randwait(100); 
        
    } 
} 

int main() {
    pthread_t tid[5];
     for (int i = 0; i < 5; i++){ 
        // create philosopher processes 
        pthread_create(&tid[i], NULL, philospher, &pid[i]); 
     }
        for (int i = 0; i < 5; i++)   
        pthread_join(tid[i], NULL);            
}