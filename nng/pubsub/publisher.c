#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>

int main() {
  nng_socket publisher;
  nng_msg *msg;
  char *data;
  int i;

  // Initialize the publisher socket
  nng_pub0_open(&publisher);

  // Bind the publisher to a local address
  nng_listen(publisher, "tcp://localhost:5000", NULL, 0);

  while (1) {
    // Send a message from the publisher
    nng_msg_alloc(&msg, 0);
    data = nng_msg_body(msg);
    sprintf(data, "Message %d", i);
    nng_sendmsg(publisher, msg, 0);
    printf("Sent message: %s\n", data);
    i++;
  }

  // Clean up
  nng_close(publisher);
  nng_msg_free(msg);

  return 0;
}
