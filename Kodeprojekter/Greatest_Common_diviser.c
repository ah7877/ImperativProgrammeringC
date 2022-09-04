#include <stdio.h>

//troede at "se her" linket i opgaven var til et eksempel på hvordan algoritmen virkede og ikke programmet, det derfor det ligner

int main()
{
    //jeg initialiserer mine variabler
    int a = 0, b = 0, big, small, remainder;

    //loopet forhindre brugeren i at bruge tal der er <=0 i algoritmen, da det ikke er sikkert den vil virke med dette
    while(a <= 0 || b <= 0)
    {
        //jeg assigner brugerens tal til variablerne a og b
        printf("Skriv 2 tal du gerne vil finde den største fælles divisor til, tallende må ikke være 0 eller mindre \nTal nr. 1 = ");
        scanf("%d", &a);
        printf("Tal nr. 2 = ");
        scanf("%d", &b);
    }

    //jeg finder ud af hvilket tal der er størst, og assigner dem til henholdsvis big og small
    small = (a <= b) ? a : b;
    big = (a >= b) ? a : b ;

    //her kører eulers algoritme, som stopper når small er mindre end 0
    while(small > 0)
    {
        remainder= big % small;
        big = small;
        small = remainder;
    }
    //her printer jeg største fælles deviser
    printf("Største fælles divisor er %d", big);
    //scanf er der for at programmet kan læses hvis det køres "stand alone"
    scanf("%d", &a);
    return 0;
}