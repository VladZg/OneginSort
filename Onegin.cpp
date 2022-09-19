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
    char* data = nullptr;

    FILE* fileinp = fopen(FILENAME_INPUT, "r");

    int file_size   = size_of_file(fileinp);
    int data_length = read_file_to_data(fileinp, &data, file_size);

    fclose(fileinp);

    int text_lines_amount = symb_count('\n', data);

    char** text = (char**) calloc(text_lines_amount + 1, sizeof(char *));
    ASSERT(text != NULL);

    fill_text(data, text, data_length);

    FILE* fileout_sorted   = fopen(FILENAME_OUTPUT_SORTED, "w");
    FILE* fileout_original = fopen(FILENAME_OUTPUT_ORIGINAL, "w");

    buble_sort(text, (size_t) text_lines_amount, sizeof(char*), cmp_left_to_right);
    FPUTS_BUBLESORTED_TEXT

    qsort(text, (size_t) text_lines_amount, sizeof(char*), cmp_right_to_left);
    FPUTS_QSORTED_TEXT

    FPUTS_ORIGINAL_TEXT

    fclose(fileout_sorted);
    fclose(fileout_original);

    free(data);
    free(text);
    return 0;
}
