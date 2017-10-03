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
void chercheClef(char *text, int* clef, char tableauFreqFrance[], char tableauFreqtext[]);

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

	// affiche l'alphabet, le nb de chaque lettre, la frequence en pourcentage de chaque lettre precision 0.001
	int i = 0;
	printf("alphaFreqNormal nombreChiffre alphaFreqChiffree\n");
	for (i=0; i<TAILLE_ALPHA; ++i)
		printf("%c %d %c \n", tableauFreqFrance[i], nbLettre[i], tableauFreqtext[i]);

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
		int ascii = (int) c;
		if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
				++nbLettre[ascii - ASCII_MAJ_DEBUT];
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

	int i = 0;
	for (i=0; i<TAILLE_ALPHA; ++i)
		printf(" %d \n",nbLettre[i]);

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

void chercheClef(char *text, int *clef, char tableauFreqFrance[], char tableauFreqtext[])
{
	// calcule la clef en fonction de la frequence des lettres
	char *copieText;
	int trouver = 0, i = 0, j = 0;
	do
	{
		// on estime que la lettre la plus presente est la lettre la plus presente dans l'alphabet francais si ce n'ai pas le cas on passe a la lettre suivante pour calculer l'ecart
		*clef =  (int)tableauFreqtext[0] - (int)tableauFreqFrance[i];
		++i;

		// on modifie le texte chiffre avec la clef pour afficher le texte origiginal
		copieText = text;
		for (j = 0; copieText[j] != '\0'; ++j)
		{
			int ascii = (int) copieText[j];
			if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
			{
				ascii = (int)copieText[j] + *clef;

				while (ascii < ASCII_MAJ_DEBUT)
					ascii += TAILLE_ALPHA;

				while (ascii >= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
					ascii -= TAILLE_ALPHA;

				copieText[j] = (char) ascii;
			}
		}

		// affichage le texte dechiffre
		printf("\n%s\n", text);
		printf("\n%d\n", *clef);

		trouver = 1;
	}while(fgetc(stdin) != EOF);
}

void modificationText(char *text, int *clef)
{
  int i = 0;
  for (i = 0; text[i] != '\0'; ++i)
  {
    int ascii = (int) text[i];
    if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
    {
      ascii = (int)text[i] + *clef;

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
}

void affichageClef(int *clef)
{
  printf("############ \n");
  printf("%d\n", *clef);
}

void viderBuffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

int chercheMot(char *tableau)
{
    FILE *fichier = NULL;
    char car = 0;   //Contient temporairement chaque caractère du fichier dico.txt
    long i = 0;

    fichier = fopen("dico.txt", "r+");

    while(car != EOF)
    {
        car = fgetc(fichier);   //On lit un caractère de dico.txt

        if(tableau[i] == car)   //Si le 1er caractère correspond, on augmente i pour tester le second caractère au tour suivant
        {
            i++;
            if(tableau[i] == '0' && fgetc(fichier) == '\n') //Si cette condition est vraie, c'est que la chaine est déja dans le dico
            {
                return 1;
            }
            fseek(fichier, -1, SEEK_CUR);   //Si la condition précedente est fausse, on remet la position dans le fichier tel qu'elle était avant cette condition
        }

        else
        {
            i = 0;
        }
    }

    return 0;   //Si on a rien trouvé, on retourne 0
}
