#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_ALPHA 26
#define ASCII_MAJ_DEBUT 65

void testArgument(int argc);
void lectureText(char * text);
void modificationText(char * text, int clef);
void affichageText(char * text);


int main (int argc, char *argv[])
{
  int clef = 0;
  char *text = (char *) malloc(sizeof(char));

  testArgument(argc);
  clef = atoi(argv[1]);

  lectureText(text);
  modificationText(text, clef);
  affichageText(text);

  return 0;
}


void testArgument(int argc)
{
  if (argc != 2)
  {
      fprintf(stderr, "USAGE: ./main <clef> \n");
      exit(1);
  }
}

void lectureText(char * text)
{
  int i = 0, nb = 0;
  while((i = fgetc(stdin)) != EOF) // ctrl + d
  {
    unsigned char c = (unsigned char) i;
    ++nb;
    text = (char *) realloc(text, sizeof(char) * nb);
    text[nb - 1] = c;
  }
}

void modificationText(char * text, int clef)
{
  int i = 0;
  for (i = 0; text[i] != '\0'; ++i)
  {
    int ascii = (int) text[i];
    if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
    {
      ascii = text[i] + clef;

      while (ascii < 65)
        ascii += 26;
      while (ascii > 90)
        ascii -= 26;

      text[i] = (char) ascii;
    }
  }
}

void affichageText(char * text)
{
  printf("############ \n");
  printf("%s\n", text);
}
