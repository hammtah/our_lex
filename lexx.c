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

void success(int nb_automate) {
    switch (nb_automate) {
        case 0:
            write_to_file("si\n");
            printf("\nSI");
            start = 0;
            break;
        case 1:
            write_to_file("alors\n");
            printf("\nALORS");
            start = 0;
            break;
        case 4:
            write_to_file("id\n");
            printf("\nID");
            start = 0;
            break;
        default:
    }
}
void lexical_error() {
    printf("Lexical error!\n");
    start = 0;
    // if (read_word_from_file())
    //     analyser();
}
void not_mine_error() {
    start++;
    analyser();
}
void analyser() {
    switch (start) {
        case 0:
            state_si_0();
            break;
        case 1:
            state_alors_0();
            break;
        // case 2:
        //     // state_sinon_0();
        //     break;
        // case 3:
        //     // state_oprel_0();
        //     break;
        case 4:
            state_id_0();
            break;
        // case 5:
        //     // state_nb_0();
        //     break;
        default:
            lexical_error();
    }
}
int main() {
    input = fopen(input_file, "r");
    output = fopen(output_file, "w");

    // while (read_word_from_file())
    // printf("%s", word);

    while (read_word_from_file())
        analyser();
    fclose(input);
    fclose(output);

    return 0;
}