#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(void)
{
    int n = 100;
    int *random_numbers;
    random_numbers = malloc(n * sizeof(int));
    srand(time(0));

    for (int a = 0; a < n; a++){
        random_numbers[a] = rand() % 1000;
    }

    qsort(random_numbers, n, sizeof(int), cmpfunc);

    for (int a = 0; a < n; a++){
        printf("%d\n", random_numbers[a]);
    }
    
    return 0;
}