#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// klee --libc=uclibc --posix-runtime demo_args.bc --sym-argv 0 10 100

int main(int argc, char **argv) {
  char buf[16];

  int k = 0;
  for (int i = 1; i < argc; i++) {
    int ln = strlen(argv[i]);

    for (int j = 0; j < ln; j++) {
      buf[k] = argv[i][j];
      k++;
    }
  }

  buf[k] = '\0';
  printf("%s\n", buf);

  return 0;
}
