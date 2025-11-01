//
// Created by taha on 10/31/25.
//

#ifndef OUR_LEX_UTILITY_H
#define OUR_LEX_UTILITY_H

char input_file[30] = "input.txt";
char output_file[30] = "output.txt";
FILE *input = NULL, *output = NULL;
char word[100];
char* temp;
int start = 0;

// void empty_buffer() {
//     for (int i = 0; word[i]!='\0'; word[i++] = '\0');
// }
// int read_word_from_file() {
//     empty_buffer();
//     char ch;
//     int i = 0;
//     // if (input == NULL) {
//     //     printf("Error opening input for reading!\n");
//     //     return 0;
//     // }
//     // Skip initial spaces, newlines, or tabs
//     while ((ch = fgetc(input)) != EOF && isspace(ch))
//         ;
//     if (ch == EOF) return 0;
//
//     // Read characters until space, newline, tab, or EOF
//     while (ch != EOF && !isspace(ch) && i < sizeof(word) - 1) {
//         word[i++] = ch;
//         ch = fgetc(input);
//     }
//     word[i] = '\0';  // null-terminate the string
//     // fclose(input);
//     return 1;
//
// }
void write_to_file(const char* text) {
    // if (output == NULL) {
    //     printf("Error opening output for writing!\n");
    //     return;
    // }
    fputs(text, output);
    // fclose(output);
}
// char getstrchar(char** str) {
//     if (strlen(*str) == 0)
//         return '\0';
//     char c = str[0][0];
//     (*str) = &str[0][1];
//     return c;
// }
#endif //OUR_LEX_UTILITY_H