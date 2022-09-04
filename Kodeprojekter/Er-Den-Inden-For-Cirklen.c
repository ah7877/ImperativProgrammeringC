#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DELTA 0.00001

int main(void)
{
    double x, y, r, res, hyp;
    printf("Angiv en radius for en cirkel \n");
    scanf(" %lf", &r);
    printf("\nGiv et punkt, og jeg fortæller om den er inden for cirklen \n");
    printf("\nvi starter med x koordinaten \n");
    scanf(" %lf", &x);
    printf("\nog nu y koordinaten \n");
    scanf(" %lf", &y);
    printf("\n");

    res = x*x + y*y;
    hyp = r*r;

    printf((res < (hyp - DELTA)) ? "Punktet er inden for cirklen\n" : (res > (hyp + DELTA)) ? "Punktet er uden for cirklen\n" : "Punktet er på cirklens perifiri\n");
    scanf(" %lf", &x);
    return 0;
}