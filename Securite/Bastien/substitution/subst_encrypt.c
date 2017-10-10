#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* macro */
#define TAILLE_ALPHA 26
#define ASCII_MAJ_DEBUT 65


/* prototype */
//verifie le nombre d'arguement passe dans le programme
void testArgument(int argc);

//test de la clef si elle comprend bien 26 caractere
void testClef(char * clef);

//lit l'entree standard et enregistre tout dans text
void lectureText(char** text);

//modifie le tableau en fonction de la clef
void modificationText(char *text, char *clef);

//affiche le contenu d'un tableau de char
void affichageText(char *text);

//vide le buffer d'entree
void viderBuffer(void);

/* main */
int main (int argc, char *argv[])
{
  testArgument(argc);
  testClef(argv[1]);

  char *clef = (char *)malloc(strlen(argv[1]) * sizeof(char));
  clef = argv[1];
  char *text = NULL;


  lectureText(&text);
  modificationText(text, clef);
  affichageText(text);

  free(text);

  viderBuffer();
  return 0;
}

/* definition des fonctions */
void testArgument(int argc)
{
  if (argc != 2)
  {
      fprintf(stderr, "USAGE: ./main <clef> \n");
      exit(1);
  }
}

//test de la clef si elle comprend bien 26 caractere
void testClef(char * clef)
{
  if (strlen(clef) != 26)
  {
      fprintf(stderr, "<clef> doit faire 26 caracteres \n");
      exit(1);
  }
}


void lectureText(char** text)
{
	int c;
	size_t p4kB = 4096, i = 0;
	void *newPtr = NULL;
	*text = (char *)malloc(p4kB * sizeof(char));

	while ((c = fgetc(stdin)) != EOF)	// EOF = ctrl+d sous Unix, ctrl+z sous Windows
	{
		if (i == p4kB * sizeof(char))	// si i vaut 4096, on a deja remplis "*text" -> On realloue 4096 char en plus
		{
			p4kB += 4096;	// ajoute 4096 a p4kB pour allouer 8128 char
			if ((newPtr = realloc(*text, p4kB * sizeof(char))) != NULL)	// tente la reallocation
        *text = (char*)newPtr;
			else // probleme d'allocation, on desalloue et on quitte le programme
			{
				free(*text);
				exit(1);
			}
		}
		(*text)[i++] = c;	// ajoute le caractere
	}

	if (*text != NULL)	// si stdin n'est pas vide
	{
		(*text)[i] = '\0';
		*text = realloc(*text, strlen(*text) + 1);	// on reduit l'allocation a la bonne taille pour ne pas gacher de la memoire
	}
	else return;	// sinon on quitte
}

void modificationText(char *text, char *clef)
{
  int i = 0;
  for (i = 0; text[i] != '\0'; ++i)
  {
    if(ASCII_MAJ_DEBUT <= text[i] && text[i] < (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
    {
      text[i] = clef[(int)text[i] - ASCII_MAJ_DEBUT];

      while (text[i] < ASCII_MAJ_DEBUT)
		  text[i] += TAILLE_ALPHA;
      while (text[i] >= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
		  text[i] -= TAILLE_ALPHA;
    }
  }
}

void affichageText(char *text)
{
  printf("############ \n");
  printf("%s\n", text);
}

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}
