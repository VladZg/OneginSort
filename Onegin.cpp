#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>

// #define NDEBUG
#include "defines.h"
#include "functions.h"


int main()
{
    char* data_0 = nullptr;
    char* data = nullptr;

    FILE* fileinp = fopen(FILENAME_INPUT, "r");

    int data_length = read_file(fileinp, &data, &data_0);
    // int file_length = read_file(fileinp, &data);

    fclose(fileinp);


    int text_lines_amount = symb_count('\n', data);

    char** text = (char**) calloc(text_lines_amount + 1, sizeof(char *));

    fill_text(data, text, data_length);


    FILE* fileout_sorted = fopen(FILENAME_OUTPUT_SORTED, "w");
    FILE* fileout_original = fopen(FILENAME_OUTPUT_ORIGINAL, "w");

    buble_sort(text, (size_t) text_lines_amount, sizeof(char*), cmp_left_to_right);
    FPUTS_BUBLESORTED_TEXT

    qsort(text, (size_t) text_lines_amount, sizeof(char*), cmp_right_to_left);
    FPUTS_QSORTED_TEXT

    FPUTS_ORIGINAL_TEXT

    fclose(fileout_sorted);
    fclose(fileout_original);


    // while (*text != NULL)
    //     printf("%s", *text++);

    // printf("%s", data);

    free(data);
    free(data_0);
    free(text);


    return 0;
}
