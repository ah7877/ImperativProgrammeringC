#include <stdio.h>

int main (void)
{
    const int sec_in_min = 60;
    const int sec_in_hour = 60 * sec_in_min;
    const int sec_in_day = 24 * sec_in_hour;
    const int sec_in_week = 7 * sec_in_day;

    int input, rest;
    
    printf("Indtatst sekunder:");
    scanf(" %d", &input);

    int week = input/sec_in_week;
    rest = input % sec_in_week;

    int day = rest/sec_in_day;
    rest = rest % sec_in_day;

    int hour = rest/sec_in_hour;
    rest = rest % sec_in_hour;

    int min = rest/sec_in_min;
    rest = rest % sec_in_min;

    printf("%d uger, %d dage, %d timer, %d minutter, %d sekunder", week, day, hour, min, rest);
    scanf(" %d", &input);
    return 0;
}