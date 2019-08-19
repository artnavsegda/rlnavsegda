#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "config.h"

int main()
{
	printf(PACKAGE_STRING);
	printf("\n");
	return 0;
}
