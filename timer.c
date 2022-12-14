/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int alarmOn = 0;
int alarmNum = 0;

time_t start, stop;

void alarmHandler(int signum)
{ //signal handler
  printf("Hello World!\n");
  sleep(5);
  
  alarmOn = 1;
  alarmNum++;
}

void sigintHandler(int signum)
{
  int totalTime;
  stop = time(NULL);
  totalTime = stop - start;
  
  printf("Number of Alarms: %d in seconds: %d\n", alarmNum, totalTime);
}


int main(int argc, char * argv[])
{
  signal(SIGALRM, alarmHandler); //register handler to handle SIGALRM
  signal(SIGINT, sigintHandler);
  start = time(NULL);
  
  
  while(1){
    alarmOn = 0;
    alarm(5);
  
    while(!alarmOn) //busy wait for signal to be delivered
      ;
    printf("Turing was right!\n");
  }
  return 0; //never reached
}
