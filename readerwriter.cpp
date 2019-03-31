#include <iostream>
#include <stdlib.h>
#include <pthread.h> 
using namespace std;


int mutex[] = {1}; //mutual exclusion
int write[] = {1}; //for writer
int read[] = {0}; // reading
int holder[] = {5};
int readers[] = { 0, 1, 2, 3, 4 }; 
string reader_name[] = { "0", "1", "2", "3", "4" }; 

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

void wait(int* S, string printer){
  while(*S==0); 
  cout<<printer<<endl;
  *S -= 1;
}



void signal(int* fork1){
  *fork1 += 1;
}

void* writer(void* num) 
{
  int *ID = (int*)num;
  int i = *ID;
  //i is writer ID
    while (1) {
      cout<<"Writer wants to access data"<<endl;
      wait(write, "Writer is writing data");
      
      randwait(100000000);
      
      signal(write);
      cout<<"Writer has made changes"<<endl;
      randwait(100000000);
    } 
} 

void* reader(void* num) 
{
  int *ID = (int*)num;
  int i = *ID;
    while (1) {
      cout<<"Reader "+reader_name[i]+" wants to access the data"<<endl;
      wait(mutex);
      read[0]++;

      //Reader shouldnt starve
      if (read[0]==1)
        wait(write);

      signal(mutex);
      cout<<"Reader "+reader_name[i]+" is reading"<<endl;
      randwait(100000000);
      cout<<"Reader "+reader_name[i]+" has finished reading"<<endl;
      wait(mutex); // Reader wants to leave
      read[0]--;

      if(read[0]==0)
        //making availabke for writer
        signal(write);
      signal(mutex); //Leave

      randwait(400000000);
    } 
} 

int main() {
    pthread_t thread_id[6];

    pthread_create(&thread_id[5], NULL, writer, &holder[0]); 

     for (int i = 0; i < 5; i++){ 
        // create readers 
        pthread_create(&thread_id[i], NULL, reader, &readers[i]); 
     }

        for (int i = 0; i < 6; i++)   
          pthread_join(thread_id[i], NULL);
}
