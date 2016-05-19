#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// --sym-argvs <min> <max> <len>

int main (int argc, char **argv) {
  int a = 1;
  int b = 1;

  // ADVANCED ALGORITHM START
  while (b <= 10) {
    b = a;
    a = a * 2;
  }  

  // Some constraint that we whish to have satisfied
  klee_assume(b <= a);

  return 0;
}
