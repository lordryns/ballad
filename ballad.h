#ifndef BALLAD_H
#define BALLAD_H

typedef struct {
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
         "\n\n\t%s\n\nOptions:\n\t--help\tShow this message and exit",
         cli.charv[0], cli.help);
}

#endif
