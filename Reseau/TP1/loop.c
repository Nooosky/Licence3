#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int fake_count = 0;
    int i, j = 0;

    for (i = 0; i< 999999; ++i){
	for (j = 0; j < 999999; ++j){
		fake_count = (i+j)*(i-j);
	}
    }
    return 0;
}
