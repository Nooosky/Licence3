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
struct in_addr resolve_hostname(const char *name)
{
      struct addrinfo hints;
      struct addrinfo *result;

      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_INET;
      hints.ai_socktype = SOCK_DGRAM;
      hints.ai_flags = 0;
      hints.ai_protocol = 0;

      int error = getaddrinfo(name, NULL, &hints, &result);
      if (error != 0)
      {
          fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(error));
          exit(errno);
      }

      struct in_addr res = ((struct sockaddr_in *)result->ai_addr)->sin_addr;
      freeaddrinfo(result);
      return res;
}

int resolve_and_connect_hostname(const char *name, const char *port,   struct sockaddr_in * s)
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
          if (sfd < 0)
              close(sfd);
          else
          {
            s = (struct sockaddr_in *) rp;
            s->sin_family = AF_INET;
            break;
          }
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

  struct sockaddr_in * server_addr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));

  // création de la socket
  int sock = resolve_and_connect_hostname(argv[1], argv[2], server_addr);

  // encodage de l'adresse du serveur
  /*struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr = resolve_hostname(argv[1]);

  // création de la socket
  int sock;
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      perror("socket()");
      exit(errno);
  }*/

  // envoie message
  char reponse[] = "OK";
  if (sendto(sock, reponse, sizeof(reponse), 0, (struct sockaddr *) &server_addr,  (socklen_t) sizeof(server_addr)) == -1)
  {
    perror("sendto()");
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
