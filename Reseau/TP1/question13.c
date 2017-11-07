#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

//CONST
#define _REQUIRED_ARGUMENTS 2                   //Required number of arguments
#define _USAGE "Usage : ./question13 *nb_desired_cpu*"

int main(int argc, char* argv[])
{

	int required_processor = 0;
    pid_t pid = getpid();
    cpu_set_t my_set;
    int i, j, ret;

	printf("%d\n", atoi(argv[1]));

	if(argc != _REQUIRED_ARGUMENTS){
        fprintf(stderr, "Not the right number of arguments...");
        fprintf(stderr, "%s", _USAGE);
        return -1;
    }else if(atoi(argv[1]) > (int) sysconf(_SC_NPROCESSORS_ONLN) || atoi(argv[1]) <= 0){
		fprintf(stderr, "Processor does not exist, please enter a valid number between 1 and %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
		return -1;
	}else{
		required_processor = atoi(argv[1]);
	}

    CPU_ZERO(&my_set);
    CPU_SET(required_processor, &my_set);

    ret = sched_setaffinity(0, sizeof(my_set), &my_set);

	printf("pid %d is now running on the CPU number %d\n", pid, sched_getcpu());

	for(i = 0; i<99999; i++){
		for(j=0; j<9000; ++j){
			i+j;
		}
	}
	

    return 0;
}
