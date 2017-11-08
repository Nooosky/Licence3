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

#define BUFSIZE 64000

// fait la résolution de nom inverse : adresse IP -> nom de domaine
char *resolve_addr_to_name(const struct sockaddr_in *addr)
{
  static char name[256];
  int error = getnameinfo((const struct sockaddr *)addr, sizeof(*addr), name, sizeof(name), NULL, 0, 0);
  if (error)
  {
    fprintf(stderr, "getnameinfo(%s): %s", inet_ntoa(addr->sin_addr), gai_strerror(error));
    exit(errno);
  }
  return name;
}

int main(int argc, char *argv[])
{
  // récupération des paramètres
  if (argc != 2) {
    fprintf(stderr, "USAGE: ./serveur <port_serveur>\n");
    exit(EXIT_FAILURE);
  }

  const int port = atoi(argv[1]);

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
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // associe socket a l'adresse
  if (bind(sock, (struct sockaddr *)&server_addr, (socklen_t) sizeof(server_addr)) == -1)
  {
    perror("bind()");
    exit(errno);
  }

  // boucle principal
  struct sockaddr_in client_addr;
  while (1)
  {
    // attend un client
    if (listen(sock, 1) == -1)
    {
      perror("listen()");
      exit(errno);
    }

    int sockClient;
    socklen_t size = sizeof(client_addr);
    if ((sockClient = accept(sock, (struct sockaddr *) &client_addr, &size)) == -1)
    {
      perror("accept()");
      exit(errno);
    }

    // envoie message client
    char reponse[] = "Message provenant du serveur!";
    if (send(sockClient, reponse, sizeof(reponse), 0) == -1)
    {
      perror("send()");
      exit(errno);
    }

    // fermeture de la socket client
    if (close(sockClient) == -1)
    {
      perror("close()");
      exit(errno);
    }
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
