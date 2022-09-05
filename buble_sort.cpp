#include <stdio.h>
#include <cstring>


void printf_arr(char* arr[], int n)
{
    for (int k = 0; k < n; k++)
    {
        printf("%s\n", arr[k]);
    }
}

int file_strings(const char* file_name)
{
    FILE* file = fopen(file_name, "r");
    int lines = 0;
    char c;

    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
            lines++;
    }

    fclose(file);

    return lines;
}

char* getline(FILE* file, char line[])
{
    int i = 0;
    char c;

    while ((c = fgetc(file)) != '\n')
        line[i++] = c;

    return line;
}

void read_file(const char* file_name, char* arr[], int n)
{
    FILE* file = fopen(file_name, "r");

    char line[n][2000] = {};

    for (int i = 0; i < n; i++)
    {
        arr[i] = getline(file, line[i]);
    }

    fclose(file);
}


void buble_sort(char* arr[], int n)
{
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
    char* arr[2000];
    const char *file_name = "text.txt";
    int n = file_strings(file_name);

    read_file(file_name, arr, n);

    buble_sort(arr, n);

    return 0;
}
