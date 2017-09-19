#include <stdio.h>
#include <stdlib.h>

#define TAILLE_ALPHA 26
#define ASCII_MAJ_DEBUT 65

int main(int argc, char *argv[])
{

	int nbCaractere = 0;
	char * text = (char *) malloc(sizeof(char));
	int nbChaqueLettre[TAILLE_ALPHA] = {0};

	int i;
	while((i = fgetc(stdin)) != EOF) // ctrl + d
	{
		unsigned char c = (unsigned char) i;
		int ascii = (int) c;

		if(ASCII_MAJ_DEBUT <= ascii && ascii <= (ASCII_MAJ_DEBUT + TAILLE_ALPHA))
		{
				++nbCaractere;
				++nbChaqueLettre[ascii - ASCII_MAJ_DEBUT];
		}

		printf("%c = %d\n", c, ascii);
	}

	printf("\nnbCaractere = %d\n\n", nbCaractere);

	// affiche l'alphabet
	for (i=0; i<TAILLE_ALPHA; ++i)
		printf("%c ", (char) (i + ASCII_MAJ_DEBUT));
	printf("\n");

	// affiche le nb de chque lettre
	for (i=0; i<TAILLE_ALPHA; ++i)
		printf("%d ", nbChaqueLettre[i]);
	printf("\n");

	// affichele la frequence en pourcentage de chaque lettre precision 0.001
	for (i=0; i<TAILLE_ALPHA; ++i)
		printf("%f ", nbChaqueLettre[i] / (float)nbCaractere * 100);
	printf("\n");

	return 0;
}
