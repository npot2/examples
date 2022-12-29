#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>

int main() {
  nng_socket responder;
  nng_msg *msg;
  char *data;

  // Initialize the responder socket
  nng_rep0_open(&responder);

  // Bind the responder to a local address
  nng_listen(responder, "tcp://localhost:5000", NULL, 0);

  // Wait for a survey request from the surveyor
  nng_recvmsg(responder, &msg, 0);
  data = nng_msg_body(msg);
  printf("Received survey request: %s\n", data);

  // Send a response to the surveyor
  nng_msg_alloc(&msg, 0);
  data = nng_msg_body(msg);
  strcpy(data, "Hello, World!");
  nng_sendmsg(responder, msg, 0);

  // Clean up
  nng_close(responder);
  nng_msg_free(msg);

  return 0;
}
