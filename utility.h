/*
 * Utility declarations and globals used by the lexical analyzer.
 *
 * Created by taha on 10/31/25.
 */

#ifndef OUR_LEX_UTILITY_H
#define OUR_LEX_UTILITY_H

/* Default input/output file names used by the driver. */
char input_file[30] = "input.txt";
char output_file[30] = "output.txt";

/* Shared I/O streams for the analyzer. */
FILE *input = NULL, *output = NULL;

/* Scratch buffers and state used across DFAs and the driver. */
char word[100];
char* temp;
int start = 0;
char d;
int line_num = 1;
/* Token kinds recognized by the analyzer. */
typedef enum {
    SI,      /* 'si' keyword */
    ALORS,   /* 'alors' keyword */
    SINON,   /* 'sinon' keyword */
    OPREL,   /* relational operator: <, <=, =, <>, >, >= */
    ID,      /* identifier */
    NB       /* numeric literal */
} Tokens;

/*
 * write_to_file
 * Append a token label or text to the output stream. The caller ensures
 * the stream is open and writable.
 */
void write_to_file(const char* text) {
    fputs(text, output);
}

/* The commented code below was used for earlier experiments and is retained for reference. */
// void empty_buffer() {
//     for (int i = 0; word[i]!='\0'; word[i++] = '\0');
// }
// int read_word_from_file() {
//     empty_buffer();
//     char ch;
//     int i = 0;
//     while ((ch = fgetc(input)) != EOF && isspace(ch));
//     if (ch == EOF) return 0;
//     while (ch != EOF && !isspace(ch) && i < sizeof(word) - 1) {
//         word[i++] = ch;
//         ch = fgetc(input);
//     }
//     word[i] = '\0';
//     return 1;
// }
// char getstrchar(char** str) {
//     if (strlen(*str) == 0)
//         return '\0';
//     char c = str[0][0];
//     (*str) = &str[0][1];
//     return c;
// }

#endif // OUR_LEX_UTILITY_H