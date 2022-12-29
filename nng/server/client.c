#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>

int main() {
  nng_socket client;
  nng_msg *msg;
  char *data;

  // Initialize the client socket
  nng_req0_open(&client);

  // Connect the client to the server
  nng_dial(client, "tcp://localhost:5000", NULL, 0);

  // Send a request to the server
  nng_msg_alloc(&msg, 0);
  data = nng_msg_body(msg);
  strcpy(data, "Hello, World!");
  nng_sendmsg(client, msg, 0);

  // Receive a response from the server
  nng_recvmsg(client, &msg, 0);
  data = nng_msg_body(msg);
  printf("Received response: %s\n", data);

  // Clean up
  nng_close(client);
  nng_msg_free(msg);

  return 0;
}
