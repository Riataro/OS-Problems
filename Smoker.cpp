#include <iostream>
#include <stdlib.h>
#include <pthread.h> 
using namespace std;

string sem[] = {"Paper and Tobacco", "Matches and Paper", "Matches and Tobacco"};
int semaphores[] = {0,0,0}; // 0 indicates not on table
int done[] = {1}; 
int agi[] = {3};
int smokers[] = {0, 1, 2}; 
string resource[] = {"Matches","Tobacco","Paper"};

void exec(int secs) {
  int len;
  len = (int) ((drand48() * secs) + 1);
  while(len--);
}

void wait(int* semaphore){
  while(*semaphore==0); 
  *semaphore -= 1;
}

void wait(int* semaphore, string printer){
  while(*semaphore==0);
  cout<<printer<<endl;
  *semaphore -= 1;
}

void signal(int* semaphore){
  *semaphore += 1;
}

void* agent(void* num) 
{
    while (1) {
      //waiting for smoker to finish
      wait(done);
      int random = rand() % 3;
      cout<<"Agent puts "<<sem[random]<<" on table"<<endl;
      signal(semaphores+random);
    } 
} 

void* smoker(void* num) 
{
  int *ID = (int*)num;
  int i = *ID;
  //i is smoker ID
    while (1) {
        cout<<"Smoker with "+resource[i]+" wants to smoke"<<endl;
        wait(semaphores + i,"Smoker with "+resource[i]+" is smoking");

        //smoking
        exec(10000); 

        cout<<"Smoker with "<<resource[i]<<" is done smoking"<<endl;
       // agent puts down next resources
        signal(done);
        
        
    } 
} 

int main() {
    pthread_t thread_id[4];

     pthread_create(&thread_id[3], NULL, agent, &agi[0]); //agent
     exec(200);

     for (int i = 0; i < 3; i++){ 
        // create smokers
        pthread_create(&thread_id[i], NULL, smoker, &smokers[i]); 
     } 
       
        for (int i = 0; i < 3; i++)   
         pthread_join(thread_id[i], NULL);
}