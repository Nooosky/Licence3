#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[])
{
  if (argc != 3)
  {
      fprintf(stderr, "USAGE: ./main <clef> \n");
      exit(1);
  }

  char *chaine = argv[1];

  return 0;
}
