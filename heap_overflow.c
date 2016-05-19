#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char *a = (char*)malloc(20);
  char *b = (char*)malloc(20);

  strncpy(b, a, 21);

  return 0;
}
