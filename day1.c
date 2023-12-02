#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char digit_name_to_num(const char *str);

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "no file given\n");
        exit(1);
    }
    
    FILE *file = fopen(argv[1], "r");
    
    if(file == NULL)
    {
        fprintf(stderr, "file doesn't exist\n");
        exit(1);
    }
    
    int sum = 0;
    char line[128] = { 0 };
    
    while(!feof(file))
    {
        fgets(line, sizeof(line), file);
        long linelen = strlen(line);
        
        char first_digit = 0, last_digit = 0;
        
        for(int j = 0 ; first_digit == 0 ; j++)
        {
            char left_digit_name_as_num;
            
            if(isdigit(line[j]))
                first_digit = line[j] - '0';
            else if((left_digit_name_as_num = digit_name_to_num(line + j)) != 0)
                first_digit = left_digit_name_as_num;
        }
        
        for(int j = linelen - 1 ; last_digit == 0 ; j--)
        {
            char right_digit_name_as_num;
            
            if(isdigit(line[j]))
                last_digit = line[j] - '0';
            else if((right_digit_name_as_num = digit_name_to_num(line + j)) != 0)
                last_digit = right_digit_name_as_num;
        }
        
        sum += (first_digit * 10) + last_digit;
    }
    
    printf("%d\n", sum);
    
    fclose(file);
}

#define CHARS_TO_U64_(A,B,C,D,E,...) ( \
    ((uint64_t)(A)) |       \
    ((uint64_t)(B) << 8)  | \
    ((uint64_t)(C) << 16) | \
    ((uint64_t)(D) << 24) | \
    ((uint64_t)(E) << 32))

#define CHARS_TO_U64(...) CHARS_TO_U64_(__VA_ARGS__,0,0)

char digit_name_to_num(const char *str) {
    uint64_t u64;
    memcpy(&u64, str, sizeof(u64));
    
    switch(u64 & 0xFFFFFFFFFF)
    {
        case CHARS_TO_U64('t','h','r','e','e'): return 3;
        case CHARS_TO_U64('s','e','v','e','n'): return 7;
        case CHARS_TO_U64('e','i','g','h','t'): return 8;
    }
    
    switch(u64 & 0xFFFFFFFF)
    {
        case CHARS_TO_U64('f','o','u','r'): return 4;
        case CHARS_TO_U64('f','i','v','e'): return 5;
        case CHARS_TO_U64('n','i','n','e'): return 9;
    }
    
    switch(u64 & 0xFFFFFF)
    {
        case CHARS_TO_U64('o','n','e'): return 1;
        case CHARS_TO_U64('t','w','o'): return 2;
        case CHARS_TO_U64('s','i','x'): return 6;
    }
    
    return 0;
}
