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
void state_sinon_0();
void state_sinon_1();
void state_sinon_2();
void state_sinon_3();
void state_sinon_4();
void state_sinon_5();
void state_oprel_0();
void state_oprel_1();
void state_oprel_2();
void state_oprel_3();
void state_oprel_4();
void state_nb_0();
void state_nb_1();
void state_nb_2();
void state_nb_3();
void state_nb_4();
void state_nb_5();
void state_nb_6();
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

/************SINON*************/
void state_sinon_0() {
    temp = strdup(word);
    char c = getstrchar(&temp);
    switch (c) {
        case 's': case 'S':
            state_sinon_1();
            break;
        default:
            not_mine_error();
    }
}
void state_sinon_1() {
    char c = getstrchar(&temp);
    switch (c) {
        case 'i': case 'I':
            state_sinon_2();
            break;
        default:
            not_mine_error();
    }
}
void state_sinon_2() {
    char c = getstrchar(&temp);
    switch (c) {
        case 'n': case 'N':
            state_sinon_3();
            break;
        default:
            not_mine_error();
    }
}
void state_sinon_3() {
    char c = getstrchar(&temp);
    switch (c) {
        case 'o': case 'O':
            state_sinon_4();
            break;
        default:
            not_mine_error();
    }
}
void state_sinon_4() {
    char c = getstrchar(&temp);
    switch (c) {
        case 'n': case 'N':
            state_sinon_5();
            break;
        default:
            not_mine_error();
    }
}
// Final state for 'sinon'
void state_sinon_5() {
    if (getstrchar(&temp) == '\0')
        success(2);
    else
        not_mine_error();
}

/************OPREL (< | <= | = | <> | > | >=) DFAM*************/
void state_oprel_0() {
    temp = strdup(word);
    char c = getstrchar(&temp);
    switch (c) {
        case '<':
            state_oprel_1();
            break;
        case '>':
            state_oprel_2();
            break;
        case '=':
            state_oprel_3();
            break;
        default:
            not_mine_error();
    }
}
// After reading '<': accept '<' alone, or consume '='/'>' for '<=' / '<>'
void state_oprel_1() {
    char c = getstrchar(&temp);
    switch (c) {
        case '=': // '<='
        case '>': // '<>'
            state_oprel_4();
            break;
        case '\0': // '<'
            success(3);
            break;
        default:
            not_mine_error();
    }
}
// After reading '>': accept '>' alone, or consume '=' for '>='
void state_oprel_2() {
    char c = getstrchar(&temp);
    switch (c) {
        case '=': // '>='
            state_oprel_4();
            break;
        case '\0': // '>'
            success(3);
            break;
        default:
            not_mine_error();
    }
}
// '=' is a complete operator by itself
void state_oprel_3() {
    if (getstrchar(&temp) == '\0')
        success(3);
    else
        not_mine_error();
}
// Final acceptor for two-character operators: '<=', '<>', '>='
void state_oprel_4() {
    if (getstrchar(&temp) == '\0')
        success(3);
    else
        not_mine_error();
}

/************NB (chiffre+(.chiffre+)?(E(+|-)?chiffre+)?) DFAM*************/
void state_nb_0() {
    temp = strdup(word);
    char c = getstrchar(&temp);
    if (c >= '0' && c <= '9') {
        state_nb_1();
    } else {
        not_mine_error();
    }
}
// Integer part acceptor: digits+, optional '.' or 'E', or end
void state_nb_1() {
    char c = getstrchar(&temp);
    if (c >= '0' && c <= '9') {
        state_nb_1();
    } else if (c == '.') {
        state_nb_2();
    } else if (c == 'E') {
        state_nb_3();
    } else if (c == '\0') {
        success(5);
    } else {
        not_mine_error();
    }
}
// After '.', require at least one digit
void state_nb_2() {
    char c = getstrchar(&temp);
    if (c >= '0' && c <= '9') {
        state_nb_4();
    } else {
        not_mine_error();
    }
}
// Fractional part acceptor: digits+, optional 'E', or end
void state_nb_4() {
    char c = getstrchar(&temp);
    if (c >= '0' && c <= '9') {
        state_nb_4();
    } else if (c == 'E') {
        state_nb_3();
    } else if (c == '\0') {
        success(5);
    } else {
        not_mine_error();
    }
}
// After 'E': optional sign or require at least one digit
void state_nb_3() {
    char c = getstrchar(&temp);
    if (c == '+' || c == '-') {
        // require at least one digit next
        state_nb_6();
    } else if (c >= '0' && c <= '9') {
        state_nb_5();
    } else {
        not_mine_error();
    }
}
// After sign: require first exponent digit
void state_nb_6() {
    char c = getstrchar(&temp);
    if (c >= '0' && c <= '9') {
        state_nb_5();
    } else {
        not_mine_error();
    }
}
// Exponent digits acceptor: digits+, then end
void state_nb_5() {
    char c = getstrchar(&temp);
    if (c >= '0' && c <= '9') {
        state_nb_5();
    } else if (c == '\0') {
        success(5);
    } else {
        not_mine_error();
    }
}

#endif //OUR_LEX_STATES_H