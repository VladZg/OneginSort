#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>
#define ASSERT(condition)                                                             \
        {                                                                             \
        if (!(condition))                                                             \
            fprintf(stderr, "Error in '%s' in line %d in file %s in %s\n",            \
                    #condition, __LINE__, __FILE__, __PRETTY_FUNCTION__);             \
        }



int read_file_data(FILE* file, char** data, int file_size)    // считывание файла в строку
{
    ASSERT(file != NULL);
    ASSERT(data != NULL);

    *data = (char*) calloc(file_size, sizeof(char));
    free(*data);

    if (!(*data))
        return 0;

    return fread(*data, sizeof(char), file_size, file);
}


int open_read_close_file(const char* file_name, char** data, char** data_0)    // открытие, считывание, закрытие файла
{
    ASSERT(file_name != NULL);
    ASSERT(data != NULL);
    ASSERT(data_0 != NULL);

    FILE* file = fopen(file_name, "r");
    struct stat buf;

    fstat(fileno(file), &buf);
    int file_size = buf.st_size;

    int n = read_file_data(file, data, file_size);

    *data_0 = (char*) calloc(file_size, sizeof(char));
    free(*data_0);

    if (!(*data_0))
        return 0;

    strncpy(*data_0, *data, n);

    fclose(file);

    return n;
}


// void printf_arr(char* arr[])    // распечатка массива
// {
//     ASSERT(arr != NULL);
//
//     while (*arr != NULL)
//     {
//         printf("%s\n", *arr++);
//     }
// }


int main()
{
    // char* arr[1000] = {};
    char* data_0 = nullptr;
    char* data = nullptr;
    const char* file_name = "text.txt";

    int n = open_read_close_file(file_name, &data, &data_0);

    printf("%s\n\n%s", data);

    return 0;
}
