#include <stdio.h>
#include <cstring>
#define ASSERT(condition)                                                             \
        {                                                                             \
        if (!(condition))                                                             \
            fprintf(stderr, "Error in '%s' in line %d in file %s in %s\n",  \
                    #condition, __LINE__, __FILE__, __PRETTY_FUNCTION__);             \
        }


void printf_arr(char* arr[], int n)
{
    // ASSERT(arr != NULL);

    for (int k = 0; k < n; k++)
    {
        printf("%s\n", arr[k]);
    }
}


void buble_sort(char* arr[], int n)
{
    ASSERT(arr != NULL);

    printf_arr(arr, n);

    printf("\n");

    for (int i = n; i >= 0; i--)
    {
        for (int j = 0; j < i-1; j++)
        {
            printf("\"%s\" \"%s\" -> ", arr[j], arr[j+1]);

            if (strcmp(arr[j], arr[j+1]) >= 0)
            {
                char* temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }

            printf("\"%s\" \"%s\"\n", arr[j], arr[j+1]);
        }

        printf("\n");
    }

    printf_arr(arr, n);

}


int main()
{
    char* arr[1000] = {};
    char data[1000] = {};
    char* data_ptr = data;
    const char file_name[] = "text.txt";
    int n = 0;

    FILE* file = fopen(file_name, "r");

    n = fread(data, sizeof(char), 1000, file);

    fclose(file);

    int length = 0, k = 0, count = 0;

    for (int i = 0; i < n; i++)
    {
        if (*data_ptr == '\n')
        {
            data[i] = '\0';
            data_ptr -= count;
            arr[k++] = data_ptr;
            data_ptr += count;
            length++;
            count = 0;
        }
        else
            count++;
        data_ptr++;
    }

    buble_sort(arr, length);

    return 0;
}
