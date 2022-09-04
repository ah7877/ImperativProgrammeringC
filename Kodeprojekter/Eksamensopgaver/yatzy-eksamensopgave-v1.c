#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*
Navn: Andreas Hougaard
Email: houga20@student.aau.dk
Gruppe: A310a
Studieretning: Datalogi
*/

/*enumerator, så det er nemmere at holde styr på resultaterne i scoreboard*/
enum size_of_scoreboard {sum_of_1s, sum_of_2s, sum_of_3s, sum_of_4s, sum_of_5s, sum_of_6s, bonus,
                        one_pair, two_pairs, three_of_a_kind, four_of_a_kind, 
                        small_straight, large_straight, full_house, chance, yatzy, total_points};

/*initialisering af funktioner*/
void throw_dices (int *throw, int number_of_dice);
int cmpfunc (const void * a, const void * b);
void sums (int *throw, int number_of_dice, int *scoreboard);
int calculate_specifik_sum (int *throw, int search_number, int number_of_dice);
void calculate_bonus (int *throw, int number_of_dice);
void if_one_set_of_pair (int *throw, int number_of_dice, int *scoreboard, int how_many, int catagory, int (*condition)(int*, int, int));
void if_two_set_of_pair (int *throw, int number_of_dice, int *scoreboard, int how_many_large, int how_many_small, int catagory, 
                         int (*longest_pair_condition)(int*, int, int), int (*shortest_pair_condition)(int*, int, int));
int template (int *throw, int number_of_dice, int already_found_pair, int (*condition)(int*, int, int));
int one_pair_condition (int *throw, int a, int already_found_pair);
int three_of_a_kind_condition (int *throw, int a, int already_found_pair);
int four_of_a_kind_condition (int *throw, int a, int already_found_pair);
int yatzy_condition (int *throw, int a, int already_found_pair);
void straights (int *throw, int number_of_dice, int *scoreboard, int catagory, int lower_boarder, int upper_boarder);
void calculate_chance (int *throw, int number_of_dice, int *scoreboard);
void calculate_total_points (int number_of_dice, int *scoreboard);


int main(void) {
    /*setup for programmet*/
    char flag = 'a';
    int number_of_dice = 0;
    int *throw, *scoreboard;
    srand(time(0));
    scoreboard = (int*) malloc((total_points + 1) * sizeof(int));

    while(flag != 'q'){
        /*her bestemmer brugeren hvor mange terninger, der kastes med*/
        while(number_of_dice < 5){
            /*hvis ikke jeg bruge fflush er der mulighed for at brugeren bliver fanget i et loop*/
            fflush(stdin);
            printf("\nHvor mange terninger skal der spilles med? Min. 5\n");
            scanf("%d", &number_of_dice);
        }
        /*allokere plads til arrayet hvor jeg holder de forskellige kast*/
        throw = calloc(number_of_dice, sizeof(int));

        /*finder/printer resultatet af summene 1-6*/
        sums(throw, number_of_dice, scoreboard);

        /*beregner/printer bonus*/
        calculate_bonus(scoreboard, number_of_dice);

        /*beregner højeste par*/
        printf("\nEt par:\t\t");
        if_one_set_of_pair(throw, number_of_dice, scoreboard, 2, one_pair, &one_pair_condition);

        /*her beregner jeg de højeste 2 par*/
        printf("\nTo par:\t\t");
        if_two_set_of_pair(throw, number_of_dice, scoreboard, 2, 2, two_pairs, &one_pair_condition, &one_pair_condition);

        /*beregner højeste 3 ens*/
        printf("\nTre ens:\t");
        if_one_set_of_pair(throw, number_of_dice, scoreboard, 3, three_of_a_kind, &three_of_a_kind_condition);

        /*beregner højeste 4 ens*/
        printf("\nFire ens:\t");
        if_one_set_of_pair(throw, number_of_dice, scoreboard, 4, four_of_a_kind, &four_of_a_kind_condition);
        
        /*beregner small straight (12345) værdi 15 (summen af dice)*/
        printf("\nLille straight:\t");
        straights(throw, number_of_dice, scoreboard, small_straight, 1, 5);

        /*beregner large straight (23456) værdi 20 (summen af dice)*/
        printf("\nStor straight:\t");
        straights(throw, number_of_dice, scoreboard, large_straight, 2, 6);

        /*beregner full house (3 ens + 2 ens)*/
        printf("\nFuld hus:\t");
        if_two_set_of_pair(throw, number_of_dice, scoreboard, 3, 2, full_house, &three_of_a_kind_condition, &one_pair_condition);

        /*beregner chancen*/
        calculate_chance(throw, number_of_dice, scoreboard);

        /*beregner yatzy*/
        printf("\nYatzy:\t\t");
        if_one_set_of_pair(throw, number_of_dice, scoreboard, 5, yatzy, yatzy_condition);

        /*beregner spillerens point i alt*/
        calculate_total_points(number_of_dice, scoreboard);          

        /*frigør throw allokeringen og gør klar til et ny gennemløb + tjækker jeg om brugeren vil fortsætte eller stoppe*/
        free(throw);
        number_of_dice = 0;
        printf("\n\nskriv q hvis du ikke vil spille igen, ellers skriv noget tilfældigt\n");
        scanf(" %c", &flag);
    }
    return 0;
}



/*kaster terningerne og udskriver dem*/
void throw_dices (int *throw, int number_of_dice){
    int a;
    for(a = 0; a < number_of_dice; a++){
        throw[a] = (rand() % 6) + 1;
    }
    qsort(throw, number_of_dice, sizeof(int), cmpfunc);
    for(a = 0; a < number_of_dice; a++){
        printf("%i ", throw[a]);
    }
    return;
}   

/*sorterings fuktionen, sorterer fra laveste til højeste*/
int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

/*udskriver og angiver summen af tallet vi søger efter til scoreboardet*/
void sums (int *throw, int number_of_dice, int *scoreboard){
    int a;
    for (a = 1; a < 7; a++){
        printf("\nsummen af %i:\t", a);
        scoreboard[a-1] = calculate_specifik_sum(throw, a, number_of_dice);
        printf("\t%4i point", scoreboard[a-1]);
    }
}

/*summere alle enheder af tallet vi søger efter og retunerer det, så længe der er flere end 3 af tallet*/
int calculate_specifik_sum (int *throw, int search_number, int number_of_dice){
    int a, counter = 0;
    throw_dices(throw, number_of_dice);
    for(a = 0; a < number_of_dice; a++){
        if (throw[a] == search_number)
            counter += search_number;
    }
    if (counter >= search_number * 3)
        return (counter < search_number * 5) ? counter: search_number * 5;
    else
        return 0;
}

/*beregner og skriver bonussen*/
void calculate_bonus (int *scoreboard, int number_of_dice){
    int a;
    printf("\nBonus: \t\t");
    for (a = 0; a < number_of_dice; a++)
        printf("  ");
    scoreboard[bonus] = 0;
    for(a = 0; a < 6; a++)
        scoreboard[bonus] += scoreboard[a];
    scoreboard[bonus] = (scoreboard[bonus] < 63) ? 0: 50;
    printf("\t%4i point", scoreboard[bonus]);
    return;
}

/*template til alle der kun skal bruge 1 par, af 2 eller flere
how_many er antallet af gentagelser der skal være i paret. catagory er katagorien vi slå til lige nu*/
void if_one_set_of_pair (int *throw, int number_of_dice, int *scoreboard, int how_many, int catagory, 
                         int (*condition)(int*, int, int)){
    throw_dices(throw, number_of_dice);
    scoreboard[catagory] = how_many * template(throw, number_of_dice, 0, &(*condition));
    if (catagory == yatzy && scoreboard[catagory] > 4)
        scoreboard[catagory] = 50;
    printf("\t%4i point", scoreboard[catagory]); 
    return;
}

/*template til alle beregninger der skal bruge mere end 1 par
how_many er antallet af gentagelser der skal være af i paret. catagory er katagorien vi slå til lige nu
large/small er så how_many bliver ganget på den rigtige variabel*/
void if_two_set_of_pair (int *throw, int number_of_dice, int *scoreboard, int how_many_large, int how_many_small, int catagory, 
                         int (*longest_pair_condition)(int*, int, int), int (*shortest_pair_condition)(int*, int, int)){
    int pair_1, pair_2;
    throw_dices(throw, number_of_dice);
    pair_1 = template(throw, number_of_dice, 0, &(*longest_pair_condition));
    pair_2 = template(throw, number_of_dice, pair_1, &(*shortest_pair_condition));
    if (pair_1 == 0 || pair_2 == 0)
        scoreboard[catagory] = 0;
    else
        scoreboard[catagory] = (how_many_large * pair_1) + (how_many_small * pair_2);
    printf("\t%4i point", scoreboard[catagory]);    
}

/*funktion til at finde par, med forskellige krav, så den kan bruges i alt der har noget med par at gøre*/
int template (int *throw, int number_of_dice, int already_found_pair, int (*condition)(int*, int, int)){
    int a;
    for (a = number_of_dice; a >= 2; a--){
        if ((*condition)(throw, a, already_found_pair))
            return  throw[a-1];
    }
    return 0;
}

/*betingelsen for et par, som ikke er fundet endu + lidt for at hjælp til fuld hus*/
int one_pair_condition (int *throw, int a, int already_found_pair){
    return throw[a-1] != already_found_pair && throw[a-1] == throw[a-2];
}

/*betingelsen for 3 ens, som ikke er fundet endu + lidt for at hjælp til fuld hus*/
int three_of_a_kind_condition (int *throw, int a, int already_found_pair){
    return throw[a-1] != already_found_pair && throw[a-1] == throw[a-2] && throw[a-2] == throw[a-3];
}

/*betingelsen for 4 ens*/
int four_of_a_kind_condition (int *throw, int a, int already_found_pair){
    return throw[a-1] == throw[a-2] && throw[a-2] == throw[a-3] && throw[a-3] == throw[a-4];
}

/*betingelsen for 5 ens*/
int yatzy_condition (int *throw, int a, int already_found_pair){
    return throw[a-1] == throw[a-2] && throw[a-2] == throw[a-3] && throw[a-3] == throw[a-4] && throw[a-4] == throw[a-5];
}

/*beregner og udskriver en dynamisk straight, tjækker om alle tal fra nedre til øvre grænse er i slaget og ligger point til undervejs*/
void straights (int *throw, int number_of_dice, int *scoreboard, int catagory, int lower_boarder, int upper_boarder){
    bool flag = true;
    int a, b, point_counter = 0;
    throw_dices(throw, number_of_dice);
    for (a = lower_boarder; a <= upper_boarder; a++){
        for (b = 0; b < number_of_dice; b++){
            if(throw[b] == a){
                flag = true;
                break;
            }
            else
                flag = false;
        }
        if (flag == false)
            break;
        point_counter += a;
    }

    if(flag == true)
        scoreboard[catagory] = point_counter;
    else
        scoreboard[catagory] = 0;
    printf("\t%4i point", scoreboard[catagory]); 
    return;
}

/*beregner og udskriver chancen*/
void calculate_chance (int *throw, int number_of_dice, int *scoreboard){
    int a;
    printf("\nChancen:\t");
    scoreboard[chance] = 0;
    throw_dices(throw, number_of_dice);
    for(a = 0; a < 5; a++)
        scoreboard[chance] += throw[(number_of_dice - 1) - a];
    printf("\t%4i point", scoreboard[chance]);  
}

/*beregner og udskriver alle point sammenlagt*/
void calculate_total_points (int number_of_dice, int *scoreboard){
    int a;
    printf("\n\nI alt:\t\t");
    for (a = 0; a < number_of_dice; a++)
        printf("  ");
    scoreboard[total_points] = 0;
    for(a = 0; a < total_points; a++)
        scoreboard[total_points] += scoreboard[a];
    printf("\t%4i point", scoreboard[total_points]); 
}