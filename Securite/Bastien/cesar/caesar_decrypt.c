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
void lectureText(char *text);

// modifie le tableau de caractere en fonction de la clef
void modificationText(char *text, int clef);

// affiche le text
void affichageText(char *text);


/* main */
int main (int argc, char *argv[])
{
  testArgument(argc);
  int clef = atoi(argv[1]);

  char *text = (char *) malloc(sizeof(char));

  lectureText(text);
  modificationText(text, clef);
  affichageText(text);

  free(text);

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

void lectureText(char *text)
{
  int i = 0, nb = 0;
  while((i = fgetc(stdin)) != EOF) // ctrl + d
  {
    // ajoute caractere au tableau de caractere
    unsigned char c = (unsigned char) i;
    text = (char *) realloc(text, sizeof(char) * ++nb);
    text[nb - 1] = c;
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
      ascii = text[i] - clef;

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
