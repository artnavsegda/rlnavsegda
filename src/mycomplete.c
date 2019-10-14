#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "config.h"

static int chisto(int count, int key)
{
  printf("%d\n",count);
  rl_forced_update_display();
}

int main()
{
  rl_bind_key('\t', chisto);

  while (1)
  {
    char * input = readline("prompt> ");
    if (!input)
      break;
    add_history(input);
    free(input);
  }
	return 0;
}
