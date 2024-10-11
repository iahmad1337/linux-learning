// see: man socket
// see: :help 'path' - about how vim makes 'gf' work
#include <sys/socket.h>
#include <sys/types.h>

#include <resolv.h>

#include <strings.h>
#include <string.h>

#include <arpa/inet.h>

#include <stdlib.h>
#include <unistd.h>

// PF_ - protocol family
// AF_ - address family
// these are practically the same: https://stackoverflow.com/a/6737450

#define MAXBUF 8192

int main(int argc, char* argv[]) {
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  char buffer[MAXBUF];
  if (sd < 0) {
    printf("Error opening socket: %d", sd);
  }
  // see: man 2 connect
  struct sockaddr_in dest;
  const char* host= "127.0.0.1";
  bzero(&dest, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(atoi(argv[2]));
  inet_aton(argv[1], &dest.sin_addr);
  // for now fails (the same goes for telnet). 'ufw' might be useful (to disable
  // firewall)
  // Also see: https://askubuntu.com/questions/166068/port-seems-to-be-open-but-connection-refused
  if (connect(sd, (struct sockaddr*)&dest, sizeof(dest)) != 0) {
    perror("socket connection");
    abort();
  }
  printf("Connected successfuly");

  sprintf(buffer, "%s\n", argv[3]);
  send(sd, buffer, strlen(buffer), 0);

  bzero(buffer, MAXBUF);
  recv(sd, buffer, MAXBUF-1, 0);
  printf("%s", buffer);
  close(sd);
  return 0;
}
