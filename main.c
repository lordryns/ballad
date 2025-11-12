#include <stdio.h>
#define BALLAD_IMPLEMENTATION
#include "ballad.h"

void create_new_project(char *arg)
{
	printf("Your project '%s' created successfully!\n", arg);
}

int main(int charc, char **charv) 
{
	BalladCli cli = ballad_init(charc, charv, "Create fun stuff with test-cli");	

	BalladFlag flag = {'f', "find", BOOLEAN_FLAG};
	BalladFlag flags[1] = {flag};
	ballad_add_command(&cli, (BalladCommand){"new", "Create a new project", create_new_project, (BalladFlagBox){flags, 1}});

	ballad_run(cli);
	return 0;
}


