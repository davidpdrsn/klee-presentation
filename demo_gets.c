#include <string.h>
#include <stdio.h>

// klee --libc=uclibc --posix-runtime demo_count.bc --sym-files 2 100

int main(int argc, char **argv) {
  char str[16];

  gets(str);
  
  return strlen(str);
}
