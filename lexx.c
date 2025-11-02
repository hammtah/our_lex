/*
 * Lexical analyzer driver.
 * - Orchestrates deterministic finite automata (DFAs) to recognize tokens.
 * - Manages success/error reporting, input pushback, and I/O loop.
 *
 * Created by taha on 10/31/25.
 */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "states.h"
#include "utility.h"

/* Forward declarations for cross-file functions implemented in states.h */
void analyser();
void lexical_error();
void not_mine_error();
void success(int nb_automate);

/*
 * success
 * Called by a DFA when a token has been recognized.
 * Writes the token kind to the output file, prints a debug label,
 * resets the DFA dispatch position, and clears the lexeme buffer.
 */
void success(int nb_automate) {
    switch (nb_automate) {
        case OPREL:
            write_to_file("oprel\t");
            printf("\tOPREL");
            start = 0;
            break;
        case ID:
            write_to_file("id\t");
            printf("\tID");
            start = 0;
            break;
        case NB:
            write_to_file("nb\t");
            printf("\tNB");
            start = 0;
            break;
        case SI:
            write_to_file("si\t");
            printf("\tSI");
            start = 0;
            break;
        case ALORS:
            write_to_file("alors\t");
            printf("\tALORS");
            start = 0;
            break;
        case SINON:
            write_to_file("sinon\t");
            printf("\tSINON");
            start = 0;
            break;
        default:
            /* Unknown automate id: nothing to emit, buffer will be cleared below. */
            break;
    }
    clear_buffer();
}

/*
 * lexical_error
 * Handles a lexical error when no DFA accepts the current input.
 * Resets the dispatch position, clears the buffer, and consumes one
 * character so the analysis can progress.
 */
void lexical_error() {
    printf("\nLexical error!\n");
    start = 0;
    clear_buffer();
    /* Consume the unrecognized character to move past the error. */
    fgetc(input);
}

/*
 * not_mine_error
 * Invoked by a DFA when the current input does not belong to it.
 * Restores the word read so far, advances to the next DFA, and retries analysis.
 */
void not_mine_error() {
    /* Return the word to the input so another DFA can attempt to consume it. */
    unget_word();
    start++;
    analyser();
}

/*
 * analyser
 * Dispatches to the next DFA based on 'start'. Each DFA either recognizes
 * a token (calls success), rejects and asks another DFA to try (calls not_mine_error),
 * or ultimately triggers a lexical error if none accept.
 */
void analyser() {
    switch (start) {
        case 0:
            state_si_0();
            break;
        case 1:
            state_alors_0();
            break;
        case 2:
            state_sinon_0();
            break;
        case 3:
            state_oprel_0();
            break;
        case 4:
            state_id_0();
            break;
        case 5:
            state_nb_0();
            break;
        default:
            lexical_error();
    }
}

/*
 * main
 * Opens input/output files, iterates over the input stream, and repeatedly
 * runs the analyser. Each loop fetches a non-space character, pushes it back,
 * and lets the DFAs consume as needed.
 */
int main() {
    input = fopen(input_file, "r");
    output = fopen(output_file, "w");

    char c;
    while ((c = getfchar(input)) != EOF) {
        /* Give the character back to the stream so the appropriate DFA can read it. */
        ungetc(c, input);
        analyser();
    }

    fclose(input);
    fclose(output);

    return 0;
}