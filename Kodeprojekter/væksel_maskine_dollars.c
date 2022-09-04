#include <stdio.h>

int Calculator (int *a, int constant);

int main(void) {
    const int hundred_bill = 100;
    const int fifty_bill = 50;
    const int twenty_bill = 20;
    const int ten_bill = 10;

    int dollars = 9, hundred, fifty, twenty, ten;

    do
    {
        printf("Skriv et antal dollars du gerne vil have penge tilbage, i sedler: ");
        scanf("%d", &dollars);
    }
    while (dollars % 10 != 0);

    printf("dollars = %d", dollars);

    hundred = Calculator(&dollars, hundred_bill);
    fifty = Calculator(&dollars, fifty_bill);
    twenty = Calculator(&dollars, twenty_bill);
    ten = Calculator(&dollars, ten_bill);

    printf("\nDu får \n%d 100$\n%d 50$\n%d 20$\n%d 10$.\n", 
    hundred, fifty, twenty, ten);
    return 0;
}

int Calculator (int *a, int constant){
    int b = *a/constant;
    printf("her %d", b);
    *a = *a % constant;
    return b;
}