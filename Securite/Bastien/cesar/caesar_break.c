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

#define TAILLE_ALPHA 26
#define ASCII_MAJ_DEBUT 65

int main(int argc, char *argv[])
{

	char tableauFreq[] = {'E','S','A','N','T','I','R','U','L','O','D','C','P','M','Q','V','G','F','B','H','X','Y','J','Z','K','W'};

	int nbCaractereTotal = 0;
	char *textChiffre = (char *) malloc(sizeof(char));

	int nbChaqueLettre[TAILLE_ALPHA] = {0};
	char tableauFreqChiffre[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	// incremente le tableau de frequence et insere les caracteres dans un tableau de caracteres
	int i;
	while((i = fgetc(stdin)) != EOF) // ctrl + d
	{
		unsigned char c = (unsigned char) i;
		int ascii = (int) c;

		if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
				++nbChaqueLettre[ascii - ASCII_MAJ_DEBUT];
		++nbCaractereTotal;

		textChiffre = (char *) realloc(textChiffre, sizeof(char) * nbCaractereTotal);
		textChiffre[nbCaractereTotal - 1] = c;
		//printf("%c = %d\n", c, ascii);
	}


	//printf("%s\n", textChiffre);

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

	//correction probleme d'affichage en affichant la premiere valeur
	//printf("\n\n probleme %c\n\n", tableauFreqChiffre[0]);


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
		clef =  (int)tableauFreq[i] - (int)tableauFreqChiffre[0];
		++i;

		// analyse si bonne clef en rentrant la modification dans un autre tableau et comparant au dictionnaire
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

		printf("\n%s\n", text);

		trouver = 1;
	}while(fgetc(stdin) != EOF);

	// affiche la clef
	printf("%d \n", clef);


	free(text);

	return 0;
}
