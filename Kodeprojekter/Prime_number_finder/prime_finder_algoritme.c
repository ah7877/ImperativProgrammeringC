#include <stdio.h>
#include<stdbool.h>
#include <time.h>
#include <math.h>

int main()
{
    int highest_number, check_number = 2;
    printf("hvor stort skal det største primetal højest være?\n");
    scanf("%d", &highest_number);
    bool numbers[highest_number + 1];

    numbers[0] = false;
    numbers[1] = false;
    for(int a = 2; a + 1 <= highest_number; a++){
        numbers[a] = true;
    }

    struct timespec startTime, endTime;
    clock_gettime(CLOCK_MONOTONIC, &startTime);

    while (check_number <= sqrt(highest_number)){
        if(numbers[check_number] == true){
            for(int a = 2 * check_number; a <= highest_number; a = a + check_number){
                numbers[a] = false;
            }
        }
        check_number++;
    }

    clock_gettime(CLOCK_MONOTONIC, &endTime);
    double duration = (double)(endTime.tv_sec-startTime.tv_sec) +
                    1e-9*(endTime.tv_nsec-startTime.tv_nsec);

    int b = 1;
    for(int a = 0; a <= highest_number; a++){
        if(numbers[a] == true){
            printf("\n%d\t%d", b, a);
            b++;
        }
    }
    printf("\ntid: %.7fs\n", duration);

    return 0;
}