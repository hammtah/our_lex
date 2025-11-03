/*
 * State machine implementations for the lexical analyzer.
 * Groups of functions below implement DFAs for keywords, identifiers,
 * relational operators, and numeric literals. Includes small helper
 * routines for buffering and input handling used by the DFAs.
 *
 * Created by taha on 10/31/25.
 */
#ifndef OUR_LEX_STATES_H
#define OUR_LEX_STATES_H
#include <iso646.h>

#include "utility.h"

/* External control and reporting hooks implemented in the driver. */
void analyser();
void lexical_error();
void not_mine_error();
void success(int nb_automate);

/* Prototypes for state functions (DFAs). */
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
// void state_oprel_3();
// void state_oprel_4();

void state_nb_0();
void state_nb_1();
void state_nb_2();
void state_nb_3();
void state_nb_4();
void state_nb_5();
void state_nb_6();

/* Shared lexeme buffer used by the DFAs to accumulate characters. */
char word[100];
/* Shared error_word buffer used to print the word when we have lexical error. */
char error_word[100];

/* Reset the lexeme buffer to an empty string. */
void clear_buffer() {
    for (int i = 0; i < 100; word[i++] = '\0');
}
/* Reset the error word buffer to an empty string. */
void clear_error_word() {
    for (int i = 0; i < 100; error_word[i++] = '\0');
}

/* Append a character to the end of the lexeme buffer. */
void insert_buffer(char c) {
    int i = 0;
    while (word[i++] != '\0');
    word[i - 1] = c;
}

/*
 * Push the currently accumulated word back into the input stream
 * (so other DFAs can try to recognize it) and clear the buffer.
 */
void unget_word() {
    int i = 0;
    while (word[i++] != '\0');
    fseek(input, -(i - 1), SEEK_CUR);
    clear_buffer();
}

/*
 * Read the next non-whitespace character from the given stream.
 * Returns EOF if end-of-file is reached.
 */
char getfchar(FILE *f) {
    char c;
    while (isspace(c = fgetc(f))) {
        if (c == '\n')
            line_num++;
    }
    return c;
}

/* ======================== DFA: SI (keyword) ======================== */
void state_si_0() {
    /* Read the first non-space character of the lexeme. */
    char c = getfchar(input);
    insert_buffer(c);
    if (c == 's' || c == 'S') {
        state_si_1();
    } else {
        not_mine_error();
    }
}

void state_si_1() {
    /* Read the next character (may be whitespace if previously consumed). */
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 'i' || c == 'I') {
        state_si_2();
    } else {
        not_mine_error();
    }
}

void state_si_2() {
    /* Look ahead to ensure the keyword is not followed by an alphanumeric. */
    char c = fgetc(input);
    insert_buffer(c);
    if (!isalnum(c)) {
        /* Character does not belong to this DFA: push back and accept 'si'. */
        ungetc(c, input);
        word[strlen(word) - 1] = '\0';
        success(SI);
    } else {
        not_mine_error();
    }
}

/* ====================== DFA: SINON (keyword) ======================= */
void state_sinon_0() {
    char c = getfchar(input);
    insert_buffer(c);
    if (c == 's' || c == 'S') {
        state_sinon_1();
    } else {
        not_mine_error();
    }
}

void state_sinon_1() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 'i' || c == 'I') {
        state_sinon_2();
    } else {
        not_mine_error();
    }
}

void state_sinon_2() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 'n' || c == 'N') {
        state_sinon_3();
    } else {
        not_mine_error();
    }
}

void state_sinon_3() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 'o' || c == 'O') {
        state_sinon_4();
    } else {
        not_mine_error();
    }
}

void state_sinon_4() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 'n' || c == 'N') {
        state_sinon_5();
    } else {
        not_mine_error();
    }
}

void state_sinon_5() {
    /* Look ahead to ensure the keyword is not followed by an alphanumeric. */
    char c = fgetc(input);
    insert_buffer(c);
    if (!isalnum(c)) {
        /* Character does not belong to this DFA: push back and accept 'sinon'. */
        ungetc(c, input);
        word[strlen(word) - 1] = '\0';
        success(SINON);
    } else {
        not_mine_error();
    }
}

/* ====================== DFA: ALORS (keyword) ======================= */
void state_alors_0() {
    char c = getfchar(input);
    insert_buffer(c);
    if (c == 'a' || c == 'A') {
        state_alors_1();
    } else {
        not_mine_error();
    }
}

void state_alors_1() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 'l' || c == 'L') {
        state_alors_2();
    } else {
        not_mine_error();
    }
}

void state_alors_2() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 'o' || c == 'O') {
        state_alors_3();
    } else {
        not_mine_error();
    }
}

void state_alors_3() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 'r' || c == 'R') {
        state_alors_4();
    } else {
        not_mine_error();
    }
}

void state_alors_4() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == 's' || c == 'S') {
        state_alors_5();
    } else {
        not_mine_error();
    }
}

void state_alors_5() {
    /* Look ahead to ensure the keyword is not followed by an alphanumeric. */
    char c = fgetc(input);
    insert_buffer(c);
    if (!isalnum(c)) {
        /* Character does not belong to this DFA: push back and accept 'alors'. */
        ungetc(c, input);
        word[strlen(word) - 1] = '\0';
        success(ALORS);
    } else {
        not_mine_error();
    }
}

/* =================== DFA: Identifier (ID) =========================
 * Grammar: letter (letter | digit)*
 */
void state_id_0() {
    char c = getfchar(input); /* First non-space character of a potential identifier. */
    insert_buffer(c);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        state_id_1();
    } else {
        not_mine_error();
    }
}

void state_id_1() {
    /* Continue consuming letters and digits; stop on first non-[A-Za-z0-9]. */
    char c = fgetc(input);
    insert_buffer(c);
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        state_id_1();
    } else {
        /* Non-identifier character encountered: push back and accept ID. */
        ungetc(c, input);
        word[strlen(word) - 1] = '\0';
        success(ID);
    }
}

/* ========= DFA: Relational operator (< | <= | = | <> | > | >=) ======== */
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
            // state_oprel_3();
            success(OPREL);
            break;
        default:
            not_mine_error();
    }
}

/* After reading '<': accept '<' alone, or consume '='/'>' for '<=' / '<>' */
void state_oprel_1() {
    char c = fgetc(input);
    insert_buffer(c);
    switch (c) {
        case '=': /* '<=' */
        case '>': /* '<>' */
            // state_oprel_4();
            success(OPREL);
            break;
        default:
            /* Next character does not belong: push back and accept '<'. */
            ungetc(c, input);
            success(OPREL);
    }
}

/* After reading '>': accept '>' alone, or consume '=' for '>=' */
void state_oprel_2() {
    char c = fgetc(input);
    insert_buffer(c);
    switch (c) {
        case '=': /* '>=' */
            // state_oprel_4();
            success(OPREL);
            break;
        default:
            /* Next character does not belong: push back and accept '>'. */
            ungetc(c, input);
            success(OPREL);
    }
}

/* '=' is a complete operator by itself */
// void state_oprel_3() {
//     success(OPREL);
// }

/* Final acceptor for two-character operators: '<=', '<>', '>=' */
// void state_oprel_4() {
//     success(OPREL);
// }

/* ========== DFA: Number (digits+(.digits+)?(E(+|-)?digits+)?) ==========
 * Recognizes integers, decimals, and scientific notation. Uses a best-match
 * buffer to backtrack cleanly when a partial numeric literal is valid.
 */
char best_match[100];

/* Keep the longest valid numeric prefix seen so far (excluding the latest lookahead). */
void insert_best_match() {
    if ((strlen(word) - 1) > strlen(best_match)) {
        strncpy(best_match, word, strlen(word) - 1);
    }
}

void state_nb_0() {
    /* Initialize best_match for this token attempt. */
    for (int i = 0; i < 100; best_match[i++] = '\0');
    char c = getfchar(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_1();
    } else {
        not_mine_error();
    }
}

/* Integer part acceptor: digits+, optional '.' or 'E', or end */
void state_nb_1() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        /* Store the longest valid numeric prefix so far. */
        insert_best_match();
        state_nb_1();
    } else if (c == '.') {
        insert_best_match();
        state_nb_2();
    } else if (c == 'E') {
        insert_best_match();
        state_nb_3();
    } else {
        /* No further numeric content: push back and accept integer. */
        ungetc(c, input);
        success(NB);
    }
}

/* After '.', require at least one digit */
void state_nb_2() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_4();
    } else {
        if (strlen(best_match) > 0) {
            /* Backtrack to the last recognized number and accept it. */
            fseek(input, -(strlen(word) - strlen(best_match)), SEEK_CUR);
            success(NB);
        } else {
            not_mine_error();
        }
    }
}

/* Fractional part acceptor: digits+, optional 'E', or end */
void state_nb_4() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_4();
    } else if (c == 'E') {
        state_nb_3();
    } else {
        /* No more fractional content: push back and accept decimal. */
        ungetc(c, input);
        success(NB);
    }
}

/* After 'E': optional sign or require at least one digit */
void state_nb_3() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c == '+' || c == '-') {
        /* Require at least one digit after the sign. */
        state_nb_6();
    } else if (c >= '0' && c <= '9') {
        state_nb_5();
    } else {
        if (strlen(best_match) > 0) {
            /* Backtrack to the last recognized number and accept it. */
            fseek(input, -(strlen(word) - strlen(best_match)), SEEK_CUR);
            success(NB);
        } else {
            not_mine_error();
        }
    }
}

/* After sign: require first exponent digit */
void state_nb_6() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_5();
    } else {
        if (strlen(best_match) > 0) {
            /* Backtrack to the last recognized number and accept it. */
            fseek(input, -(strlen(word) - strlen(best_match)), SEEK_CUR);
            success(NB);
        } else {
            not_mine_error();
        }
    }
}

/* Exponent digits acceptor: digits+, then end */
void state_nb_5() {
    char c = fgetc(input);
    insert_buffer(c);
    if (c >= '0' && c <= '9') {
        state_nb_5();
    } else {
        /* No more exponent digits: push back and accept scientific literal. */
        ungetc(c, input);
        success(NB);
    }
}

#endif // OUR_LEX_STATES_H