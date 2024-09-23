/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// void handler(int signum)
// { //signal handler
//   printf("Hello World!\n");
//   exit(1); //exit after printing
// }

// int main(int argc, char * argv[])
// {
//   signal(SIGALRM,handler); //register handler to handle SIGALRM
//   alarm(1); //Schedule a SIGALRM for 1 second
//   while(1); //busy wait for signal to be delivered
//   return 0; //never reached
// }

volatile sig_atomic_t alarm_count = 0; // Global variable to track alarms

// Handler for SIGALRM
void sigalrm_handler(int signum) {
  printf("Hello World!\n");
  alarm_count++;
}

// Handler for SIGINT
void sigint_handler(int signum) {
  printf("\nTotal alarms received: %d\n", alarm_count);
  exit(0); // Exit the program
}

int main() {
  // Register signal handlers
  signal(SIGALRM, sigalrm_handler); // Handle SIGALRM
  signal(SIGINT, sigint_handler); // Handle SIGINT
    
  alarm(1); // Schedule a SIGALRM for 1 second

  // Loop indefinitely
  while (1) {
    pause(); // Wait for a signal
    printf("Turing was right!\n");
    alarm(1); // Reset the alarm for the next second
  }

  return 0; // This line will never be reached
}
