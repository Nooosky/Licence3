/*DEPUIS LONGTEMPS, J'AI LA MANIE DE GLISSER DES JEUX
DE MOTS LORS DES CONVERSATIONS.
LES GENS DE MON ENTOURAGE NE POUVANT PLUS ME SUPPORTER, JE
ME SUIS MIS A LES ECRIRE.
LORSQUE JE SUIS ENTRE A L'ECOLE POLYTECHNIQUE DE MONTREAL,
J'AI EU L'OCCASION D'ECRIRE UNE CHRONIQUE HEBDOMADAIRE DANS
LE JOURNAL ETUDIANT, LE ``POLYSCOPE''.
CE SONT CES TEXTES QUI SE RETROUVENT DANS LE PRESENT RECUEIL.
ILS ONT BIEN SUR ETE LEGEREMENT MODIFIES, POUR LES RENDRE
PLUS COMPREHENSIBLES POUR QUELQU'UN QUI N'A PAS ETUDIE A
L'ECOLE POLYTECHNIQUE.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* constante */
#define TAILLE_ALPHA 26
#define ASCII_MAJ_DEBUT 65


/* prototype */
// test le nombre d,argument
void testArgument(int argc);

// lit le text pour le mettre dans un tableau de caractere
void lectureText(char *text, int *nbLettre);

// modifie le tableau de caractere en fonction de la clef
void modificationText(char *text, int clef);

// affiche le text
void affichageText(char *text);


/* main */
int main(int argc, char *argv[])
{
	testArgument(argc);

	char *text = (char *) malloc(sizeof(char));
	int *nbLettre = (int *) calloc(TAILLE_ALPHA, sizeof(int));

	lectureText(text, nbLettre);

  affichageText(text);

	printf("alphaFreqNormal nombreChiffre alphaFreqChiffree\n");
	for (i=0; i<TAILLE_ALPHA; ++i)
		printf("%c %d %c \n", tableauFreq[i], nbChaqueLettre[i], tableauFreqChiffre[i]);
/*
	// tableau qui represente les lettres les plus presentes dans la langue francais par ordre decroissant
	char tableauFreq[] = {'E','S','A','N','T','I','R','U','L','O','D','C','P','M','Q','V','G','F','B','H','X','Y','J','Z','K','W'};
	// tableau de l'alphabet qui servira a donner l'ordre des lettres les plus presentes dans le message chiffre
	char tableauFreqChiffre[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	// trie le tableau par ordre decroissant de la frequence de lettre utilise
	int j = TAILLE_ALPHA, k = 0, tmpi = 0;
	char tmpc = ' ';
	for(j = TAILLE_ALPHA; j != 0; --j)
	{
		for(k = 0; k < j; ++k)
		{
			if(nbChaqueLettre[k] < nbChaqueLettre[k + 1])
			{
				tmpi = nbChaqueLettre[k];
				tmpc = tableauFreqChiffre[k];

				nbChaqueLettre[k] = nbChaqueLettre[k + 1];
				tableauFreqChiffre[k] = tableauFreqChiffre[k + 1];

				nbChaqueLettre[k + 1]  = tmpi;
				tableauFreqChiffre[k + 1] = tmpc;
			}
		}
	}

	// affiche l'alphabet, le nb de chaque lettre, la frequence en pourcentage de chaque lettre precision 0.001
	printf("alphaFreqNormal nombreChiffre alphaFreqChiffree\n");
	for (i=0; i<TAILLE_ALPHA; ++i)
		printf("%c %d %c \n", tableauFreq[i], nbChaqueLettre[i], tableauFreqChiffre[i]);


	// calcule la clef en fonction de la frequence des lettres
	char *text;
	int clef = 0, trouver = 0;
	i = 0;
	do
	{
		// on estime que la lettre la plus presente est la lettre la plus presente dans l'alphabet francais si ce n'ai pas le cas on passe a la lettre suivante pour calculer l'ecart
		clef =  (int)tableauFreq[i] - (int)tableauFreqChiffre[0];
		++i;

		// on modifie le texte chiffre avec la clef pour afficher le texte origiginal
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
		}

		// affichage le texte dechiffre
		printf("\n%s\n", text);

		trouver = 1;
	}while(fgetc(stdin) != EOF);

	// affiche la clef
	printf("%d \n", clef);
*/
	free(text);

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

void lectureText(char *text, int *nbLettre)
{
  int i = 0, nb = 0;
  while((i = fgetc(stdin)) != EOF) // ctrl + d
  {
		// ajoute caractere au tableau de caractere
    unsigned char c = (unsigned char) i;
    text = (char *) realloc(text, sizeof(char) * ++nb);
    text[nb - 1] = c;

		// incremente le tableau du nombre de lettre pour connaitre le nombre present de chaque lettre
		int ascii = (int) c;
		if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
				++nbLettre[ascii - ASCII_MAJ_DEBUT];
  }
}

void modificationText(char *text, int clef)
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

void affichageText(char *text)
{
  printf("############ \n");
  printf("%s\n", text);
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
