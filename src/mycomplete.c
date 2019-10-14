#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "config.h"

int i = 0;

static int chisto(int count, int key)
{
  if (i == 0)
    i = 1;
  else
    i = 0;
  if (i)
    rl_insert_text("puk");
  else
    {
      printf("\n%d\n",count);
      printf("buffer: %s\n", rl_line_buffer);
      printf("position: %d\n", rl_point);
      printf("buf len %d\n", rl_end);
      //rl_message("hello");
//  rl_on_new_line();
      rl_forced_update_display();
    }
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
