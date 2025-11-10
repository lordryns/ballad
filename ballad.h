#ifndef BALLAD_H
#define BALLAD_H

typedef struct {
  char *name;
  char *help;
} BalladCommand;

typedef struct {
  char *help;
  BalladCommand *buffer;
  int capacity;
  int index;
  int charc;
  char **charv;
} BalladCli;

BalladCli ballad_init(int charc, char **charv, char *help);
void ballad_run(BalladCli cli);
void ballad_add_command(BalladCli *cli, BalladCommand command);
#endif

#ifdef BALLAD_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>

BalladCli ballad_init(int charc, char **charv, char *help) {
  return (BalladCli){help,  (BalladCommand *)malloc(5 * sizeof(BalladCommand)),
                     5,     0,
                     charc, charv};
}

void ballad_run(BalladCli cli) {
  printf("Usage: %s COMMAND [OPTIONS] [ARGS]"
         "\n\n\t%s\n\nOptions:\n\t--help, -h  Show this message and exit.\n",
         cli.charv[0], cli.help);

  printf("\nCommands:\n");
  for (int i = 0; i < cli.index; i++) {
    BalladCommand command = cli.buffer[i];
    printf("\t%s\t%s\n", command.name, command.help);
  }
  free(cli.buffer);
}

void ballad_add_command(BalladCli *cli, BalladCommand command) {
  if (cli->index > cli->capacity - 1) {
    cli->capacity *= 2;
    cli->buffer = (BalladCommand *)realloc(
        cli->buffer, cli->capacity * sizeof(BalladCommand));
  }
  cli->buffer[cli->index] = command;
  cli->index += 1;
}

#endif
