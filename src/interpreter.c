#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "config.h"

char *character_names[][4] = {
    {"file",NULL},
    {"Ford Prefect"},
    {"Tricia McMillan"},
    {"Zaphod Beeblebrox"},
    NULL
};

int arrlength(char **array)
{
  int length = 0;
  while (array[length] != NULL)
    length++;
  return length;
}

int parse(char * stringtoparse, char **tokarr)
{
  int i = 0;
  tokarr[i] = stringtoparse;
  while ((tokarr[i] = strtok(tokarr[i], " ")) != NULL)
    tokarr[++i] = NULL;
}

int interpret(char * stringtointerpret)
{
  char *tokarr[100]; // maximum argument count
  parse(stringtointerpret, tokarr);
  int numberoftokens = arrlength(tokarr);
  printf("number of tokens %d\n", numberoftokens);
}

char *
character_name_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    //printf("state %d index %d len %d\n",state, list_index, len);
    //puts(text);

    while ((name = character_names[list_index++][0])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}

char **
character_name_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, character_name_generator);
}

int main()
{
  rl_bind_key('\t', rl_complete);
  rl_attempted_completion_function = character_name_completion;

  while (1)
  {
    char * input = readline("prompt> ");
    if (!input)
      break;
    add_history(input);
    interpret(input);
    free(input);
  }
	return 0;
}
