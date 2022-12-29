#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>

int main() {
  nng_socket subscriber;
  nng_msg *msg;
  char *data;

  // Initialize the subscriber socket
  nng_sub0_open(&subscriber);

  // Connect the subscriber to the publisher
  nng_dial(subscriber, "tcp://localhost:5000", NULL, 0);

  while (1) {
    // Receive a message on the subscriber
    nng_recvmsg(subscriber, &msg, 0);
    data = nng_msg_body(msg);
    printf("Received message: %s\n", data);
  }

  // Clean up
  nng_close(subscriber);
  nng_msg_free(msg);

  return 0;
}
