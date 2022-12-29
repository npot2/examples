#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>

int main() {
  nng_socket client;
  nng_msg *msg;
  char *data;

  // Initialize the client socket
  nng_rep0_open(&client);

  // Bind the client to a local address
  nng_listen(client, "tcp://localhost:5000", NULL, 0);

  // Wait for a survey request from the client
  nng_recvmsg(client, &msg, 0);
  data = nng_msg_body(msg);
  printf("Received survey request: %s\n", data);

  // Send a response to the client
  nng_msg_alloc(&msg, 0);
  data = nng_msg_body(msg);
  strcpy(data, "Hello, World!");
  nng_sendmsg(client, msg, 0);

  // Clean up
  nng_close(client);
  nng_msg_free(msg);

  return 0;
}
