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
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 4096

// fait la résolution de nom : nom de domaine -> adresse IP et se connect
struct sockaddr_in resolve_hostname(const char *name, const char *port)
{
      struct addrinfo hints;
      struct addrinfo *result, *rp;
      int sfd;

      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_INET;
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
          if (sfd != -1)
              break;
      }

      if (rp == NULL)
      {
          fprintf(stderr, "Could not connect\n");
          exit(EXIT_FAILURE);
      }

      close(sfd);
      freeaddrinfo(result);

      return (struct sockaddr_in) rp;
}

int main(int argc, char *argv[])
{
  // récupération des paramètres
  if (argc != 3)
  {
    fprintf(stderr, "USAGE: ./client <adresse_serveur> <port_serveur> \n");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_addr = resolve_hostname(argv[1], argv[2]);

  // création de la socket
  int sock;
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    perror("socket()");
    exit(errno);
  }

  // recoie message
  char messageRecu[BUFSIZE];
  socklen_t size = sizeof(server_addr);
  if (recvfrom(sock, messageRecu, sizeof(messageRecu), 0, (struct sockaddr *) &server_addr, &size) == -1)
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
