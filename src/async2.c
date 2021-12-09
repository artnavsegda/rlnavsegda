#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>  /* for free() */
#include <unistd.h> /* for usleep() */
#include <poll.h>

char running = 1;

// The function that'll get passed each line of input
void my_rlhandler(char* line);
void my_rlhandler(char* line){
}

// The main entry-point for the program
int main()
{
 const char *prompt = "WOOP> ";

 struct pollfd fd = {0, POLLIN};

 // Install the handler
 rl_callback_handler_install(prompt, my_rlhandler);

 // Enter the event loop (simple example, so it doesn't do much except wait)
 running = 1;
 while(running){
    //usleep(10000);
    if(poll(&fd, 1, 0) == 1)
      rl_callback_read_char();
 };
 printf("\nEvent loop has exited\n");

 // Remove the handler
 rl_callback_handler_remove();

 return 0; // happy ending
}
