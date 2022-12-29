#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>

int main() {
  nng_socket server;
  nng_msg *msg;
  char *data;

  // Initialize the server socket
  nng_rep0_open(&server);

  // Bind the server to a local address
  nng_listen(server, "tcp://localhost:5000", NULL, 0);

  while (1) {
    // Wait for a request from a client
    nng_recvmsg(server, &msg, 0);
    data = nng_msg_body(msg);
    printf("Received request: %s\n", data);

    // Send a response to the client
    nng_msg_alloc(&msg, 0);
    data = nng_msg_body(msg);
    strcpy(data, "Hello, World!");
    nng_sendmsg(server, msg, 0);
  }

  // Clean up
  nng_close(server);
  nng_msg_free(msg);

  return 0;
}
