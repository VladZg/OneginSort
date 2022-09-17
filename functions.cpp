#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>

// #define NDEBUG
#include "defines.h"


int size_of_file        (FILE* file                             ) // узнать размер файла
{
    ASSERT(file != NULL);

    struct stat buf;
    fstat(fileno(file), &buf);
    return buf.st_size;
}

int  read_file_to_data  (FILE* file, char** data, int file_size ) // считывание файла в строку
{
    ASSERT(file != NULL);
    ASSERT(data != NULL);

    *data = (char*) calloc(file_size, sizeof(char));

    if (!(*data))
        return -1;

    return fread(*data, sizeof(char), file_size, file);
}

void write_text_in_file (FILE* file, char** text                ) // запись массива указателей в файл
{
    ASSERT(file != NULL);
    ASSERT(text != NULL);

    while (*text != NULL)
    {
        fputs(*text++, file);
        fputs("\n", file);
    }
}


void fill_text(char* data, char** text, int data_length) // заполнение массива указателей на строки
{
    ASSERT(data != NULL);
    ASSERT(text != NULL);

    int str_length = 0, i = 0;

    while (i++ < data_length)
    {
        if (*data == '\n')
        {
            *data = '\0';
            data -= str_length;
            *text++ = data;
            data += str_length;
            str_length = 0;
        }
        else
            str_length++;

        data++;
    }

    *text++ = nullptr;
}


int symb_count     (char symb, char* string) // подсчёт кол-ва заданных символов в строке
{
    ASSERT(string != NULL);

    int count = 0;

    while (*string != '\0')
    {
        if (*string++ == symb)
            count++;
    }

    return count;
}

int is_letter_or_0 (char symb              ) // проверка на небукву или \0
{
    return isalpha(symb) || (symb == '\0');
}


void skip_non_letters    (const char** string1,  const char** string2,  const int direction ) // пропускание первых небукв
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

int  strcmp_letters_only (const char** string1,  const char** string2,  const int direction ) // сравнение строк без знаков пунктуации
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

int  cmp                 (const void*  str1_ptr, const void*  str2_ptr, const int direction,
                                                                                              int (*strcmp_letters_only_func)(
                          const char** string1,  const char** string2,  const int direction)) // общая функция сравнения void* строк
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);
    ASSERT (strcmp_letters_only != NULL);

    const char *string1 = *(const char**) str1_ptr;
    const char *string2 = *(const char**) str2_ptr;

    return strcmp_letters_only(&string1, &string2, direction);
}

int  cmp_left_to_right   (const void*  str1_ptr, const void*  str2_ptr                      ) // функция сравнения слева-направо
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);

    return cmp(str1_ptr, str2_ptr, 1, strcmp_letters_only);
}

int  cmp_right_to_left   (const void*  str1_ptr, const void*  str2_ptr                      ) // функция сравнения справа-налево
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);

    return cmp(str1_ptr, str2_ptr, -1, strcmp_letters_only);
}


void buble_sort(char* arr[], size_t arr_length, int size, int (*cmp)(const void* str1, const void* str2)) // собственная сортировка (пузырьком)
{
ASSERT(arr != NULL);
ASSERT(cmp != NULL);

for (int i = (int) arr_length; i >= 0; i--)
{
for (int j = 0; j < i-1; j++)
{
if (cmp(&arr[j], &arr[j+1]) >= 0)
{
    char* temp = arr[j];
    arr[j] = arr[j+1];
    arr[j+1] = temp;
}
}
}
}


void fputs_original(FILE* file, char* data, int data_length) //печать в файл исходного текста
{
    for (int i = 0; i < data_length; i++)
    {
        if (*data != '\0')
            fputc(*data, file);

        else
            fputc('\n', file);

        data++;
    }

    data -= data_length;
}
