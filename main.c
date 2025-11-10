#include <stdio.h>
#define BALLAD_IMPLEMENTATION // dont forget to add this!
#include "ballad.h"
#undef BALLAD_IMPLEMENTATION // optional

// action functions
void find_stuff() { printf("Found some stuff!"); }

void apply_test() { printf("Testing... 1..2..3...\n"); }

int main(int charc, char **charv) {
  BalladCli cli =
      ballad_init(charc, charv, "my custom tool"); // create a new cli instance

  // commands, takes {name, help, action}
  ballad_add_command(
      &cli, (BalladCommand){"find", "Use this to find stuff", find_stuff});

  ballad_add_command(&cli,
                     (BalladCommand){"delete", "Use this to delete stuff"});

  ballad_add_command(
      &cli,
      (BalladCommand){"test", "Use to test the existing infra", apply_test});

  ballad_run(cli); // run the cli
  return 0;
}
