 #include <stdio.h>

int main (void)
{
  system ("cat /proc/cpuinfo");

  printf("nb processeurs physiques :\n");
  printf("nb de coeurs physiques :\n");
  printf("nb de coeurs logiques :\n");

  
  system("cat /proc/cpuinfo | grep processor | wc -l");
  return 0;
}
