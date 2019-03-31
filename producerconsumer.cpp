#include <iostream>
#include <random>
#define BUFFER_SIZE 10
int mutex = 1;
int full=0;
int count=0;
int empty= BUFFER_SIZE;
int buffer[BUFFER_SIZE]; 
// 1 indicative of item, 0 indicative of no item
//initializing my functions	
  int wait(int);
	int signal(int);
  void Producer();
	void Consumer();
int main() {
//running a random producer consumer thread
  for (int i=0; i<10; ++i){        
    switch(rand() % 2 + 1) {
      case 1:	
      if((mutex==1)&&(empty!=0))
			  Producer();
		  else
			  printf("\n Buffer is full");
		  break;
		  case 2:
  	  if((mutex==1)&&(full!=0))
			  Consumer();
		  else
			  printf("\n Buffer is empty");
		  break;
    }
  }
}
// wait and signal functions for semaphore 
  int wait(int S){
    while(S<=0);   
    S--;
    return S;
  }

  int signal(int S){
    S++;
    return S;
  }

void Producer(){
  mutex=wait(mutex);
  full=signal(full);
  empty=wait(empty);
  buffer[count] = 1;
  count++;
  printf("\n Item %d was produced", count);
  mutex=signal(mutex);
}

void Consumer(){
  mutex=wait(mutex);
  empty=signal(empty);
  full=wait(full);
  buffer[count] = 0;
  printf("\n Item %d was consumed", count);
  count--;
  mutex=signal(mutex);
}