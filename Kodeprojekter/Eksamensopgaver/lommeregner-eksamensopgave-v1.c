#include <stdio.h>
#include <math.h>

/*
Navn: Andreas Hougaard
Email: houga20@student.aau.dk
Gruppe: A310a
Studieretning: Datalogi
*/

void Run_calculator(int *dialog_flag, double akkumulatoren, int *quit_flag);
char Scan_data (double *new_number);
void Do_next_op (char sign, double new_number, double *akkumulator, int *flag);

/*sætter alle variabler op, og styrer main loopet i lommeregneren*/
int main(void) {
    char sign;
    double akkumulator = 0, new_number = 0;
    int quit_flag = 0, dialog_flag = 0;
    while (quit_flag == 0){
        Run_calculator(&dialog_flag, akkumulator, &quit_flag);
        sign = Scan_data(&new_number);
        Do_next_op(sign, new_number, &akkumulator, &quit_flag);
        Run_calculator(&dialog_flag, akkumulator, &quit_flag);
    }
    return 0;
}

/*styrer alt dialog med brugeren, hvor dialog_flag bestemmer om den spørger efter en ny operant eller udskriver resultatet*/
void Run_calculator(int *dialog_flag, double akkumulatoren, int *quit_flag){
    if(*dialog_flag == 0){
        printf("Enter operator, and an optional operand: ");
        *dialog_flag = 1;
    }
    else if (*dialog_flag == 1 && *quit_flag != 1){
        printf("\nResult so far is %f\n", akkumulatoren);
        *dialog_flag = 0;
    }
    else if (*dialog_flag == 1 && *quit_flag == 1)
        printf("\nEnd result is %f\n", akkumulatoren);
}

/*scanner der afgører om brugerens indtastning er en binær eller unær operator, ud fra dette scanner et tal efterfølgende*/
char Scan_data (double *new_number){
    char sign;
    scanf(" %c", &sign);
    if (sign == '+' || sign == '-' || sign == '*' || sign == '/'||sign == '^')
        scanf(" %lf", new_number);
    else
        *new_number = 0;
    return sign;
}

/*kigger på operanten og udfører en funktion på akkumulatoren derefter*/
void Do_next_op (char sign, double new_number, double *akkumulator, int *flag){
    switch(sign){
        case'+': /*ligger new_number til akkumulatoren*/
            *akkumulator += new_number;
            break;
        case'-': /*trækker new_number fra akkumulatoren*/
            *akkumulator -= new_number;
            break;
        case'*': /*ganger akkumulatoren med new_number*/
            *akkumulator *= new_number;
            break;
        case'/': /*dividerer akkumulatoren med new_number*/
            if (new_number != 0)
                *akkumulator /= new_number;   
            break;
        case'^':/*akkumulatoren^(new_number)*/
            *akkumulator = pow(*akkumulator, new_number);
            break;
        case'#': /*kvadrart rod*/
            if(*akkumulator > 0)
                *akkumulator = sqrt(*akkumulator);
            break;
        case'%': /*vender fortegnet for akkumulatoren*/
            *akkumulator *= -1;
            break;
        case'!': /*dividerer 1 med akkumulatoren*/
            if (*akkumulator != 0)
                *akkumulator = 1 / *akkumulator;
            break;
        case'q': /*quit*/
            *flag = 1;
            break;
    }
}