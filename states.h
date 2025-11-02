//
// Created by taha on 10/31/25.
//
#ifndef OUR_LEX_STATES_H
#define OUR_LEX_STATES_H
#include <iso646.h>

#include "utility.h"
void analyser() ;
void lexical_error() ;
void not_mine_error() ;
void success(int nb_automate) ;
void state_si_0();
void state_si_1();
void state_si_2();

void state_sinon_0();
void state_sinon_1();
void state_sinon_2();
void state_sinon_3();
void state_sinon_4();
void state_sinon_5();

void state_alors_0();
void state_alors_1();
void state_alors_2();
void state_alors_3();
void state_alors_4();
void state_alors_5();

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

/***************SI***************/
void state_si_0() {
    char c = getfchar(input);//We get the first character without spaces before it
    insert_buffer(c);
    if (c=='s'||c=='S') {
        state_si_1();
    }else {
        not_mine_error();
    }
}
void state_si_1() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='i'||c=='I') {
        state_si_2();
    }else {
        not_mine_error();
    }
}
void state_si_2() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (!isalnum(c)) {
        ungetc(c, input);//j'ai vu le caracter suivant qui n'appartient pas à l'automate donc je doit le rendre au buffer
        word[strlen(word)-1] = '\0';
        success(SI);
    }else {
        not_mine_error();
    }
}
    /***************SINON*******************/
void state_sinon_0() {
    char c = getfchar(input);//We get the first character without spaces before it
    insert_buffer(c);
    if (c=='s'||c=='S') {
        state_sinon_1();
    }else {
        not_mine_error();
    }
}
void state_sinon_1() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='i'||c=='I') {
        state_sinon_2();
    }else {
        not_mine_error();
    }
}
void state_sinon_2() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='n'||c=='N') {
        state_sinon_3();
    }else {
        not_mine_error();
    }
}
void state_sinon_3() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='o'||c=='O') {
        state_sinon_4();
    }else {
        not_mine_error();
    }
}
void state_sinon_4() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='n'||c=='N') {
        state_sinon_5();
    }else {
        not_mine_error();
    }
}

void state_sinon_5() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (!isalnum(c)) {
        ungetc(c, input);//j'ai vu le caracter suivant qui n'appartient pas à l'automate donc je doit le rendre au buffer
        word[strlen(word)-1] = '\0';
        success(SINON);
    }else {
        not_mine_error();
    }
}
/***************ALORS*******************/
void state_alors_0() {
    char c = getfchar(input);//We get the first character without spaces before it
    insert_buffer(c);
    if (c=='a'||c=='A') {
        state_alors_1();
    }else {
        not_mine_error();
    }
}
void state_alors_1() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='l'||c=='L') {
        state_alors_2();
    }else {
        not_mine_error();
    }
}
void state_alors_2() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='o'||c=='O') {
        state_alors_3();
    }else {
        not_mine_error();
    }
}
void state_alors_3() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='r'||c=='R') {
        state_alors_4();
    }else {
        not_mine_error();
    }
}
void state_alors_4() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (c=='s'||c=='S') {
        state_alors_5();
    }else {
        not_mine_error();
    }
}

void state_alors_5() {
    char c = fgetc(input);//We get the second character even if it's a space
    insert_buffer(c);
    if (!isalnum(c)) {
        ungetc(c, input);//j'ai vu le caracter suivant qui n'appartient pas à l'automate donc je doit le rendre au buffer
        word[strlen(word)-1] = '\0';
        success(ALORS);
    }else {
        not_mine_error();
    }
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
            success(OPREL);
    }
}
// After reading '>': accept '>' alone, or consume '=' for '>='
void state_oprel_2() {
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
char best_match[100];
void insert_best_match() {
    if ((strlen(word)-1) > strlen(best_match)) {
        strncpy(best_match, word, strlen(word)-1);
    }
}
void state_nb_0() {
    for (int i = 0; i < 100; best_match[i++] = '\0');//initialise the best match string
    char c = getfchar(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_1();
    } else {
        not_mine_error();

    }
}
// // Integer part acceptor: digits+, optional '.' or 'E', or end
void state_nb_1() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        insert_best_match();   //store the shortest word that matches the nb automata(!don't forget that the buffer(word) contains also the next caractere so we should ungetit)
        state_nb_1();
    } else if (c == '.') {
        insert_best_match();
        state_nb_2();
    } else if (c == 'E') {
        insert_best_match();
        state_nb_3();
    } else {
        ungetc(c, input);
        // insert_best_match();
        success(NB);
    }
}
// // After '.', require at least one digit
void state_nb_2() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_4();
    } else {
        if (strlen(best_match)>0) {
            //Return the pointer to the last recognised number
            fseek(input, -(strlen(word)-strlen(best_match)), SEEK_CUR);
            success(NB);
        }
        else
            not_mine_error();
    }
}
// // Fractional part acceptor: digits+, optional 'E', or end
void state_nb_4() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_4();
    } else if (c == 'E') {
        state_nb_3();
    }else {
        ungetc(c, input);
       success(NB);
    }
}
// After 'E': optional sign or require at least one digit
void state_nb_3() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == '+' || c == '-') {
        // require at least one digit next
        state_nb_6();
    } else if (c >= '0' && c <= '9') {
        state_nb_5();
    } else {
        if (strlen(best_match)>0) {
            //Return the pointer to the last recognised number
            fseek(input, -(strlen(word)-strlen(best_match)), SEEK_CUR);
            success(NB);
        }
        else
            not_mine_error();

    }
}
// // After sign: require first exponent digit
void state_nb_6() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_5();
    } else {
        if (strlen(best_match)>0) {
            //Return the pointer to the last recognised number
            fseek(input, -(strlen(word)-strlen(best_match)), SEEK_CUR);
            success(NB);
        }
        else
            not_mine_error();
    }
}
// Exponent digits acceptor: digits+, then end
void state_nb_5() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_5();
    }
    else {
        ungetc(c, input);
        success(NB);
    }
}
//
#endif //OUR_LEX_STATES_H