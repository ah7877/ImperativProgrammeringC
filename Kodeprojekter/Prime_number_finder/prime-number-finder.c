#include <stdio.h>
#include <time.h>
#include <math.h>

int main()
{
    int number_of_primenumbers, current_number_of_primenumbers, checking_this_number, possible_devisions;
    //double runs = 0;

    printf("Hvor mange primetal vil du have?\n");
    scanf(" %d", &number_of_primenumbers);

    int primenumbers [number_of_primenumbers];

    checking_this_number = 2;
    current_number_of_primenumbers = 0;
    possible_devisions = 0;

    for(int a = 0; a < number_of_primenumbers; a++){
        primenumbers[a] = 1;
    }
    
    struct timespec startTime, endTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);

    while(current_number_of_primenumbers < number_of_primenumbers){

        for(int a = 0; a <= current_number_of_primenumbers; a++){
            //runs++;
            if (checking_this_number % primenumbers[a] == 0){
                possible_devisions++;
                if(possible_devisions > 1){
                    break;
                }
            }
        }
        
        if(possible_devisions <= 1){
            primenumbers[current_number_of_primenumbers] = checking_this_number;
            current_number_of_primenumbers++;
        }

        possible_devisions = 0;
        checking_this_number++;
    }

    clock_gettime(CLOCK_MONOTONIC, &endTime);
    double duration = (double)(endTime.tv_sec-startTime.tv_sec) +
                    1e-9*(endTime.tv_nsec-startTime.tv_nsec);

    printf("\nDine tal er: \n");
    for(int a = 0; a < number_of_primenumbers; a++){
        printf("%d\t %d\n", a + 1, primenumbers[a]);
    }
    //printf("%lf\n", runs);
    printf("tid: %.7fs\n", duration);
    return 0;
}