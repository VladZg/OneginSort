#ifndef FUNCTIONS_H
#define FUNCTIONS_H


int  size_of_file       (FILE* file                            );

int  read_file_to_data  (FILE* file, char** data, int file_size);

void write_text_in_file (FILE* file, char** text               );


void fill_text(char* data, char** text, int data_length);


int symb_count     (char symb, char* string);

int is_letter_or_0 (char symb              );


void skip_non_letters    (const char** string1,  const char** string2,   const int direction);

int  strcmp_letters_only (const char** string1,  const char** string2,   const int direction);

int  cmp                 (const void*  str1_ptr, const void*  str2_ptr,  const int direction,   int (*strcmp_letters_only)(
                          const char** string1,  const char** string2,   const int direction));

int  cmp_left_to_right   (const void*  str1_ptr, const void*  str2_ptr                       );

int  cmp_right_to_left   (const void*  str1_ptr, const void*  str2_ptr                       );


void buble_sort(char* arr[], size_t arr_length, int size, int (*cmp)(const void* str1, const void* str2));


void fputs_original(FILE* file, char* data, int data_length);


#endif
