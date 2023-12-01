#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define min(a, b) (a < b ? a : b)

int digit_name_to_int(const char *str, int n);

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
        
        char f = 0, l = 0;
        
        for(int j = 0 ; f == 0 ; j++)
        {
            int left_digit_name_as_int;
            
            if(isdigit(line[j]))
                f = line[j] - '0';
            else if((left_digit_name_as_int = digit_name_to_int(line + j, linelen - j)) != -1)
                f = left_digit_name_as_int;
        }
        
        for(int j = linelen - 1 ; l == 0 ; j--)
        {
            int right_digit_name_as_int;
            
            if(isdigit(line[j]))
                l = line[j] - '0';
            else if((right_digit_name_as_int = digit_name_to_int(line + j, linelen - j)) != -1)
                l = right_digit_name_as_int;
        }
        
        sum += (f * 10) + l;
    }
    
    printf("%d\n", sum);
}

// since no digit name has more than 8 chars, it can be fully represented by a uint64_t
int digit_name_to_int(const char *str, int n)
{
    char digit_str[8] = { 0 };
    memcpy(digit_str, str, min(n, 8));
    
    // zero out the digit_str after the digit name
    if(digit_str[0] == 'o' || (digit_str[0] == 't' && digit_str[1] == 'w') || (digit_str[0] == 's' && digit_str[1] == 'i'))
    {
        memset(digit_str + 3, 0, 8 - 3);
    }
    else if(digit_str[0] == 'f' || digit_str[0] == 'n')
    {
        memset(digit_str + 4, 0, 8 - 4);
    }
    else if(digit_str[0] == 'e' || (digit_str[0] == 's' && digit_str[1] == 'e') || (digit_str[0] == 't' && digit_str[1] == 'h'))
    {
        memset(digit_str + 5, 0, 8 - 5);
    }
    
    uint64_t as_u64 = *(uint64_t*)&digit_str;
    
    constexpr uint64_t one   = 6647407;
    constexpr uint64_t two   = 7305076;
    constexpr uint64_t three = 435493693556;
    constexpr uint64_t four  = 1920298854;
    constexpr uint64_t five  = 1702259046;
    constexpr uint64_t six   = 7891315;
    constexpr uint64_t seven = 474148660595;
    constexpr uint64_t eight = 499967813989;
    constexpr uint64_t nine  = 1701734766;
    
    switch(as_u64)
    {
        case one:   return 1;
        case two:   return 2;
        case three: return 3;
        case four:  return 4;
        case five:  return 5;
        case six:   return 6;
        case seven: return 7;
        case eight: return 8;
        case nine:  return 9;
        default:    return -1;
    }
}
