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
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 4096


int main(int argc, char *argv[])
{
  // récupération des paramètres
  if (argc != 2) {
    fprintf(stderr, "USAGE: ./serveur <port_serveur>\n");
    exit(EXIT_FAILURE);
  }

  // création de la socket
  int sock;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("socket()");
    exit(errno);
  }

  // association de la socket au port donné
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[1]));
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // associe socket a l'adresse
  if (bind(sock, (struct sockaddr *)&server_addr, (socklen_t) sizeof(server_addr)) == -1)
  {
    perror("bind()");
    close(sock);
    exit(errno);
  }

  struct sockaddr_in client_addr;

  // attend un client
  if (listen(sock, 20) == -1)
  {
    perror("listen()");
    close(sock);
    exit(errno);
  }

  int sockClient;
  socklen_t size = sizeof(client_addr);
  if ((sockClient = accept(sock, (struct sockaddr *) &client_addr, &size)) == -1)
  {
    perror("accept()");
    exit(errno);
  }

  //Recoie le nom du client
  char messageRecu[BUFSIZE];
  if (recv(sockClient, messageRecu, sizeof(messageRecu), 0) == -1)
  {
    perror("recvfrom()");
    exit(errno);
  }
  // affiche message recu
  puts((char *)messageRecu);

  // envoie message client
  char reponse[] = "Bonjour ";
  strcat(reponse, messageRecu);
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

  return EXIT_SUCCESS;
}
