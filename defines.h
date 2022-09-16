#ifndef DEFINES_H
#define DEFINES_H


# ifndef NDEBUG
    #define PRINT(cmd)                                                                    \
    {                                                                                     \
        fprintf(stderr, "\"%s\" in line %d in file \"%s\" in %s\n",                       \
        #cmd, __LINE__, __FILE__, __PRETTY_FUNCTION__);                                   \
        cmd;                                                                              \
    }

    #define ASSERT(condition)                                                             \
            {                                                                             \
            if (!(condition))                                                             \
                fprintf(stderr, "Error in '%s' in line %d in file \"%s\" in %s\n",        \
                        #condition, __LINE__, __FILE__, __PRETTY_FUNCTION__);             \
            }

#else
    #define ASSERT(condition) {}

#endif

#define FILENAME_INPUT_DEFAULT "text_input.txt"
#define FILENAME_OUTPUT_SORTED_DEFAULT "text_output_sorted.txt"
#define FILENAME_OUTPUT_ORIGINAL_DEFAULT "text_output_original.txt"

#ifndef FILENAME_INPUT
    #define FILENAME_INPUT FILENAME_INPUT_DEFAULT
#endif

#ifndef FILENAME_OUTPUT_SORTED
    #define FILENAME_OUTPUT FILENAME_OUTPUT_DEFAULT
#endif

#ifndef FILENAME_OUTPUT_SORTED
    #define FILENAME_OUTPUT_SORTED FILENAME_OUTPUT_SORTED_DEFAULT
#endif

#ifndef FILENAME_OUTPUT_ORIGINAL
    #define FILENAME_OUTPUT_ORIGINAL FILENAME_OUTPUT_ORIGINAL_DEFAULT
#endif


#endif
