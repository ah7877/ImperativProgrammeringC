#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define matches_in_turnament 182
#define teams_in_turnament 14
#define location_of_kampe_2019_2020 "kampe-2019-2020.txt"

/*
Navn: Andreas Hougaard
Email: houga20@student.aau.dk
Gruppe: A310a
Studieretning: Datalogi
*/

struct match{
    char weekday_of_match[4];
    int day_of_month;
    int month;
    double time_of_day;
    char home_team_name[4];
    char away_team_name[4];
    int home_team_goals;
    int away_team_goals;
    int number_of_spectators;
};

struct team{
    char team_name[4];
    int total_points;
    int total_goals_scored;
    int total_goals_by_opponent;
};

typedef struct match match;
typedef struct team team;

/*constructer for structen match, hvor den indlæser daata fra filen*/
match constructer_match(FILE *match_file){
    match return_this;
    fscanf(match_file, "%s %d/%d %lf %s - %s %d - %d %d",
        return_this.weekday_of_match,
        &return_this.day_of_month,
        &return_this.month,
        &return_this.time_of_day,
        return_this.home_team_name,
        return_this.away_team_name, 
        &return_this.home_team_goals,
        &return_this.away_team_goals,
        &return_this.number_of_spectators);
    return return_this;
}

/*constructer for structen teams med alt tilhørende data*/
team constructer_team(struct match *match_array, struct team *team_array){
    bool found_new_team_home = true, found_new_team_away = true;
    int a, b, c;
    team return_this;
    return_this.total_goals_by_opponent = 0;
    return_this.total_goals_scored = 0;
    return_this.total_points = 0;

    /*her finder programmet et teamnavn, som ikke allerede er i team arrayet*/
    for(a = 0; a < matches_in_turnament; a++){
        for (b = 0; b < teams_in_turnament; b++){
            if (strcmp(match_array[a].home_team_name, team_array[b].team_name) == 0){
                found_new_team_home = false;
            }
            else if (strcmp(match_array[a].away_team_name, team_array[b].team_name) == 0){
                found_new_team_away = false;
            }
        }
        if(found_new_team_home == true){
            for(c = 0; c < sizeof(match_array->home_team_name); c++)
                return_this.team_name[c] = match_array[a].home_team_name[c];
            break;
        }
        if(found_new_team_away == true){
            for(c = 0; c < sizeof(match_array->away_team_name); c++)
                return_this.team_name[c] = match_array[a].away_team_name[c];
            break;
        }
        found_new_team_home = true;
        found_new_team_away = true;
    }

    /*her har vi fundet et hold, og analyserer kampene hvor de er med i, og fylder mål og point ind
    lig mærke til at a ikke starter fra 0, dette er for at vi ikke analyserer en mansse kampe som holdet ikke er med i*/
    for(a = a; a < matches_in_turnament; a++){
        if(strcmp(match_array[a].home_team_name, return_this.team_name) == 0){
            return_this.total_goals_scored += match_array[a].home_team_goals;
            return_this.total_goals_by_opponent += match_array[a].away_team_goals;

            if(match_array[a].home_team_goals > match_array[a].away_team_goals)
                return_this.total_points += 3;
            else if(match_array[a].home_team_goals == match_array[a].away_team_goals)
                return_this.total_points += 1;
        }
        else if(strcmp(match_array[a].away_team_name, return_this.team_name) == 0){
            return_this.total_goals_scored += match_array[a].away_team_goals;
            return_this.total_goals_by_opponent += match_array[a].home_team_goals;

            if(match_array[a].home_team_goals < match_array[a].away_team_goals)
                return_this.total_points += 3;
            else if(match_array[a].home_team_goals == match_array[a].away_team_goals)
                return_this.total_points += 1;
        }
    }

    return return_this;
}

/*initialisering af funktioner*/
int sorting_algorythm (const void *a, const void *b);
void print_match_array(struct match *match_array);
void print_team_array(struct team *team_array);

int main(void) {
    struct match match_array[matches_in_turnament];
    struct team team_array[teams_in_turnament];
    FILE *match_file;
    int a;
    
    match_file = fopen(location_of_kampe_2019_2020, "r");
    
    /*her udfyldes match arrayet med informationer fra filen gemt i structs*/
    for(a = 0; a < matches_in_turnament; a++)
        match_array[a] = constructer_match(match_file);
    
    fclose(match_file);

    /*her udfyldes team arrayet med informationer om holdene, baseret på matcharrayet*/
    for(a = 0; a < teams_in_turnament; a++)
        team_array[a] = constructer_team(match_array, team_array);

    /*sorterer team arrayet*/
    qsort(team_array, teams_in_turnament, sizeof(team), &sorting_algorythm);

    /*udskriver match og team arrayet på en nem læsbar måde*/
    /*print_match_array(match_array);*/
    print_team_array(team_array);
    return 0;
}

/*sorting algoritmen, der sorterer fra højeste point på [0] plads til laveste*/
int sorting_algorythm (const void *a, const void *b){
    struct team *card_1 = (struct team*) a;
    struct team *card_2 = (struct team*) b;
    int dif_in_goals_card_1 = (card_1->total_goals_scored - card_1->total_goals_by_opponent);
    int dif_in_goals_card_2 = (card_2->total_goals_scored - card_2->total_goals_by_opponent);

    if(card_2->total_points - card_1->total_points != 0)
        return card_2->total_points - card_1->total_points;

    if(dif_in_goals_card_2 - dif_in_goals_card_1 != 0)
        return dif_in_goals_card_2 - dif_in_goals_card_1;
    
    return 0;
}

/*udksriver match arrayet, på en let læselig måde*/
void print_match_array(struct match *match_array){
    int a;
    for(a = 0; a < matches_in_turnament; a++){
        printf("\n%s\t", match_array[a].weekday_of_match);
        printf("%2d/", match_array[a].day_of_month);
        printf("%-2d\t", match_array[a].month);
        printf("%.2f\t\t", match_array[a].time_of_day);
        printf("%3s - ", match_array[a].home_team_name);
        printf("%s\t", match_array[a].away_team_name);
        printf("%d - ", match_array[a].home_team_goals);
        printf("%d\t\t", match_array[a].away_team_goals);
        printf("%5d", match_array[a].number_of_spectators);
    }
}

/*udksriver team arrayet, på en let læselig måde*/
void print_team_array(struct team *team_array){
    int a;
    printf("\n\nHold\tpoint\tmål\tmod. mål");
    for(a = 0; a < teams_in_turnament; a++){
        printf("\n%.3s\t", team_array[a].team_name);
        printf("%d\t", team_array[a].total_points);
        printf("%d\t", team_array[a].total_goals_scored);
        printf("%d\t\t", team_array[a].total_goals_by_opponent);
    }
}