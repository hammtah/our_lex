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

void state_id_0();
void state_id_1();
void state_oprel_0();
void state_oprel_1();
void state_oprel_2();
void state_oprel_3();
void state_oprel_4();
// void state_nb_0();
// void state_nb_1();
// void state_nb_2();
// void state_nb_3();
// void state_nb_4();
// void state_nb_5();
// void state_nb_6();

char word[100];
void clear_buffer() {
    for (int i = 0; i < 100; word[i++] = '\0');
}
void insert_buffer(char c) {
    int i = 0;
    while (word[i++] != '\0');
    word[i-1] = c;
}
void unget_word() {
    int i = 0;
    while (word[i++] != '\0');
    fseek(input, -(i-1), SEEK_CUR);
    clear_buffer();
}
char getfchar(FILE *f) {
    char c;
    while (isspace(c=fgetc(f)));
    return c;
}
/*************id****************/
// id: letter (letter|number)*
void state_id_0() {
    char c = getfchar(input);//We get the first character without spaces before it
    insert_buffer(c);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        state_id_1();
    } else {
        not_mine_error();
    }
}
void state_id_1() {
    // char c = getfchar(input);
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        state_id_1();
    } else {
        ungetc(c, input);//j'ai vu le caracter suivant qui n'appartient pas à l'automate donc je doit le rendre au buffer
        word[strlen(word)-1] = '\0';
        success(1);
    }
}


/************OPREL (< | <= | = | <> | > | >=) DFAM*************/
void state_oprel_0() {
    char c = getfchar(input);
    insert_buffer(c);
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
    // char c = getfchar(input);
    char c = fgetc(input);
    insert_buffer(c);
    switch (c) {
        case '=': // '<='
        case '>': // '<>'
            state_oprel_4();
            break;
        default:
            ungetc(c, input);
            success(0);
    }
}
// After reading '>': accept '>' alone, or consume '=' for '>='
void state_oprel_2() {
    // char c = getfchar(input);
    char c = fgetc(input);
    insert_buffer(c);
    switch (c) {
        case '=': // '>='
            state_oprel_4();
            break;
        default:
            ungetc(c, input);
            success(0);
    }
}
// '=' is a complete operator by itself
void state_oprel_3() {
        success(0);
}
// Final acceptor for two-character operators: '<=', '<>', '>='
void state_oprel_4() {
        success(0);
}

/************NB (chiffre+(.chiffre+)?(E(+|-)?chiffre+)?) DFAM*************/
// void state_nb_0() {
//     temp = strdup(word);
//     char c = getstrchar(&temp);
//     if (c >= '0' && c <= '9') {
//         state_nb_1();
//     } else {
//         not_mine_error();
//     }
// }
// // Integer part acceptor: digits+, optional '.' or 'E', or end
// void state_nb_1() {
//     char c = getstrchar(&temp);
//     if (c >= '0' && c <= '9') {
//         state_nb_1();
//     } else if (c == '.') {
//         state_nb_2();
//     } else if (c == 'E') {
//         state_nb_3();
//     } else if (c == '\0') {
//         success(5);
//     } else {
//         not_mine_error();
//     }
// }
// // After '.', require at least one digit
// void state_nb_2() {
//     char c = getstrchar(&temp);
//     if (c >= '0' && c <= '9') {
//         state_nb_4();
//     } else {
//         not_mine_error();
//     }
// }
// // Fractional part acceptor: digits+, optional 'E', or end
// void state_nb_4() {
//     char c = getstrchar(&temp);
//     if (c >= '0' && c <= '9') {
//         state_nb_4();
//     } else if (c == 'E') {
//         state_nb_3();
//     } else if (c == '\0') {
//         success(5);
//     } else {
//         not_mine_error();
//     }
// }
// // After 'E': optional sign or require at least one digit
// void state_nb_3() {
//     char c = getstrchar(&temp);
//     if (c == '+' || c == '-') {
//         // require at least one digit next
//         state_nb_6();
//     } else if (c >= '0' && c <= '9') {
//         state_nb_5();
//     } else {
//         not_mine_error();
//     }
// }
// // After sign: require first exponent digit
// void state_nb_6() {
//     char c = getstrchar(&temp);
//     if (c >= '0' && c <= '9') {
//         state_nb_5();
//     } else {
//         not_mine_error();
//     }
// }
// // Exponent digits acceptor: digits+, then end
// void state_nb_5() {
//     char c = getstrchar(&temp);
//     if (c >= '0' && c <= '9') {
//         state_nb_5();
//     } else if (c == '\0') {
//         success(5);
//     } else {
//         not_mine_error();
//     }
// }
//
#endif //OUR_LEX_STATES_H