// gcc -g -Wall -Wextra -O -o client client.c
// ./client 127.0.0.1 54321 Élève Chaprot

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
  struct addrinfo hints = {
    .ai_flags = 0,
    .ai_family = AF_INET,
    .ai_socktype = 0,
    .ai_protocol = 0,
  };
  struct addrinfo *addr;
  int error = getaddrinfo(name, NULL, &hints, &addr);
  if (error)
  {
    fprintf(stderr, "getaddrinfo(\"%s\"): %s", name, gai_strerror(error));
    exit(errno);
  }
  struct in_addr res = ((struct sockaddr_in *)addr->ai_addr)->sin_addr;
  freeaddrinfo(addr);
  return res;
}

int main(int argc, char *argv[])
{
  // récupération des paramètres
  if (argc < 3)
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

  // fermeture de la socket
  if (close(sock) == -1)
  {
    perror("close()");
    exit(errno);
  }

  return EXIT_SUCCESS;
}
