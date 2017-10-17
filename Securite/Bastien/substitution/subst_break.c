#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* macro */
#define TAILLE_ALPHA 26


/* prototype */
//verifie le nombre d'arguement passe dans le programme
void testArgument(int argc);

//lit l'entree standard et enregistre tout dans text
void lectureText(char **text);

// incremente un tableau pour savoir le nombre de lettre presente dans le text
void incrementeLeNombreDeLettre(char *text, int *nbLettre);

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

  char *clef = (char *) malloc(TAILLE_ALPHA * sizeof(char));
  char *text = NULL;
  int *nbLettre = (int *) calloc(TAILLE_ALPHA, sizeof(int));
  // tableau qui represente les lettres les plus presentes dans la langue francais par ordre decroissant
	char tableauFreqFrance[] = "EINTASLROUCMDPQFGBVHYXJKZW";
	// tableau de l'alphabet qui servira a donner l'ordre des lettres les plus presentes dans le message chiffre
	char tableauFreqtext[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  lectureText(&text);
	incrementeLeNombreDeLettre(text, nbLettre);
	trieDecroissant(nbLettre, tableauFreqtext);
	chercheClef(text, clef, tableauFreqFrance, tableauFreqtext);
  modificationText(text, clef);
  affichageText(text);
  affichageClef(clef);

  free(clef);
  free(text);
  free(nbLettre);

  viderBuffer();
  return 0;
}

/* definition des fonctions */
void testArgument(int argc)
{
  if (argc != 1)
  {
      fprintf(stderr, "USAGE: ./main \n");
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

		(*text)[i++] = c;	// ajoute le caractere au text
	}

	// si stdin n'est pas vide on reduit l'allocation a la bonne taille pour ne pas gacher de la memoire
	if (*text != NULL)
	{
		(*text)[i] = '\0';
		*text = realloc(*text, strlen(*text) + 1);
	}
}

void incrementeLeNombreDeLettre(char *text, int *nbLettre)
{
	int i = 0;
	for (i = 0; text[i] != '\0'; ++i)
	{
		if('A' <= text[i] && text[i] <= 'Z')
				++nbLettre[text[i] - 'A'];
	}
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
	char *textCopy = (char *)malloc(strlen(text) * sizeof(char));
	strcpy(textCopy, text);

  // on estime que la lettre la plus presente est la lettre la plus presente dans l'alphabet francais
  // et on construit l'alphabet en fonction de cette frequence
  int i = 0;
  for(i = 0; i < strlen(tableauFreqFrance); ++i)
    clef[tableauFreqFrance[i] - 'A'] = tableauFreqtext[i];

	do
	{
		// on modifie le texte chiffre avec la clef pour afficher le texte
		modificationText(text, clef);

		// affichage le texte dechiffre avec la clef utilise
		affichageText(text);
		affichageClef(clef);

    // affiche la clef utilise
    for(i = 0; i < strlen(clef); ++i)
      printf(" %c %d \n", clef[i], i);

    // inverse les 2 lettres d'index le numero donne par l'utilisateur
    printf("\n echange lettre par indice : \n");
    char indice1 = getchar();
    char indice2 = getchar();
    char tampon = clef[atoi(&indice1)];
    clef[atoi(&indice1)] = clef[atoi(&indice2)];
    clef[atoi(&indice2)] = tampon;

		// remet le text original
		strcpy(text, textCopy);

	}while(fgetc(stdin) != EOF);
}

void modificationText(char *text, char *clef)
{
  int i = 0;
  for (i = 0; text[i] != '\0'; ++i)
  {
    if('A' <= text[i] && text[i] <= 'Z')
    {
      text[i] = (char)(strchr(clef,text[i]) - clef + 'A');

      while (text[i] < 'A')
		    text[i] += TAILLE_ALPHA;
      while (text[i] > 'Z')
		    text[i] -= TAILLE_ALPHA;
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
  printf("%s\n", clef);
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
