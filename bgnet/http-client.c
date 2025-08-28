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

#include <netinet/in.h>
#include <netdb.h>  // struct servent, getservent, getserventbyname, ...

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  char buffer[MAXBUF];
  if (sd < 0) {
    printf("Error opening socket: %d\n", sd);
  }
  struct servent *serv;
  if ((serv = getservbyname("http", "tcp")) == NULL) {
    printf("HTTP servent failed\n");
    return 1;
  }
  printf("serv.s_name: %s\nserv.s_port: %d\nserv.s_proto: %s\n", serv->s_name, serv->s_port, serv->s_proto);

  if ((sd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket accuisition failed");
    return 1;
  }

  // initialize address structure
  struct sockaddr_in dest;
  bzero(&dest, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = serv->s_port;  // htons?
  if ((dest.sin_addr.s_addr = inet_addr(argv[1])) == 0) {
    perror("inet_addr failed");
    return 1;
  }

  // connect to the server
  if (connect(sd, &dest, sizeof(dest)) != 0) {
    perror("socket connection");
    return 1;
  }

  // form the query and send it
  sprintf(buffer, "GET %s HTTP/1.1\n\n", argv[2]);
  send(sd, buffer, strlen(buffer), 0);

  // read and display all data
  int bytes_read = 0;
  do {
    bytes_read = recv(sd, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes_read] = 0;
    if (bytes_read > 0) {
      printf("%s\n", buffer);
    }
  } while (bytes_read > 0);

  printf("done\n");

  close(sd);
  return 0;
}
