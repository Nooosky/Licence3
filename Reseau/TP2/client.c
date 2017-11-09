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

#define BUFSIZE 64000

// fait la résolution de nom : nom de domaine -> adresse IP
struct in_addr resolve_name_to_addr(const char *name)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int sfd;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_DGRAM;
   hints.ai_flags = 0;
   hints.ai_protocol = 0;

   int error = getaddrinfo(name, NULL, &hints, &result);
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

   struct in_addr res = ((struct sockaddr_in *)rp->ai_addr)->sin_addr;
   return res;
}

int main(int argc, char *argv[])
{
  // récupération des paramètres
  if (argc != 3)
  {
    fprintf(stderr, "USAGE: ./client <adresse_serveur> <port_serveur> \n");
    exit(EXIT_FAILURE);
  }

  const char *server = argv[1];
  const int port = atoi(argv[2]);

  // encodage de l'adresse du serveur
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr = resolve_name_to_addr(server);

  // création de la socket
  int sock;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket()");
    exit(errno);
  }

  // se connect au serveur
  if (connect(sock, (struct sockaddr *) &server_addr, (socklen_t) sizeof(server_addr)) == -1)
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
