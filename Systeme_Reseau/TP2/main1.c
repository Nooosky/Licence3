#include <stdio.h>

/* mult function  multiply given x to fact */
int mult(int x, int fact);
/* map function : takes a array of int of known size and uses a Func on each member of the array*/
void map(int tab[], size_t lg, int (*pFunc)(int, int), int fact);


/* main function -- mostly tests for the previous functions*/
int main()
{

    size_t lg = 5;     /*size of the array*/
    int tab[lg];        /*array of int */

    /*Initializing the array in a loop and printing the current values */
    for (int i = 0; i < lg; ++i)
    {
        tab[i] = i+1;
        printf("%d\n",tab[i]);
    }

    /* Initializing the mult function pointer in order to use it in the map function */
    int (*pMult)(int, int);
    pMult = mult;
    map(tab, lg, *pMult, 5);

    /*Verifying*/
    printf("Using map function...\n");
    for (int i = 0; i < lg; ++i)
    {
        printf("%d\n",tab[i]);
    }

    return 0;
}


int mult(int x, int fact)
{
  return  x*fact;
}

void map(int tab[], size_t lg, int (*pFunc)(int, int), int fact)
{

    /* array loop w/ use of the function func */
    for (int i = 0; i < lg; ++i)
    {
        tab[i] = (*pFunc)(tab[i], fact);
    }
}
