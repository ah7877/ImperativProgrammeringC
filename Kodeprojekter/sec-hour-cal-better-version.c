#include <stdio.h>

int main (void)
{
    const int sec_in_min = 60;
    const int sec_in_hour = 60 * sec_in_min;

    int input, rest;
    
    printf("Indtatst sekunder:");
    scanf(" %d", &input);

    int hour = input/sec_in_hour;
    rest = input % sec_in_hour;

    int min = rest/sec_in_min;
    rest = rest % sec_in_min;

    printf((hour > 0) ? (min > 0 && rest > 0) ? "%d timer, " : "%d timer." : "", hour);
    printf((min > 0) ? (rest > 0) ? "%d minutter, " : "%d minutter." : "", min);
    printf((rest > 0) ? "%d sekunder." :"", rest);
    scanf(" %d", &input);
    return 0;
}