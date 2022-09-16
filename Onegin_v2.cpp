#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>

// #define NDEBUG
#include "defines.h"



void printf_arr(char** arr)                                                     // распечатка массива
{
    ASSERT(arr != NULL);

    while (*arr != NULL)
    {
        printf("%s\n", *arr++);
    }
}


int read_file_data(FILE* file, char** data_ptr, int file_size)                  // считывание файла в строку
{
    ASSERT(file != NULL);
    ASSERT(data_ptr != NULL);

    *data_ptr = (char*) calloc(file_size, sizeof(char));

    if (!(*data_ptr))
        return 0;

    return fread(*data_ptr, sizeof(char), file_size, file);
}


void write_data_file(FILE* fileout, char** arr)                                 // запись массива в файл
{
    ASSERT(fileout != 0);
    ASSERT(arr != 0);

    while (*arr != NULL)
    {
        fputs(*arr++, fileout);
        fputs("\n", fileout);
    }
}


int open_read_close_file(char** data_ptr, char** data_0_ptr)                    // открытие, считывание, закрытие файла
{
    ASSERT(data_ptr != NULL);
    ASSERT(data_0_ptr != NULL);

    FILE* file = fopen(FILENAME_INPUT, "r");

    struct stat buf;
    fstat(fileno(file), &buf);
    int file_size = buf.st_size;

    int n = read_file_data(file, data_ptr, file_size);

    *data_0_ptr = (char*) calloc(file_size, sizeof(char));

    if (!(*data_0_ptr))
        return 0;

    strncpy(*data_0_ptr, *data_ptr, n);

    fclose(file);

    return n;
}


void create_ptr_arr(char** data_ptr, char** arr,
                    int data_length, int arr_length)                            // заполнение массива указателей на строки
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


int cymb_count(char cymb, char* string)                                         // подсчёт кол-ва заданных символов в строке
{
    ASSERT(string != NULL);

    int count = 0;

    while (*string != '\0')
    {
        if (*string++ == cymb)
            count++;
    }

    return count;
}


int is_letter_or_0(char cymb)                                                   // проверка на небукву или \0
{
    return isalpha(cymb) || (cymb == '\0');
}


void skip_non_letters(const char** string1, const char** string2,
                      const int direction)                                      // пропускание первых небукв
{
    ASSERT(string1 != NULL);
    ASSERT(string2 != NULL);

    int flag1 = is_letter_or_0(**string1), flag2 = is_letter_or_0(**string2);

    while (!(flag1 && flag2))
    {
        if (!flag1)
            *string1 += direction;
            flag1 = is_letter_or_0(*((*string1)));

        if (!flag2)
            *string2 += direction;
            flag2 = is_letter_or_0(*(*string2));
    }
}


int strcmp_letters_only_func(const char** string1, const char** string2,
                             const int direction)                               // сравнение строк без знаков пунктуации
{
    ASSERT(string1 != NULL);
    ASSERT(string2 != NULL);

    if (direction == -1)
    {
        *string1 += strlen(*string1) - 1;
        *string2 += strlen(*string2) - 1;
    }

    skip_non_letters(string1, string2, direction);

    while(**string1 == **string2)
    {
        if (**string1 == '\0')
            return 0;

        *string1 += direction;
        *string2 += direction;
    }

    return **string1 - **string2;
}


int cmp_func(const void* str1_ptr, const void* str2_ptr, const int direction,
             int (*strcmp_letters_only_func)(const char** string1,
             const char** string2, const int direction))                        // общая функция сравнения void* строк
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);
    ASSERT (strcmp_letters_only_func != NULL);

    const char *string1 = *(const char**) str1_ptr;
    const char *string2 = *(const char**) str2_ptr;

    return strcmp_letters_only_func(&string1, &string2, direction);
}


int cmp_func1(const void* str1_ptr, const void* str2_ptr)                       // функция сравнения слева-направо
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);

    return cmp_func(str1_ptr, str2_ptr, 1, strcmp_letters_only_func);
}


int cmp_func2(const void* str1_ptr, const void* str2_ptr)                       // функция сравнения справа-налево
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);

    return cmp_func(str1_ptr, str2_ptr, -1, strcmp_letters_only_func);
}


void buble_sort(char* arr[], size_t arr_length, int size,
                int (*cmp_func)(const void* str1, const void* str2))            // собственная сортировка (пузырьком)
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


// void swap(void* l, void* r)                                                  // своп указателей друг на друга
// {
//
// }


// void buble_sort(void* arr, size_t arr_length, size_t size,                   // обобщённая собственная сортировка (пузырьком)
//                 int (*cmp_func)(const void* str1, const void* str2))                       // обобщённая собственная сортировка (пузырьком)
// {
//     ASSERT(arr != NULL);
//     ASSERT(cmp_func != NULL);
//
//     char* Arr = (char*) arr;
//     for (int i = (int) arr_length; i >= 0; i--)
//     {
//         for (int j = 0; j < i-1; j++)
//         {
//             if (cmp_func(Arr + j*size, Arr + (j+1)*size) >= 0)
//             {
//                 swap(Arr + j*size, Arr + (j+1)*size);
//             }
//         }
//     }
// }


void sort_and_output(FILE* fileout_sorted, FILE* fileout_original,
                     char* arr[], int arr_length, char* data_0)                 // сортировки и вывод массивов
{
    ASSERT(arr != NULL);
    ASSERT(data_0 != NULL);
    ASSERT(fileout_sorted != NULL);
    ASSERT(fileout_original != NULL);


    fputs("======================================================================"
          "\nСОБСТВЕННАЯ СОРТИРОВКА (прямой порядок):\n"
          "======================================================================"
          "\n", fileout_sorted);

    buble_sort(arr, (size_t) arr_length, sizeof(char*), cmp_func1);
    write_data_file(fileout_sorted, arr);

    fputs("======================================================================"
          "\n\n", fileout_sorted);


    fputs("======================================================================"
          "\nСОБСТВЕННАЯ СОРТИРОВКА (обратный порядок):\n"
          "======================================================================"
          "\n", fileout_sorted);

    buble_sort(arr, (size_t) arr_length, sizeof(char*), cmp_func2);
    write_data_file(fileout_sorted, arr);

    fputs("======================================================================"
          "\n\n", fileout_sorted);


    fputs("======================================================================"
          "\nВСТРОЕННАЯ СОРТИРОВКА (прямой порядок):\n"
          "======================================================================"
          "\n", fileout_sorted);

    qsort(arr, (size_t) arr_length, sizeof(char*), cmp_func1);
    write_data_file(fileout_sorted, arr);

    fputs("======================================================================"
          "\n\n", fileout_sorted);


    fputs("======================================================================"
          "\nВСТРОЕННАЯ СОРТИРОВКА (обратный порядок):\n"
          "======================================================================"
          "\n", fileout_sorted);

    qsort(arr, (size_t) arr_length, sizeof(char*), cmp_func2);
    write_data_file(fileout_sorted, arr);

    fputs("======================================================================"
          "", fileout_sorted);


    fputs("======================================================================"
          "\nНАЧАЛЬНЫЙ ТЕКСТ:\n"
          "======================================================================"
          "\n", fileout_original);


    fputs(data_0, fileout_original);

    fputs("======================================================================"
          "", fileout_original);
}


void output_files(char* arr[], int arr_length, char* data_0)                    // вывод всей инфы в файлы
{
    ASSERT(arr != NULL);
    ASSERT(data_0 != NULL);

    FILE* fileout_sorted = fopen(FILENAME_OUTPUT_SORTED, "w");
    FILE* fileout_original = fopen(FILENAME_OUTPUT_ORIGINAL, "w");

    sort_and_output(fileout_sorted, fileout_original, arr, arr_length, data_0);

    fclose(fileout_sorted);
    fclose(fileout_original);
}


void cleaner(char* data, char* data_0, int file_length)                         // очистка динамической памяти
{
    free((void*) (data-file_length));
    free((void*) data_0);
}


int main()
{
    char* data_0 = nullptr;
    char* data = nullptr;

    int file_length = open_read_close_file(&data, &data_0);
    int arr_length = cymb_count('\n', data);

    char* arr[arr_length+1] = {};

    create_ptr_arr(&data, arr, file_length, arr_length);
    output_files(arr, arr_length, data_0);

    cleaner(data, data_0, file_length);

    return 0;
}
