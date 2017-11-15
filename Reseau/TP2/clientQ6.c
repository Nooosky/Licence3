// gcc -g -Wall -Wextra -O -o client client.c
// ./client localhost 54321

#include <libgen.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 4096
#define SOCKET_NAME "/tmp/9Lq7BNBnBycd6nxy.socket"

// fait la résolution de nom : nom de domaine -> adresse IP et se connect
int resolve_and_connect_hostname(const char *name, const char *port)
{
      struct addrinfo hints;
      struct addrinfo *result, *rp;
      int sfd;

      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_UNIX;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = 0;
      hints.ai_protocol = 0;

      int error = getaddrinfo(name, port, &hints, &result);
      if (error != 0)
      {
          fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(error));
          exit(errno);
      }

      for (rp = result; rp != NULL; rp = rp->ai_next)
      {
          sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
          if (sfd == -1)
              continue;

          if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
              break;

          close(sfd);
      }

      if (rp == NULL)
      {
          fprintf(stderr, "Could not connect\n");
          exit(EXIT_FAILURE);
      }

      freeaddrinfo(result);

      return sfd;
}

int main(int argc, char *argv[])
{
  // récupération des paramètres
  if (argc != 3)
  {
    fprintf(stderr, "USAGE: ./client <adresse_serveur> <port_serveur> \n");
    exit(EXIT_FAILURE);
  }

  int sock = socket(AF_UNIX, SOCK_SEQPACKET, 0);
  if (sock == -1)
  {
      perror("socket()");
      exit(errno);
  }

  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);

  if (connect (sock, (const struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
  {
    perror("connect()");
    exit(errno);
  }

  // recoie message
  char messageRecu[BUFSIZE];
  if (recv(sock, messageRecu, sizeof(messageRecu), 0) == -1)
  {
    perror("recvfrom()");
    exit(errno);
  }
  // affiche message recu
  puts((char *)messageRecu);

  //fermer le flux de connexion
  if (shutdown(sock, SHUT_RDWR) == -1)
  {
    perror("shutdown()");
    exit(errno);
  }

  // fermeture de la socket
  if (close(sock) == -1)
  {
    perror("close()");
    exit(errno);
  }

  return EXIT_SUCCESS;
}
