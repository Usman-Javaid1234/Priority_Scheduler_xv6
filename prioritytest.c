#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid1, pid2, pid3;
  int i;

  printf(1, "=== Priority Scheduler Basic Test ===\n");
  printf(1, "Creating 3 processes with different priorities\n\n");

  // High priority process (priority 5)
  pid1 = fork();
  if(pid1 == 0){
    setpriority(5);  // High priority
    printf(1, "[HIGH Priority=5, PID=%d] Starting...\n", getpid());
    for(i = 0; i < 5; i++){
      printf(1, "[HIGH Priority=5, PID=%d] Running iteration %d\n", getpid(), i);
      sleep(10);
    }
    printf(1, "[HIGH Priority=5, PID=%d] Finished\n", getpid());
    exit();
  }

  // Medium priority process (priority 20)
  pid2 = fork();
  if(pid2 == 0){
    setpriority(20);  // Medium priority
    printf(1, "[MED Priority=20, PID=%d] Starting...\n", getpid());
    for(i = 0; i < 5; i++){
      printf(1, "[MED Priority=20, PID=%d] Running iteration %d\n", getpid(), i);
      sleep(10);
    }
    printf(1, "[MED Priority=20, PID=%d] Finished\n", getpid());
    exit();
  }

  // Low priority process (priority 30)
  pid3 = fork();
  if(pid3 == 0){
    setpriority(30);  // Low priority
    printf(1, "[LOW Priority=30, PID=%d] Starting...\n", getpid());
    for(i = 0; i < 5; i++){
      printf(1, "[LOW Priority=30, PID=%d] Running iteration %d\n", getpid(), i);
      sleep(10);
    }
    printf(1, "[LOW Priority=30, PID=%d] Finished\n", getpid());
    exit();
  }

  // Parent waits for all children
  wait();
  wait();
  wait();

  printf(1, "\n=== Test Complete ===\n");
  printf(1, "Expected: HIGH priority process should run more frequently\n");
  
  exit();
}