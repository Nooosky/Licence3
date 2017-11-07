#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* macro */
#define TAILLE_ALPHA 26


/* prototype */
//verifie le nombre d'arguement passe dans le programme
void testArgument(int* argc);

//lit l'entree standard et enregistre tout dans text
void lectureText(char** text);

//cherche la clef de dechiffrage
void chercheClef(char** text, char** clef);

//modifie d diamondle tableau en fonction de la clef
void modificationText(char** text, char** clef);

//affiche le contenu d'un tableau de char
void affichageText(char** text);

// affiche la clef
void affichageClef(char** clef);

//vide le buffer d'entree
void viderBuffer(void);


/* main */
int main(int argc, char *argv[])
{
  testArgument(&argc);

  char *clef = NULL;
  char *text = NULL;

  lectureText(&text);
  chercheClef(&text, &clef);
  modificationText(&text, &clef);
  affichageText(&text);
  affichageClef(&clef);

  free(clef);
  free(text);

  viderBuffer();
  return 0;
}

/* definition des fonctions */
void testArgument(int* argc)
{
  if (*argc != 1)
  {
      fprintf(stderr, "USAGE: ./main <clef> \n");
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

void chercheClef(char** text, char** clef)
{
  // cherche la longueur de la clef avec l'indice de coincidence en cherchant une lettre sur 2, puis une lettre sur 3 etc ..
  int i = 0, pas = 0;
  double indiceDeCoincidence = 0.0;
  int *nbLettre = (int *) calloc(TAILLE_ALPHA, sizeof(int));
  do
  {
    indiceDeCoincidence = 0.0;
    pas++;
    // remet a zero le tabeau qui conte les lettres
    int j = 0;
    for (j = 0; j < TAILLE_ALPHA; ++j)
      nbLettre[j] = 0;

    // incremente le tableau pour savoir le nombre de chaque lettre presente en fonction du pas
    // et incremente le nombre de lettre total presente en fonction du pas
    int pasLettre = -1, nombreTotalLettre = 0;
    for (i = 0; (*text)[i] != '\0'; ++i)
      if('A' <= (*text)[i] && (*text)[i] <= 'Z')
      {
        ++pasLettre;
        if(pasLettre % pas == 0)
        {
          ++nbLettre[(*text)[i] - 'A'];
          ++nombreTotalLettre;
        }
      }

    // calcul d'indice de coincidence
    for (i = 0; i < TAILLE_ALPHA; ++i)
      indiceDeCoincidence += (nbLettre[i] * (nbLettre[i] - 1))/(double)(nombreTotalLettre * (nombreTotalLettre - 1));

    printf("IC = %f, pas = %d\n", indiceDeCoincidence, pas);
  }
  //while (indiceDeCoincidence <= 0.060); // on arrete quand on trouve in indice de coincidence > a 0.060
  while(fgetc(stdin) != EOF);

  int tailleDeLaClef = pas;
  *clef = (char *) malloc(tailleDeLaClef * sizeof(char));
  for (i=0; i<tailleDeLaClef; ++i)
  {
    // remet a zero le tabeau qui conte les lettres
    int j = 0;
    for (j = 0; j < TAILLE_ALPHA; ++j)
      nbLettre[j] = 0;

    // incremente le nombre de lettre pour savoir le nombre de lettre pour chaque morceau de clef
    int pasLettre = -1;
    for (j = 0; (*text)[j] != '\0'; ++j)
        if('A' <= (*text)[j] && (*text)[j] <= 'Z')
        {
          ++pasLettre;
          if(pasLettre % tailleDeLaClef == i)
            ++nbLettre[(*text)[j] - 'A'];
        }

    // on cherche la lettre la plus utilise et on la remplace par 'E' pour trouver le decalage effectue
    int nombre = 0;
    for (j = 0; j < TAILLE_ALPHA; ++j)
      if (nombre < nbLettre[j])
        nombre = nbLettre[j];

    // montre la clef proposer
    for (j = 0; j < TAILLE_ALPHA; ++j)
      if (nombre == nbLettre[j])
      {
        char caractere = j + 'A' - ('E' - 'A');
        while (caractere < 'A')
          caractere += TAILLE_ALPHA;
        while (caractere > 'Z')
          caractere -= TAILLE_ALPHA;

        printf("%c ",caractere);
      }
    printf("\n");
  }

  // boucle pour demander a l'utilisateur la clef a utiliser
  char* textCopy = (char *)malloc(strlen(*text) * sizeof(char));
  strcpy(textCopy, *text);
  do
  {
    // demande a l'utilisateur de rentrer la clef
    printf("Saisie de la clef : ");
    scanf("%s", *clef);

    // on modifie le texte chiffre avec la clef pour afficher le texte
    modificationText(&(*text), &(*clef));

    // affichage le texte dechiffre avec la clef utilise
    affichageText(&(*text));
    affichageClef(&(*clef));

    // remet le text original
    strcpy(*text, textCopy);
  }while(fgetc(stdin) != EOF);

  free(nbLettre);
}

void modificationText(char** text, char** clef)
{
  int i = 0, j = 0;
  for (i = 0; (*text)[i] != '\0'; ++i)
  {
    if('A' <= (*text)[i] && (*text)[i] <= 'Z')
    {
      (*text)[i] -= ((int)(*clef)[j] - 'A');
      ++j;
      if (j > strlen(*clef) - 1)
        j = 0;

      while ((*text)[i] < 'A')
		    (*text)[i] += TAILLE_ALPHA;
      while ((*text)[i] > 'Z')
		    (*text)[i] -= TAILLE_ALPHA;
    }
  }
}

void affichageText(char** text)
{
  printf("############ \n");
  printf("%s\n", *text);
	printf("############ \n");
}

void affichageClef(char** clef)
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
