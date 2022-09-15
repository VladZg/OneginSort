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



int read_file_data(FILE* file, char data[])    // считывание файла в строку
{
    ASSERT(file != NULL);
    ASSERT(data != NULL);

    // fseek(file, 0L, SEEK_END); //сдвигает курсор в конец файла
    // int file_size = ftell(file); //возвращает положение "курсора"
    // fseek(file, 0L, SEEK_SET); //сдвигает курсор в начало файла

    struct stat buf;

    fstat(fileno(file), &buf);

    int file_size = buf.st_size;

    return fread(data, sizeof(char), file_size, file);
}


int open_read_close_file(const char file_name[], char data[], char data_0[])    // открытие, считывание, закрытие файла
{
    ASSERT(file_name != NULL);
    ASSERT(data != NULL);
    ASSERT(data_0 != NULL);

    FILE* file = fopen(file_name, "r");

    int n = read_file_data(file, data);
    strncpy(data_0, data, n);

    fclose(file);

    return n;
}


int create_ptr_arr(char* data_ptr, char data[], char* arr[], int n)    // создание массива указателей на строки
{
    ASSERT(data_ptr != NULL);
    ASSERT(data != NULL);
    ASSERT(arr != NULL);

    int arr_length = 0, k = 0, str_length = 0;

    for (int i = 0; i < n; i++)
    {
        if (data[i] == '\n')
        {
            data[i] = '\0';
            arr[k++] = data_ptr;
            data_ptr += ++str_length;
            arr_length++;
            str_length = 0;
        }
        else
            str_length++;
    }

    arr[arr_length] = NULL;

    return arr_length;
}


void printf_arr(char* arr[])    // распечатка массива
{
    ASSERT(arr != NULL);

    while (*arr != NULL)
    {
        printf("%s\n", *arr++);
    }
}


int str_cmp_letters_only(const char* string1, const char* string2)  // сравнение строк без знаков пунктуации
{
    ASSERT(string1 != NULL);
    ASSERT(string2 != NULL);

    int i1 = 0, i2 = 0, flag1 = 0, flag2 = 0;
    int length1 = strlen(string1), length2 = strlen(string2);

    flag1 = isalpha(string1[i1]);
    flag2 = isalpha(string2[i2]);

    while((i1 <= length1) && (i2 <= length2))
    {
        while (!(flag1 && flag2))
        {
            if (!flag1)
                flag1 = isalpha(string1[++i1]);

            if (!flag2)
                flag2 = isalpha(string2[++i2]);
        }

        if (string1[i1] != string2[i2])
            break;

        if (string1[i1++] == '0')
            return 0;
    }

    return string1[i1] - string2[i2];
}


void reverse_str(const char str[], int length, char str_rev[])  // переворот строки
{
    ASSERT(str != NULL);
    ASSERT(str_rev != NULL);

    int i = length-1, j = 0;

    for (; i >= 0; i--, j++)
    {
        str_rev[j] = str[i];
    }
}


int cmp_func1(const void* str1_ptr, const void* str2_ptr)   // сравнение строк слева-направо
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);

    const char* str1 = *(const char**)str1_ptr;
    const char* str2 = *(const char**)str2_ptr;

    return str_cmp_letters_only(str1, str2);  // заменить на собственный strcmp, удаляющий не буквы
}


int cmp_func2(const void* str1_ptr, const void* str2_ptr)   // сравнение строк справа-налево
{
    ASSERT(str1_ptr != NULL);
    ASSERT(str2_ptr != NULL);

    const char* str1 = *(const char**)str1_ptr;
    const char* str2 = *(const char**)str2_ptr;

    int str1_length = strlen(str1);
    int str2_length = strlen(str2);
    char str1_rev[100] = {};
    char str2_rev[100] = {};

    reverse_str(str1, str1_length, str1_rev);
    reverse_str(str2, str2_length, str2_rev);

    return str_cmp_letters_only(str1_rev, str2_rev);  // заменить на собственный strcmp, удаляющий знаки пунктуации
}


void buble_sort(char* arr[], int n, int (*cmp_func)(const void* str1, const void* str2))    // собственная сортировка (пузырьком)
{
    ASSERT(arr != NULL);

    for (int i = n; i >= 0; i--)
    {
        for (int j = 0; j < i-1; j++)
        {
            // printf("\"%s\" \"%s\" -> ", arr[j], arr[j+1]);

            if (cmp_func(&arr[j], &arr[j+1]) >= 0)
            {
                char* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }

            // printf("\"%s\" \"%s\"\n", arr[j], arr[j+1]);
        }

        // printf("\n");
    }
}


void sort_and_output(char* arr[], int arr_length, char data_0[])    // сортировки и вывод массивов
{
    ASSERT(arr != NULL);
    ASSERT(data_0 != NULL);


    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  \n"
           "СОБСТВЕННАЯ СОРТИРОВКА (прямой порядок):"
           "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    buble_sort(arr, arr_length, cmp_func1);

    printf_arr(arr);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");


    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "СОБСТВЕННАЯ СОРТИРОВКА (обратный порядок):"
           "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    buble_sort(arr, arr_length, cmp_func2);

    printf_arr(arr);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");



    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "ВСТРОЕННАЯ СОРТИРОВКА (прямой порядок):"
           "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    qsort(arr, (size_t) arr_length, sizeof(char*), cmp_func1);

    printf_arr(arr);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");


    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "ВСТРОЕННАЯ СОРТИРОВКА (обратный порядок):"
           "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    qsort(arr, (size_t) arr_length, sizeof(char*), cmp_func2);

    printf_arr(arr);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");



    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "НАЧАЛЬНЫЙ МАССИВ:"
           "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s", data_0);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}


int main()
{
    char* arr[100] = {};
    char data_0[2000] = {};
    char data[2000] = {};
    char* data_ptr = data;
    const char file_name[] = "text.txt";


    // сделать динамическую память (глава 8.7 и страница 242)
    // отдельная библиотека для считывания и обработки файлов


    int n = open_read_close_file(file_name, data, data_0);
    int arr_length = create_ptr_arr(data_ptr, data, arr, n);

    sort_and_output(arr, arr_length, data_0);

    return 0;
}
