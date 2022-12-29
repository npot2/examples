#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int sock;
  struct sockaddr_in server;
  char message[1000], server_reply[2000];

  // Create a socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    printf("Could not create socket");
  }
  puts("Socket created");

  // Set up the server address
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(8888);

  // Connect to the server
  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    perror("connect failed. Error");
    return 1;
  }
  puts("Connected\n");

  // Send a message to the server
  printf("Enter message: ");
  scanf("%s", message);
  if (send(sock, message, strlen(message), 0) < 0) {
    puts("Send failed");
    return 1;
  }

  // Receive a reply from the server
  if (recv(sock, server_reply, 2000, 0) < 0) {
    puts("recv failed");
  }
  puts("Server reply :");
  puts(server_reply);

  // Close the socket
  close(sock);

  return 0;
}
