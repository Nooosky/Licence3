#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_ALPHA 26
#define ASCII_MAJ_DEBUT 65

void supprimeNonLettre(char * s);
void supprimeNonLettre(char * s)
{
  char * newS = (char *) malloc(sizeof(char));
  int i = 0, nombre = 0;
  for (i = 0; s[i] != '\0'; ++i)
  {
    int ascii = (int) s[i];
    if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
    {
      ++ nombre;
      newS = (char *) realloc(newS, sizeof(char) * nombre);
      newS[nombre - 1] = s[i];
    }
  }

  s =  (char *) realloc(s, sizeof(newS));
  s = newS;
}




int main (int argc, char *argv[])
{
  if (argc != 2)
  {
      fprintf(stderr, "USAGE: ./main <clef> \n");
      exit(1);
  }

  char *clef = argv[1];
  printf("%s\n", clef);
  supprimeNonLettre(clef);
  printf("%s\n", clef);

  int nbCaractereTotal = 0;
  char *textChiffre = (char *) malloc(sizeof(char));

  int i;
	while((i = fgetc(stdin)) != EOF) // ctrl + d
	{
		unsigned char c = (unsigned char) i;
		int ascii = (int) c;

		++nbCaractereTotal;
		textChiffre = (char *) realloc(textChiffre, sizeof(char) * nbCaractereTotal);
		textChiffre[nbCaractereTotal - 1] = c;
		//printf("%c = %d\n", c, ascii);
	}

/*
  text = textChiffre;
  for (i = 0; text[i] != '\0'; ++i)
  {
    int ascii = (int) text[i];
    if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
    {
      ascii = (int)text[i] + clef;

      while (ascii < ASCII_MAJ_DEBUT)
        ascii += TAILLE_ALPHA;

      while (ascii >= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
        ascii -= TAILLE_ALPHA;

      text[i] = (char) ascii;
    }
  }*/

  return 0;
}
