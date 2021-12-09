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

  rl_callback_handler_install(prompt, my_rlhandler);
}

int main()
{
  struct pollfd fd = {0, POLLIN};
  rl_callback_handler_install(prompt, my_rlhandler);

  while(running){
    if(poll(&fd, 1, 0) == 1)
      rl_callback_read_char();
  };

  rl_callback_handler_remove();

  return 0;
}
