// gcc -g -Wall -Wextra -O -o serveur serveur.c
// ./serveur 54321

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


int main(int argc, char *argv[])
{
  // récupération des paramètres
  if (argc != 2) {
    fprintf(stderr, "USAGE: ./serveur <port_serveur>\n");
    exit(EXIT_FAILURE);
  }

  unlink(SOCKET_NAME);

  // création de la socket
  int sock;
  if ((sock = socket(AF_UNIX, SOCK_SEQPACKET, 0)) < 0)
  {
    perror("socket()");
    exit(errno);
  }

  // association de la socket au port donné
  struct sockaddr_un server_addr;
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, SOCKET_NAME, sizeof(server_addr.sun_path) - 1);

  // associe socket a l'adresse
  if (bind(sock, (struct sockaddr *)&server_addr, (socklen_t) sizeof(server_addr)) == -1)
  {
    perror("bind()");
    close(sock);
    exit(errno);
  }

  // attend un client
  if (listen(sock, 20) == -1)
  {
    perror("listen()");
    close(sock);
    exit(errno);
  }

  int sockClient;
  if ((sockClient = accept(sock, NULL, NULL)) == -1)
  {
    perror("accept()");
    exit(errno);
  }

  // envoie message client
  char reponse[] = "message du serveur";
  if (send(sockClient, reponse, BUFSIZE, 0) == -1)
  {
    perror("send()");
    exit(errno);
  }

  //fermer le flux de connexion
  if (shutdown(sockClient, SHUT_RDWR) == -1)
  {
    perror("shutdown()");
    exit(errno);
  }

  // fermeture de la socket client
  if (close(sockClient) == -1)
  {
    perror("close()");
    exit(errno);
  }

  //fermer le flux de connexion
  if (shutdown(sock, SHUT_RDWR) == -1)
  {
    perror("shutdown()");
    exit(errno);
  }

  // fermeture de la socket serveur
  if (close(sock) == -1)
  {
    perror("close()");
    exit(errno);
  }

  unlink(SOCKET_NAME);

  return EXIT_SUCCESS;
}
