#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_PROCESSES 50

int
main(int argc, char *argv[])
{
  int i, pid;
  int completed = 0;

  printf(1, "=== Priority Scheduler Stress Test ===\n");
  printf(1, "Creating %d processes with varying priorities\n\n", NUM_PROCESSES);

  for(i = 0; i < NUM_PROCESSES; i++){
    pid = fork();
    
    if(pid == 0){
      // Child process
      int priority = i % 32;  // Priorities from 0-31
      setpriority(priority);
      
      // Do some work
      int j, sum = 0;
      for(j = 0; j < 1000; j++){
        sum += j;
      }
      
      printf(1, "Process %d (Priority=%d) finished, sum=%d\n", getpid(), priority, sum);
      exit();
    }
    
    if(pid < 0){
      printf(1, "Fork failed at iteration %d\n", i);
      break;
    }
  }

  // Parent waits for all children
  while((pid = wait()) > 0){
    completed++;
  }

  printf(1, "\n=== Stress Test Complete ===\n");
  printf(1, "Successfully completed %d processes\n", completed);
  
  exit();
}