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
void state_id_0();
void state_id_1();
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
    // char c = d;
    insert_buffer(c);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        state_id_1();
    } else {
        // ungetc(c, input);
        not_mine_error();
        // lexical_error();
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
        success(ID);
    }
}


/************OPREL (< | <= | = | <> | > | >=) DFAM*************/
void state_oprel_0() {
    char c = getfchar(input);
    // char c = d;
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
            // lexical_error();
            // ungetc(c, input);

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
            success(OPREL);
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
            success(OPREL);
    }
}
// '=' is a complete operator by itself
void state_oprel_3() {
        success(OPREL);
}
// Final acceptor for two-character operators: '<=', '<>', '>='
void state_oprel_4() {
        success(OPREL);
}

/************NB (chiffre+(.chiffre+)?(E(+|-)?chiffre+)?) DFAM*************/
// void state_nb_0() {
//     // char c = getfchar(input);
//     char c = d;
//     insert_buffer(c);
//     if (c >= '0' && c <= '9') {
//         state_nb_1();
//     } else {
//         // not_mine_error();
//         ungetc(c, input);
//         lexical_error();
//
//     }
// }
// // // Integer part acceptor: digits+, optional '.' or 'E', or end
// void state_nb_1() {
//     char c = fgetc(input);
//     insert_buffer(c);
//     if (c >= '0' && c <= '9') {
//         state_nb_1();
//     } else if (c == '.') {
//         state_nb_2();
//     } else if (c == 'E') {
//         state_nb_3();
//     } else {
//         ungetc(c, input);
//         success(2);
//     }
// }
// // // After '.', require at least one digit
// void state_nb_2() {
//     char c = fgetc(input);
//     insert_buffer(c);
//     if (c >= '0' && c <= '9') {
//         state_nb_4();
//     } else {
//         // not_mine_error();
//         ungetc(c, input);
//         lexical_error();
//     }
// }
// // // Fractional part acceptor: digits+, optional 'E', or end
// void state_nb_4() {
//     char c = fgetc(input);
//     insert_buffer(c);
//     if (c >= '0' && c <= '9') {
//         state_nb_4();
//     } else if (c == 'E') {
//         state_nb_3();
//     }else {
//         ungetc(c, input);
//        success(2);
//     }
// }
// // After 'E': optional sign or require at least one digit
// void state_nb_3() {
//     char c = fgetc(input);
//     insert_buffer(c);
//     if (c == '+' || c == '-') {
//         // require at least one digit next
//         state_nb_6();
//     } else if (c >= '0' && c <= '9') {
//         state_nb_5();
//     } else {
//         // not_mine_error();
//         ungetc(c, input);
//         lexical_error();
//
//     }
// }
// // // After sign: require first exponent digit
// void state_nb_6() {
//     char c = fgetc(input);
//     insert_buffer(c);
//     if (c >= '0' && c <= '9') {
//         state_nb_5();
//     } else {
//         // not_mine_error();
//         ungetc(c, input);
//         lexical_error();
//     }
// }
// // Exponent digits acceptor: digits+, then end
// void state_nb_5() {
//     char c = fgetc(input);
//     insert_buffer(c);
//     if (c >= '0' && c <= '9') {
//         state_nb_5();
//     }
//     else {
//         ungetc(c, input);
//         success(2);
//     }
//     // else if (c == '\0') {
//     //     success(5);
//     // } else {
//     //     // not_mine_error();
//     // }
// }
//
#endif //OUR_LEX_STATES_H