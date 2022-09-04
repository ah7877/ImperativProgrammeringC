#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define decksize 55

/*
Navn: Andreas Hougaard
Email: houga20@student.aau.dk
Gruppe: A310a
Studieretning: Datalogi
*/

struct Card {
   int  suit;
   int  value;
};

void deck_maker (struct Card *deck);
void shuffle (struct Card *deck);
int sorting_algorythm (const void *a, const void *b);
void print_deck (struct Card *deck);
char *suit_mapping (int suit);
char *value_mapping (int value);

enum suit {joker, clubs, diamonds, hearts, spades};
enum value {two = 2, three, four, five, six, seven, eight, nine, ten, knight, queen, king, es};

int main(void) {
    struct Card deck[decksize];
    srand(time(0));

    deck_maker(deck);
    shuffle(deck);
    print_deck(deck);
    printf("\n\n\n");
    qsort(deck, decksize, sizeof(struct Card), sorting_algorythm);
    print_deck(deck);
    return 0;
}

void deck_maker (struct Card *deck){
    int a = 0;
    for(int b = clubs; b <= spades; b++){
        for(int c = two; c <= es; c++){
            deck[a].suit = b;
            deck[a].value = c;
            a++;
        }
    }
    for(int b = a; b < decksize; b++){
        deck[b].suit = joker;
        deck[b].value = 15;
    }
}

void shuffle (struct Card *deck){
    struct Card placeholder;
    int random_number;
    for (int a = 0; a < decksize; a++){
        random_number = rand() % decksize;
        placeholder = deck[a];
        deck[a] = deck[random_number];
        deck[random_number] = placeholder;
    }
}

int sorting_algorythm (const void *a, const void *b){
    struct Card *card_1 = (struct Card*) a;
    struct Card *card_2 = (struct Card*) b;
    if(card_1->suit == card_2->suit && card_1->suit == 0)
        return 0;
    if(card_1->suit == 0)
        return 1;
    if(card_2->suit == 0)
        return -1;
    
    if(card_1->suit < card_2->suit)
        return -1;
    if(card_1->suit > card_2->suit)
        return 1;
    
    if(card_1->value < card_2->value)
        return -1;
    if(card_1->value > card_2->value)
        return 1;
    return 0;
}

void print_deck (struct Card *deck){
    for (int a = 0; a < decksize; a++){
    if(deck[a].value < 11)
        printf("\n%s\t%d", suit_mapping(deck[a].suit), deck[a].value);
    else
        printf("\n%s\t%s", suit_mapping(deck[a].suit), value_mapping(deck[a].value));
    }
    return;
}

char *suit_mapping (int suit){
    switch (suit){
    case joker:
        return "Joker";
        break;
    case spades:
        return "Spar";
        break;
    case clubs:
        return "Klør";
        break;
    case diamonds:
        return "Ruder";
        break;
    case hearts:
        return "Hjerter";
        break;
    default:
        return "Fejl i suitmapping";
        break;
    }
}

char *value_mapping (int value){
    if (value < 11){
        printf("%d", value);
        return "";
    }
    switch (value){
    case knight:
        return "knægt";
        break;
    case queen:
        return "dronning";
        break;
    case king:
        return "konge";
        break;
    case es:
        return "es";
        break;
    case 15:
        return "";
    default:
        return "fejl i value mapping";
        break;
    }
}