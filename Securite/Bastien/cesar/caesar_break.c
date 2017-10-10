/*
GHSXLV ORQJWHPSV, M'DL OD PDQLH GH JOLVVHU GHV MHXA
GH PRWV ORUV GHV FRQYHUVDWLRQV.
OHV JHQV GH PRQ HQWRXUDJH QH SRXYDQW SOXV PH VXSSRUWHU, MH
PH VXLV PLV D OHV HFULUH.
ORUVTXH MH VXLV HQWUH D O'HFROH SROBWHFKQLTXH GH PRQWUHDO,
M'DL HX O'RFFDVLRQ G'HFULUH XQH FKURQLTXH KHEGRPDGDLUH GDQV
OH MRXUQDO HWXGLDQW, OH ``SROBVFRSH''.
FH VRQW FHV WHAWHV TXL VH UHWURXYHQW GDQV OH SUHVHQW UHFXHLO.
LOV RQW ELHQ VXU HWH OHJHUHPHQW PRGLILHV, SRXU OHV UHQGUH
SOXV FRPSUHKHQVLEOHV SRXU TXHOTX'XQ TXL Q'D SDV HWXGLH D
O'HFROH SROBWHFKQLTXH.
*/

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
void chercheClef(char text[], int* clef, char tableauFreqFrance[], char tableauFreqtext[]);

//cherche le mot si il est present dans le dictionnaire
int chercheMotDansDico(char *tableau);

//modifie le tableau en fonction de la clef
void modificationText(char *text, int *clef);

//affiche le contenu d'un tableau de char
void affichageText(char *text);

// affiche la clef
void affichageClef(int *clef);

//vide le buffer d'entree
void viderBuffer(void);


/* main */
int main(int argc, char *argv[])
{
	testArgument(argc);

	int *clef = (int *) malloc(sizeof(int));
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

void chercheClef(char text[], int *clef, char tableauFreqFrance[], char tableauFreqtext[])
{
	// calcule la clef en fonction de la frequence des lettres
	char *textCopy = (char *)malloc(strlen(text) * sizeof(char));
	strcpy(textCopy, text);

	int compteurMot = 0, compteurMotTrouve = 0, i = 0;
	do
	{
		compteurMot = 0, compteurMotTrouve = 0;

		// on estime que la lettre la plus presente est la lettre la plus presente dans l'alphabet francais si ce n'ai pas le cas on passe a la lettre suivante pour calculer l'ecart
		*clef =  (int)tableauFreqtext[0] - (int)tableauFreqFrance[i];
		++i;

		// on modifie le texte chiffre avec la clef pour afficher le texte origiginal
		int j = 0;
		for (j = 0; text[j] != '\0'; ++j)
		{
			if(ASCII_MAJ_DEBUT <= text[j] && text[j]  < (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
			{
				text[j] -= *clef;

				while (text[j] < ASCII_MAJ_DEBUT)
					text[j] += TAILLE_ALPHA;

				while (text[j] >= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
					text[j] -= TAILLE_ALPHA;
			}
		}

		// affichage le texte dechiffre
		affichageText(text);
		affichageClef(clef);

		// verifie la presence des mot dans le dictionnaire
		/*
		char * pch = strtok (text,"\n ,.-'`:;\"");
		while (pch != NULL)
		{
			if ((int)strlen(pch) != 1)
			{
				compteurMot++;
				if(chercheMotDansDico(pch))
					compteurMotTrouve++;
			}

			pch = strtok (NULL, "\n ,.-'`:;\"");

		}*/
		strcpy(text, textCopy);
	//}while(i < TAILLE_ALPHA && compteurMotTrouve < (int)((double)compteurMot * 0.75));

	}while(fgetc(stdin) != EOF);
}

int chercheMotDansDico(char *tableau)
{
    FILE *fichier = NULL;
    char car = 0;
    long i = 0;

    fichier = fopen("../dico.txt", "r+");

    while(!feof(fichier))
    {
        car = fgetc(fichier);
				//printf("%c == %c\n",car, tableau[i]);

        if(tableau[i] == car)
        {
            i++;
            if(tableau[i] == '\0' && fgetc(fichier) == '\n')
						{
							fclose(fichier);
              return 1;
						}
            //fseek(fichier, -1, SEEK_CUR);
        }
        else
				{
          i = 0;
				}
    }

		fclose(fichier);
    return 0;
}

void modificationText(char *text, int *clef)
{
  int i = 0;
  for (i = 0; text[i] != '\0'; ++i)
  {
    if(ASCII_MAJ_DEBUT <= text[i] && text[i] < (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
    {
      text[i] -= *clef;

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
	printf("############ \n");
}

void affichageClef(int *clef)
{
  printf("############ \n");
  printf("%d\n", *clef);
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
