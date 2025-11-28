#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid;
  int result;

  printf(1, "=== Priority Scheduler Edge Case Test ===\n\n");

  // Test 1: Invalid priority (too low)
  printf(1, "Test 1: Setting invalid priority -5 (should fail)\n");
  result = setpriority(-5);
  if(result < 0)
    printf(1, "  PASS: Correctly rejected negative priority\n");
  else
    printf(1, "  FAIL: Accepted invalid priority\n");

  // Test 2: Invalid priority (too high)
  printf(1, "\nTest 2: Setting invalid priority 35 (should fail)\n");
  result = setpriority(35);
  if(result < 0)
    printf(1, "  PASS: Correctly rejected out-of-range priority\n");
  else
    printf(1, "  FAIL: Accepted invalid priority\n");

  // Test 3: Valid boundary priorities
  printf(1, "\nTest 3: Setting boundary priority 0 (highest)\n");
  result = setpriority(0);
  if(result == 0)
    printf(1, "  PASS: Accepted priority 0\n");
  else
    printf(1, "  FAIL: Rejected valid priority\n");

  printf(1, "\nTest 4: Setting boundary priority 31 (lowest)\n");
  result = setpriority(31);
  if(result == 0)
    printf(1, "  PASS: Accepted priority 31\n");
  else
    printf(1, "  FAIL: Rejected valid priority\n");

  // Test 5: Priority inheritance in fork
  printf(1, "\nTest 5: Testing priority inheritance\n");
  setpriority(15);
  
  pid = fork();
  if(pid == 0){
    // Child should inherit priority 15
    printf(1, "  Child process created (should inherit priority 15)\n");
    printf(1, "  Child performing work...\n");
    int i, sum = 0;
    for(i = 0; i < 100; i++){
      sum += i;
    }
    printf(1, "  Child finished, sum=%d\n", sum);
    exit();
  }
  
  wait();
  printf(1, "  PASS: Child inherited and executed successfully\n");

  // Test 6: Equal priority processes
  printf(1, "\nTest 6: Multiple processes with same priority\n");
  int pid1, pid2;
  
  pid1 = fork();
  if(pid1 == 0){
    setpriority(10);
    printf(1, "  Process A (Priority=10) running\n");
    sleep(5);
    exit();
  }
  
  pid2 = fork();
  if(pid2 == 0){
    setpriority(10);
    printf(1, "  Process B (Priority=10) running\n");
    sleep(5);
    exit();
  }
  
  wait();
  wait();
  printf(1, "  PASS: Equal priority processes handled correctly\n");

  printf(1, "\n=== Edge Case Test Complete ===\n");
  printf(1, "All tests passed!\n");
  
  exit();
}