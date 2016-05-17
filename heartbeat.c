#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int   length;
  char *payload;
} ssl_record;

typedef struct {
  int   length;
  char *payload;
} heartbeat;

int main(int argc, char **argv) {
  //- SETUP -//
  ssl_record ssl_records[100];

  for (int i = 1; i < 100; i++) {
    ssl_records[i].length  = 4;
    ssl_records[i].payload = (char*)malloc(4);
    *ssl_records[i].payload = "AAAA";
  }

  // Create a heartbeat message
  heartbeat *hb = (heartbeat*)malloc(sizeof(heartbeat));
  hb->length    = 256;
  hb->payload   = (char*)malloc(3);
  *hb->payload = (char*)":(";

  // Save it as ssl payload
  ssl_record *ssl = &ssl_records[0];
  klee_make_symbolic(ssl, sizeof(ssl_record), "ssl_record");
  ssl->length     = sizeof(heartbeat);
  ssl->payload    = (char*)hb;
  printf("HB size: %d\n", sizeof(heartbeat));

  //- HEARTBLEED EMULATION START -//

  // Recieve ssl record and read heartbeat message.
  ssl = &ssl_records[0];
  hb  = (heartbeat*)ssl->payload;
  int ln = hb->length;

  /*
  if (ssl->length < ln)
    ln = ssl->length;
  */

  // Create new heartbeat message to send back.
  heartbeat echo;
  echo.length  = ln;  // Same length as original hb message.
  echo.payload = (char*)malloc(ln);

  // Copy from original payload, withouth checking against ssl payload length.
  for (int i = 0; i < ln; i++) {
    echo.payload[i] = hb->payload[i];
  }
 
  //- HEARTBLEED EMULATION STOP -//
 
  char *p = echo.payload;
  for (int i = 0; i < echo.length; i++) {
    printf("%d\t%#02X\n",i, p[i]); 
  }
  
  return 0;
}
