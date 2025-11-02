//
// Created by taha on 10/31/25.
//
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "states.h"
#include "utility.h"

void analyser() ;
void lexical_error() ;
void not_mine_error() ;
void success(int nb_automate) ;
void check_reserved() {
    if (!strcmp(word, "si")) {
        write_to_file("SI\t");
        printf("\tSI");
    }else if (!strcmp(word, "sinon")) {
        write_to_file("SINON\t");
        printf("\tSINON");
    }else if (!strcmp(word, "alors")) {
        write_to_file("ALORS\t");
        printf("\tALORS");
    }else {
        write_to_file("id\t");
        printf("\tID");
    }
}
void success(int nb_automate) {
    switch (nb_automate) {
        case 0:
            write_to_file("oprel\t");
            printf("\tOPREL");
            start = 0;
            break;
        case 1:
            check_reserved();
            start = 0;
            break;
        case 2:
            write_to_file("nb\t");
            printf("\tNB");
            start = 0;
            break;
        case 3:
            write_to_file("si\t");
            printf("\tSI");
            start = 0;
            break;
        case 4:
            write_to_file("alors\t");
            printf("\tALORS");
            start = 0;
            break;
        case 5:
            write_to_file("sinon\t");
            printf("\tSINON");
            start = 0;
            break;
        default:
    }
    clear_buffer();
}
void lexical_error() {
    printf("\nLexical error!\n");
    // start = 0;
    clear_buffer();
    // fgetc(input);//consume the character that has not been recognized so that we can move to the next one(the reality, we should consume the shortest not recognised word by the automatas)
    //move the file input ptr to the next string

    // if (read_word_from_file())
    //     analyser();
}
void not_mine_error() {
    unget_word();//unget the word that have been read by the automata to be analysed by another automata
    start++;
    analyser();
}
void analyser() {
        // ungetc(d, input);//Should be removed and we should not enter to state0 because we already read the first character so we should go to state1 or 2 ..
        if ((d=='<')||(d=='>')||(d=='='))
            state_oprel_0();
        else if ((d >= 'A' && d <= 'Z') || (d >= 'a' && d <= 'z'))
            state_id_0();
        else if (d >= '0' && d <= '9')
            state_nb_0();
        else lexical_error();
}
// void analyser() {
//     switch (start) {
//         // case 0:
//         //     state_si_0();
//         //     break;
//         // case 1:
//         //     state_alors_0();
//         //     break;
//         // case 2:
//         //     state_sinon_0();
//         //     break;
//         case 0:
//             state_oprel_0();
//             break;
//         case 1:
//             state_id_0();
//             break;
//         case 2:
//             state_nb_0();
//             break;
//         default:
//             lexical_error();
//     }
// }
int main() {
    input = fopen(input_file, "r");
    output = fopen(output_file, "w");

    // while (read_word_from_file())
    // printf("%s", word);

    // while (read_word_from_file())
    while ((d = getfchar(input))!=EOF) {
        // ungetc(c, input);
        analyser();
    }
    fclose(input);
    fclose(output);

    return 0;
}