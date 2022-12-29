#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nng/nng.h>

int main() {
  nng_socket surveyor;
  nng_msg *msg;
  char *data;

  // Initialize the surveyor socket
  nng_surveyor0_open(&surveyor);

  // Connect the surveyor to the responders
  nng_dial(surveyor, "tcp://localhost:5000", NULL, 0);

  // Send a survey request to the responders
  nng_msg_alloc(&msg, 0);
  data = nng_msg_body(msg);
  strcpy(data, "What is your favorite color?");
  nng_sendmsg(surveyor, msg, 0);

  // Receive responses from the responders
  while (1) {
    nng_recvmsg(surveyor, &msg, 0);
    data = nng_msg_body(msg);
    printf("Received response: %s\n", data);
    nng_msg_free(msg);
  }

  // Clean up
  nng_close(surveyor);

  return 0;
}
