// clang -emit-llvm -c overflow.c -o overflow.bc
// klee --libc-uclibc --posix-runtime overflow.bc

#include <string.h>

int main(int argc, char **argv) {
  char buf[64];
  klee_make_symbolic(buf, sizeof(buf), "buf");

  char cpy[8];
  strcpy(cpy, buf);

  return 0;
}
