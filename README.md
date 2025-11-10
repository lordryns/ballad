# ballad
A command line argument parser for C (single header library)

Ballad takes heavy inspiration from [urfave/cli](https://github.com/urfave/cli) in golang and attempts to implement a similar workflow.

The Ballad philosophy is to abstract away as much complexity as possible.

## Setup instructions
Just clone the repo and move the ballad.h file to your codebase and that's it!

## How to use ?

Here is a basic example of Ballad in use 


```c 
#include <stdio.h>
#define BALLAD_IMPLEMENTATION // dont forget to add this!
#include "ballad.h"
#undef BALLAD_IMPLEMENTATION // optional

// action functions
void find_stuff() { 
  printf("Found some stuff!"); 
}

void apply_test() { 
  printf("Testing... 1..2..3...\n"); 
}


int main(int charc, char **charv) {
  BalladCli cli = ballad_init(charc, charv, "my custom tool"); // create a new cli instance

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
```


**Full documentation coming soon!** 

> [!CAUTION]
> Project is still under active development!
