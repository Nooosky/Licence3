#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
  if (argc != 3)
  {
      fprintf(stderr, "USAGE: ./main3 <clef> <texte> \n");
      exit(1);
  }

  int decalage = atoi(argv[1]);
  char *chaine = argv[2];

  int i = 0;
  for (i = 0; chaine[i] != '\0'; ++i)
  {
    int ascii = chaine[i] + decalage;

    while (ascii < 65)
      ascii += 26;

    while (ascii > 90)
      ascii -= 26;

    chaine[i] = (char) ascii;
  }

  printf("%s\n", chaine);

  return 0;
}
