#ifndef BALLAD_H
#define BALLAD_H

typedef struct {
  char *name;
  char *help;
  void (*action)(char *arg);
} BalladCommand;

typedef struct {
  char *help;
  BalladCommand *buffer;
  int capacity;
  int index;
  int charc;
  char **charv;
} BalladCli;

// cli function declarations
BalladCli ballad_init(int charc, char **charv, char *help);
void ballad_run(BalladCli cli);
void ballad_add_command(BalladCli *cli, BalladCommand command);
void ballad_print(BalladCli cli);
char *ballad_get_arg(int charc, char **charv, int index);
void ballad_invalid_command_print(char *name, BalladCli cli);

// logging function declarations
void ballad_log_success(char *message);
void ballad_log_info(char *message);
void ballad_log_warning(char *message);
void ballad_log_danger(char *message);
#endif

#ifdef BALLAD_IMPLEMENTATION
#include "color_codes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BalladCli ballad_init(int charc, char **charv, char *help) {
  return (BalladCli){help,  (BalladCommand *)malloc(5 * sizeof(BalladCommand)),
                     5,     0,
                     charc, charv};
}

void ballad_run(BalladCli cli) {
  if (cli.charc < 2) {
    ballad_print(cli);
  } else {
    bool arg_exists = false;
    for (int i = 0; i < cli.index; i++) {
      if (strcmp(ballad_get_arg(cli.charc, cli.charv, 1), cli.buffer[i].name) ==
          0) {
        arg_exists = true;
        if (cli.buffer[i].action != NULL) {
          cli.buffer[i].action(ballad_get_arg(cli.charc, cli.charv, 2));
        }
      }
    }

    if (!arg_exists) {
      ballad_invalid_command_print(ballad_get_arg(cli.charc, cli.charv, 1),
                                   cli);
    }
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

void ballad_print(BalladCli cli) {
  printf("Usage: %s COMMAND [OPTIONS] [ARGS]"
         "\n\n\t%s\n\nOptions:\n\t--help, -h  Show this message and exit.\n",
         cli.charv[0], cli.help);

  printf("\nCommands:\n");
  for (int i = 0; i < cli.index; i++) {
    BalladCommand command = cli.buffer[i];
    printf("\t%s\t%s\n", command.name, command.help);
  }
}

char *ballad_get_arg(int charc, char **charv, int index) {
  // dunno why this function exists tbh i was trying to do the golang thing
  // didn't quite work out lmao

  if (charc > index)
    return charv[index];
  else
    return "";
}

void ballad_invalid_command_print(char *name, BalladCli cli) {
  printf("Usage: %s COMMAND [OPTIONS] [ARGS]\n", cli.charv[0]);
  printf("Try '%s --help' for help\n\n", cli.charv[0]);
  printf("No such command '%s'\n", name);
}

// logging functions definitions

#endif
