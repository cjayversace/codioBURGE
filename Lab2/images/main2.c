// // #include  <stdio.h>
// // #include  <sys/types.h>

// #define   MAX_COUNT  200

// void  ChildProcess(void);                /* child process prototype  */
// void  ParentProcess(void);               /* parent process prototype */

// // void  main(void)
// // {
// //      pid_t  pid;

// //      pid = fork();
// //      if (pid == 0) 
// //           ChildProcess();
// //      else 
// //           ParentProcess();
// // }

// // void  ChildProcess(void)
// // {
// //      int   i;

// //      for (i = 1; i <= MAX_COUNT; i++)
// //           printf("   This line is from child, value = %d\n", i);
// //      printf("   *** Child process is done ***\n");
// // }

// // void  ParentProcess(void)
// // {
// //      int   i;

// //      for (i = 1; i <= MAX_COUNT; i++)
// //           printf("This line is from parent, value = %d\n", i);
// //      printf("*** Parent is done ***\n");
// // }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ITERATIONS 30
#define MAX_SLEEP_TIME 10

int main() {
  pid_t pid1, pid2;
  int status;

  // Seed the random number generator
  srandom(getpid());

  // Create the first child process
  pid1 = fork();
  if (pid1 < 0) {
    perror("Failed to fork");
    exit(1);
  }

  if (pid1 == 0) { // First child process
    int iterations = random() % MAX_ITERATIONS;
    int i; // Declare loop variable here
    for (i = 0; i < iterations; i++) {
      printf("Child Pid: %d is going to sleep!\n", getpid());
      sleep(random() % (MAX_SLEEP_TIME + 1));
      printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }
      exit(0);
    }

    // Create the second child process
    pid2 = fork();
    if (pid2 < 0) {
      perror("Failed to fork");
      exit(1);
    }

    if (pid2 == 0) { // Second child process
      int iterations = random() % MAX_ITERATIONS;
      int i; // Declare loop variable here
      for (i = 0; i < iterations; i++) {
            printf("Child Pid: %d is going to sleep!\n", getpid());
            sleep(random() % (MAX_SLEEP_TIME + 1));
            printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
        }
        exit(0);
    }

    // Parent process
    int i; // Declare loop variable here
    for (i = 0; i < 2; i++) {
        pid_t finished_pid = wait(&status);
        printf("Child Pid: %d has completed\n", finished_pid);
    }

    return 0;
}
