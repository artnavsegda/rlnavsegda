#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>

char running = 1;
const char *prompt = ">";

void my_rlhandler(char* line){
  if (line == NULL || strcmp (line, "exit") == 0)
  {
    rl_callback_handler_remove ();
    running = 0;
  }

  if (strcmp (line, "test") == 0)
  {
    printf("running test\n");
  }

  rl_callback_handler_install(prompt, my_rlhandler);
}

int main()
{
  struct pollfd pfds[2];
  int pfdcount = 1;
  pfds[0].fd = 0;
  pfds[0].events = POLLIN;

  rl_callback_handler_install(prompt, my_rlhandler);

  while(running){
    poll(pfds,pfdcount, -1);

    if(pfds[0].revents & POLLIN)
      rl_callback_read_char();
  };

  rl_callback_handler_remove();

  return 0;
}
