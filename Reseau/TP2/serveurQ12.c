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
#include <sys/select.h>
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
  sleep(5);
  int sock;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("socket()");
    exit(errno);
  }
  sleep(5);

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

  sleep(5);

  struct sockaddr_in client_addr;

  // attend un client
  if (listen(sock, 20) == -1)
  {
    perror("listen()");
    close(sock);
    exit(errno);
  }

  sleep(5);

  int sockClient;
  socklen_t size = sizeof(client_addr);
  if ((sockClient = accept(sock, (struct sockaddr *) &client_addr, &size)) == -1)
  {
    perror("accept()");
    exit(errno);
  }

  sleep(5);


  fd_set writefs;

  while(1)
  {
     FD_ZERO(&writefs);
     FD_SET(sockClient, &writefs);

     sleep(5);

     // temporisation
     if(select(sockClient + 1, NULL, &writefs, NULL, NULL) < 0)
     {
        perror("select()");
        exit(errno);
     }

     // si des donnes sur la socket
     sleep(5);

     if(FD_ISSET(sockClient, &writefs))
     {
       // envoie message client
       char reponse[] = "message du serveur";
       sleep(5);
       if (send(sockClient, reponse, BUFSIZE, 0) == -1)
       {
         perror("send()");
         exit(errno);
       }

       break;
     }
   }
   sleep(5);

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
