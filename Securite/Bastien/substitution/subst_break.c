#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* macro */
#define TAILLE_ALPHA 26
#define ASCII_MAJ_DEBUT 65


/* prototype */
//verifie le nombre d'arguement passe dans le programme
void testArgument(int argc);

//lit l'entree standard et enregistre tout dans text
void lectureText(char** text, int *nbLettre);

// trie par ordre decroissant les 2 tableaux passes en parametre
void trieDecroissant(int *nbLettre, char *tableauFreqtext);

//cherche la clef de dechiffrage
void chercheClef(char *text, char *clef, char *tableauFreqFrance, char *tableauFreqtext);

//modifie le tableau en fonction de la clef
void modificationText(char *text, char *clef);

//affiche le contenu d'un tableau de char
void affichageText(char *text);

// affiche la clef
void affichageClef(char *clef);

//vide le buffer d'entree
void viderBuffer(void);


/* main */
int main(int argc, char *argv[])
{
  testArgument(argc);

  char *clef = NULL;
  char *text = NULL;
  int *nbLettre = (int *) calloc(TAILLE_ALPHA, sizeof(int));
  // tableau qui represente les lettres les plus presentes dans la langue francais par ordre decroissant
  char tableauFreqFrance[] = {'E','S','A','N','T','I','R','U','L','O','D','C','P','M','Q','V','G','F','B','H','X','Y','J','Z','K','W'};
  // tableau de l'alphabet qui servira a donner l'ordre des lettres les plus presentes dans le message chiffre
  char tableauFreqtext[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  lectureText(&text, nbLettre);
	trieDecroissant(nbLettre, tableauFreqtext);
	chercheClef(text, clef, tableauFreqFrance, tableauFreqtext);
  modificationText(text, clef);
  affichageText(text);
  affichageClef(clef);

  free(clef);
  free(text);

  viderBuffer();
  return 0;
}

/* definition des fonctions */
void testArgument(int argc)
{
  if (argc != 1)
  {
      fprintf(stderr, "USAGE: ./main <clef> \n");
      exit(1);
  }
}

void lectureText(char** text, int *nbLettre)
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

		// incremente le tableau du nombre de lettre pour connaitre le nombre present de chaque lettre
		if(ASCII_MAJ_DEBUT <= c && c < (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
				++nbLettre[c - ASCII_MAJ_DEBUT];
	}

	if (*text != NULL)	// si stdin n'est pas vide
	{
		(*text)[i] = '\0';
		*text = realloc(*text, strlen(*text) + 1);	// on reduit l'allocation a la bonne taille pour ne pas gacher de la memoire
	}
	else return;	// sinon on quitte
}

void trieDecroissant(int *nbLettre, char *tableauFreqtext)
{
	int j = TAILLE_ALPHA - 1, k = 0, tmpi = 0;
	char tmpc = ' ';
	for(j = TAILLE_ALPHA - 1; j != 0; --j)
	{
		for(k = 0; k < j; ++k)
		{
			if(nbLettre[k] < nbLettre[k + 1])
			{
				tmpi = nbLettre[k];
				tmpc = tableauFreqtext[k];

				nbLettre[k] = nbLettre[k + 1];

				tableauFreqtext[k] = tableauFreqtext[k + 1];

				nbLettre[k + 1]  = tmpi;
				tableauFreqtext[k + 1] = tmpc;
			}
		}
	}
}

void chercheClef(char *text, char *clef, char *tableauFreqFrance, char *tableauFreqtext)
{
  int i = 0;
  for (i = 0; text[i] != '\0';++i)

    printf("%c %c \n ", tableauFreqFrance[i], tableauFreqtext[i]);

}

void modificationText(char *text, char *clef)
{
  int i = 0;
  for (i = 0; text[i] != '\0'; ++i)
  {
    int ascii = (int) text[i];
    if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
    {
      ascii = text[i] + atoi(clef);

      while (ascii < 65)
        ascii += 26;
      while (ascii > 90)
        ascii -= 26;

      text[i] = (char) ascii;
    }
  }
}

void affichageText(char *text)
{
  printf("############ \n");
  printf("%s\n", text);
	printf("############ \n");
}

void affichageClef(char *clef)
{
  printf("############ \n");
  printf("%s\n", *clef);
	printf("############ \n");
}

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}
