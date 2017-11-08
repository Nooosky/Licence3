#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	long nb_usable_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	
	printf("Nb usable processors : %ld\n", nb_usable_cpus);

    return 0;
}
