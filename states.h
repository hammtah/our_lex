//
// Created by taha on 10/31/25.
//
#ifndef OUR_LEX_STATES_H
#define OUR_LEX_STATES_H
#include "utility.h"
void analyser() ;
void lexical_error() ;
void not_mine_error() ;
void success(int nb_automate) ;

void state_si_0();
void state_si_1();
void state_si_2();
/************SI*************/
void state_si_0() {
    temp = strdup(word);
    char c = getstrchar(&temp);
    switch (c) {
        case 's':case 'S':
            state_si_1();
            break;
        default:
            not_mine_error();
    }
}
void state_si_1() {
    char c = getstrchar(&temp);
    switch (c) {
        case 'i':case 'I':
            state_si_2();
            break;
        default:
            not_mine_error();
    }
}
//Final state for 'si'
void state_si_2() {
    if (getstrchar(&temp) == '\0')
        success(0);
    else
        not_mine_error();
}

/*************alors****************/

#endif //OUR_LEX_STATES_H