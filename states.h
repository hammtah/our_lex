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
void state_id_0();
void state_id_1();
void state_alors_0();
void state_alors_1();
void state_alors_2();
void state_alors_3();
void state_alors_4();
void state_alors_5();
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

/*************id****************/
// id: letter (letter|number)*
void state_id_0() {
    temp = strdup(word);
    char c = getstrchar(&temp);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        state_id_1();
    } else {
        not_mine_error();
    }
}
void state_id_1() {
    char c = getstrchar(&temp);
    if (c == '\0') {
        success(4);
    } else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        state_id_1();
    } else {
        not_mine_error();
    }
}

/************ALORS*************/
void state_alors_0() {
    temp = strdup(word);
    char c = getstrchar(&temp);
    switch (c) {
        case 'a': case 'A':
            state_alors_1();
            break;
        default:
            not_mine_error();
    }
}
void state_alors_1() {
    char c = getstrchar(&temp);
    switch (c) {
        case 'l': case 'L':
            state_alors_2();
            break;
        default:
            not_mine_error();
    }
}
void state_alors_2() {
    char c = getstrchar(&temp);
    switch (c) {
        case 'o': case 'O':
            state_alors_3();
            break;
        default:
            not_mine_error();
    }
}
void state_alors_3() {
    char c = getstrchar(&temp);
    switch (c) {
        case 'r': case 'R':
            state_alors_4();
            break;
        default:
            not_mine_error();
    }
}
void state_alors_4() {
    char c = getstrchar(&temp);
    switch (c) {
        case 's': case 'S':
            state_alors_5();
            break;
        default:
            not_mine_error();
    }
}
// Final state for 'alors'
void state_alors_5() {
    if (getstrchar(&temp) == '\0')
        success(1);
    else
        not_mine_error();
}

#endif //OUR_LEX_STATES_H