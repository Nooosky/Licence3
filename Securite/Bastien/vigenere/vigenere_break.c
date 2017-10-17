#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* macro */
#define TAILLE_ALPHA 26


/* prototype */
//verifie le nombre d'arguement passe dans le programme
void testArgument(int argc);

//lit l'entree standard et enregistre tout dans text
void lectureText(char** text);

//cherche la clef de dechiffrage
void chercheClef(char *text, char* clef);

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

  lectureText(&text);
  chercheClef(text, clef);
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

void chercheClef(char *text, char *clef)
{
  // enelve les carateres speciaux du text
  size_t p4kB = 4096, i = 0;
  void *newPtr = NULL;
  char *textSansCaractereSpeciaux = (char *)malloc(p4kB * sizeof(char));

  int j = 0;
  for(j = 0; text[j] != '\0'; ++j)
  {
    if (i == p4kB * sizeof(char))	// si i vaut 4096, on a deja remplis "*text" -> On realloue 4096 char en plus
    {
      p4kB += 4096;	// ajoute 4096 a p4kB pour allouer 8128 char
      if ((newPtr = realloc(*textSansCaractereSpeciaux, p4kB * sizeof(char))) != NULL)	// tente la reallocation
        *textSansCaractereSpeciaux = (char*)newPtr;
      else // probleme d'allocation, on desalloue et on quitte le programme
      {
        free(*textSansCaractereSpeciaux);
        exit(1);
      }
    }
    (*textSansCaractereSpeciaux)[i++] = text[j];	// ajoute le caractere
  }

printf("%s\n",textSansCaractereSpeciaux );
/*

  char chaineATrouver[2];
  int i = 0, j = 0;
  for (i = 0; i < (strlen(text) - 2); ++i)
  {
    chaineATrouver[0] = text[i]; chaineATrouver[1] = text[i + 1];
    printf("%s\n",chaineATrouver);
    char *chaineTrouve;
    chaineTrouve = strstr(text, chaineATrouver);

    int position = 0;
    if (chaineTrouve != NULL)
    {
      position = chaineTrouve - text;
      if (position != i)
      {
        printf("%d %d %d\n", position, i, i - position);

      }
    }

    for (j = 0; j < (strlen(text) - 2); ++j)
    {
      chaine2[0] = text[j]; chaine2[1] = text[j + 1];
      printf("%s = %s\n", chaine1, chaine2);
    }



  }*/
}

void modificationText(char *text, char *clef)
{
  int i = 0;
  for (i = 0; text[i] != '\0'; ++i)
  {
    int ascii = (int) text[i];
    if('A' <= ascii && ascii <= 'Z')
    {
      ascii = text[i] + atoi(clef);

      while (ascii < 'A')
        ascii += TAILLE_ALPHA;
      while (ascii > 'Z')
        ascii -= TAILLE_ALPHA;

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
