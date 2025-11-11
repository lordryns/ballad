#ifndef BALLAD_H
#define BALLAD_H


// this section was gotten from:
// https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
// although i updated the macro names to make reading easier


/*
 * This is free and unencumbered software released into the public domain.
 *
 * For more information, please refer to <https://unlicense.org>
 */

// Regular text
#define COLOR_BLACK "\e[0;30m"
#define COLOR_RED "\e[0;31m"
#define COLOR_GREEN "\e[0;32m"
#define COLOR_YELLOW "\e[0;33m"
#define COLOR_BLUE "\e[0;34m"
#define COLOR_MAGENTA "\e[0;35m"
#define COLOR_CYAN "\e[0;36m"
#define COLOR_WHITE "\e[0;37m"

// Regular bold text
#define COLOR_BOLD_BLACK "\e[1;30m"
#define COLOR_BOLD_RED "\e[1;31m"
#define COLOR_BOLD_GREEN "\e[1;32m"
#define COLOR_BOLD_YELLOW "\e[1;33m"
#define COLOR_BOLD_BLUE "\e[1;34m"
#define COLOR_BOLD_MAGENTA "\e[1;35m"
#define COLOR_BOLD_CYAN "\e[1;36m"
#define COLOR_BOLD_WHITE "\e[1;37m"

// Regular underline text
#define COLOR_UNDERLINE_BLACK "\e[4;30m"
#define COLOR_UNDERLINE_RED "\e[4;31m"
#define COLOR_UNDERLINE_GREEN "\e[4;32m"
#define COLOR_UNDERLINE_YELLOW "\e[4;33m"
#define COLOR_UNDERLINE_BLUE "\e[4;34m"
#define COLOR_UNDERLINE_MAGENTA "\e[4;35m"
#define COLOR_UNDERLINE_CYAN "\e[4;36m"
#define COLOR_UNDERLINE_WHITE "\e[4;37m"

// Regular background
#define COLOR_BACKGROUND_BLACK "\e[40m"
#define COLOR_BACKGROUND_RED "\e[41m"
#define COLOR_BACKGROUND_GREEN "\e[42m"
#define COLOR_BACKGROUND_YELLOW "\e[43m"
#define COLOR_BACKGROUND_BLUE "\e[44m"
#define COLOR_BACKGROUND_MAGENTA "\e[45m"
#define COLOR_BACKGROUND_CYAN "\e[46m"
#define COLOR_BACKGROUND_WHITE "\e[47m"

// High intensity background
#define COLOR_BRIGHT_BACKGROUND_BLACK "\e[0;100m"
#define COLOR_BRIGHT_BACKGROUND_RED "\e[0;101m"
#define COLOR_BRIGHT_BACKGROUND_GREEN "\e[0;102m"
#define COLOR_BRIGHT_BACKGROUND_YELLOW "\e[0;103m"
#define COLOR_BRIGHT_BACKGROUND_BLUE "\e[0;104m"
#define COLOR_BRIGHT_BACKGROUND_MAGENTA "\e[0;105m"
#define COLOR_BRIGHT_BACKGROUND_CYAN "\e[0;106m"
#define COLOR_BRIGHT_BACKGROUND_WHITE "\e[0;107m"

// High intensity text
#define COLOR_BRIGHT_BLACK "\e[0;90m"
#define COLOR_BRIGHT_RED "\e[0;91m"
#define COLOR_BRIGHT_GREEN "\e[0;92m"
#define COLOR_BRIGHT_YELLOW "\e[0;93m"
#define COLOR_BRIGHT_BLUE "\e[0;94m"
#define COLOR_BRIGHT_MAGENTA "\e[0;95m"
#define COLOR_BRIGHT_CYAN "\e[0;96m"
#define COLOR_BRIGHT_WHITE "\e[0;97m"

// Bold high intensity text
#define COLOR_BOLD_BRIGHT_BLACK "\e[1;90m"
#define COLOR_BOLD_BRIGHT_RED "\e[1;91m"
#define COLOR_BOLD_BRIGHT_GREEN "\e[1;92m"
#define COLOR_BOLD_BRIGHT_YELLOW "\e[1;93m"
#define COLOR_BOLD_BRIGHT_BLUE "\e[1;94m"
#define COLOR_BOLD_BRIGHT_MAGENTA "\e[1;95m"
#define COLOR_BOLD_BRIGHT_CYAN "\e[1;96m"
#define COLOR_BOLD_BRIGHT_WHITE "\e[1;97m"

// Reset
#define COLOR_RESET "\e[0m"

// end of color section


// ballad declarations 

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
