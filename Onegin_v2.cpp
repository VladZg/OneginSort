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



int read_file_data(FILE* file, char** data_ptr, int file_size)    // считывание файла в строку
{
    ASSERT(file != NULL);
    ASSERT(data_ptr != NULL);

    *data_ptr = (char*) calloc(file_size, sizeof(char));
    free(*data_ptr);

    if (!(*data_ptr))
        return 0;

    return fread(*data_ptr, sizeof(char), file_size, file);
}


int open_read_close_file(const char* file_name, char** data_ptr, char** data_0_ptr)    // открытие, считывание, закрытие файла
{
    ASSERT(file_name != NULL);
    ASSERT(data_ptr != NULL);
    ASSERT(data_0_ptr != NULL);

    FILE* file = fopen(file_name, "r");
    struct stat buf;

    fstat(fileno(file), &buf);
    int file_size = buf.st_size;

    int n = read_file_data(file, data_ptr, file_size);

    *data_0_ptr = (char*) calloc(file_size, sizeof(char));
    free(*data_0_ptr);

    if (!(*data_0_ptr))
        return 0;

    strncpy(*data_0_ptr, *data_ptr, n);

    fclose(file);

    return n;
}


void printf_arr(char* arr[])    // распечатка массива
{
    ASSERT(arr != NULL);

    while (*arr != NULL)
    {
        printf("%s\n", *arr++);
    }
}


int cymb_count(char cymb, char* string)
{
    int count = 0;

    while (*string != '\0')
    {
        if (*string++ == cymb)
            count++;
    }

    return count;
}


int is_letter(char cymb)
{
    if (isalpha(cymb) || (cymb == '\0'))
        return 1;

    return 0;
}


int strcmp_letters_only(const char* string1, const char* string2)  // сравнение строк без знаков пунктуации
{
    ASSERT(string1 != NULL);
    ASSERT(string2 != NULL);

    int flag1 = is_letter(*string1), flag2 = is_letter(*string2);

    while(*string1 != '\0')
    {
        while (!(flag1 && flag2))
        {
            if (!flag1)
                flag1 = is_letter(*(++string1));

            if (!flag2)
                flag2 = is_letter(*(++string2));
        }

        if ((*string1 == '\0') || (*string2 == '\0'))
            return 0;

        if (*string1 != *string2)
            break;

        flag1 = is_letter(*(++string1));
        flag2 = is_letter(*(++string2));
    }

    return *string1 - *string2;
}


int cmp_func1(const void* str1_ptr, const void* str2_ptr)   // сравнение строк слева-направо
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);

    return strcmp_letters_only(*(const char**) str1_ptr, *(const char**) str2_ptr);
}


void create_ptr_arr(char** data_ptr, char* arr[], int data_length, int arr_length)    // заполнение массива указателей на строки
{
    ASSERT(data_ptr != NULL);
    ASSERT(arr != NULL);

    int str_length = 0;

    for (int i = 0; i < data_length; i++)
    {
        if (*(*data_ptr) == '\n')
        {
            *(*data_ptr) = '\0';
            *data_ptr -= str_length;
            *arr++ = *data_ptr;
            *data_ptr += str_length;
            str_length = 0;
        }
        else
            str_length++;

        (*data_ptr)++;
    }

    *arr++ = NULL;
}


void buble_sort(char* arr[], size_t arr_length, int size, int (*cmp_func)(const void* str1, const void* str2))    // собственная сортировка (пузырьком)
{
    ASSERT(arr != NULL);
    ASSERT(cmp_func != NULL);

    for (int i = (int) arr_length; i >= 0; i--)
    {
        for (int j = 0; j < i-1; j++)
        {
            if (cmp_func(&arr[j], &arr[j+1]) >= 0)
            {
                char* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


void sort_and_output(char* arr[], int arr_length, char* data_0)    // сортировки и вывод массивов
{
    ASSERT(arr != NULL);
    ASSERT(data_0 != NULL);


    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  \n"
           "СОБСТВЕННАЯ СОРТИРОВКА (прямой порядок):"
           "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    buble_sort(arr, (size_t) arr_length, sizeof(char*), cmp_func1);

    printf_arr(arr);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");


//     printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
//            "СОБСТВЕННАЯ СОРТИРОВКА (обратный порядок):"
//            "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//
//     buble_sort(arr, arr_length, cmp_func2);
//
//     printf_arr(arr);
//     printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");



    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "ВСТРОЕННАЯ СОРТИРОВКА (прямой порядок):"
           "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    qsort(arr, (size_t) arr_length, sizeof(char*), cmp_func1);

    printf_arr(arr);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");


//     printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
//            "ВСТРОЕННАЯ СОРТИРОВКА (обратный порядок):"
//            "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//
//     qsort(arr, (size_t) arr_length, sizeof(char*), cmp_func2);
//
//     printf_arr(arr);
//     printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");



    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "НАЧАЛЬНЫЙ МАССИВ:"
           "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s", data_0);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}



int main()
{
    char* data_0 = nullptr;
    char* data = nullptr;
    const char* file_name = "text.txt";

    int file_length = open_read_close_file(file_name, &data, &data_0);
    int arr_length = cymb_count('\n', data);

    char* arr[arr_length+1] = {};

    create_ptr_arr(&data, arr, file_length, arr_length);
    sort_and_output(arr, arr_length, data_0);

    return 0;
}
