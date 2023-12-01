#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define min(a, b) (a < b ? a : b)

int digit_name_to_char(const char *str, int n);

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
    
    char **lines = NULL;
    arrput(lines, NULL);
    
    int i = 0;
    while(!feof(file))
    {
        int c = fgetc(file);
        if(c == '\n' || c == EOF)
        {
            arrput(lines[i], '\0');
            arrput(lines, NULL);
            i++;
        }
        else
        {
            arrput(lines[i], c);
        }
    }
    
    const long nb_lines = i;
    
    char (*results)[3] = calloc(nb_lines, sizeof(char[3]));
    
    for(int i = 0 ; i < nb_lines ; i++)
    {
        long linelen = strlen(lines[i]);
        char f = 0, l = 0;
        for(int j = 0, k = linelen - 1 ; f == 0 || l == 0 ; j++, k--)
        {
            if(!f)
            {
                int left_digit_name_as_char = digit_name_to_char(lines[i] + j, linelen - j);
                
                if(isdigit(lines[i][j]))
                    f = lines[i][j];
                else if(left_digit_name_as_char != -1)
                    f = left_digit_name_as_char;
            }
            if(!l)
            {
                int right_digit_name_as_char = digit_name_to_char(lines[i] + k, linelen - k);
                
                if(isdigit(lines[i][k]))
                    l = lines[i][k];
                else if(right_digit_name_as_char != -1)
                    l = right_digit_name_as_char;
            }
        }
        
        results[i][0] = f;
        results[i][1] = l;
    }
    
    int sum = 0;
    for(int i = 0 ; i < nb_lines ; i++)
    {
        sum += atoi(results[i]);
    }
    
    printf("%d\n", sum);
    
    for(int i = 0 ; i < arrlen(lines) ; i++)
    {
        arrfree(lines[i]);
    }
    
    arrfree(lines);
    free(results);
}

// since no digit name has more than 8 chars, it can be fully represented by a long
int digit_name_to_char(const char *str, int n)
{
    char digit_str[8] = { 0 };
    memcpy(digit_str, str, min(n, 8));
    
    // zero out the digit_str after the digit name
    if(digit_str[0] == 'o')
    {
        memset(digit_str + 3, 0, 8 - 3);
    }
    else if(digit_str[0] == 't')
    {
        if(digit_str[1] == 'w')
        {
            memset(digit_str + 3, 0, 8 - 3);
        }
        else if(digit_str[1] == 'h')
        {
            memset(digit_str + 5, 0, 8 - 5);
        }
    }
    else if(digit_str[0] == 'f')
    {
        memset(digit_str + 4, 0, 8 - 4);
    }
    else if(digit_str[0] == 's')
    {
        if(digit_str[1] == 'i')
        {
            memset(digit_str + 3, 0, 8 - 3);
        }
        else if(digit_str[1] == 'e')
        {
            memset(digit_str + 5, 0, 8 - 5);
        }
    }
    else if(digit_str[0] == 'e')
    {
        memset(digit_str + 5, 0, 8 - 5);
    }
    else if(digit_str[0] == 'n')
    {
        memset(digit_str + 4, 0, 8 - 4);
    }
    
    long as_long = *(long*)&digit_str;
    
    constexpr long one   = 6647407;
    constexpr long two   = 7305076;
    constexpr long three = 435493693556;
    constexpr long four  = 1920298854;
    constexpr long five  = 1702259046;
    constexpr long six   = 7891315;
    constexpr long seven = 474148660595;
    constexpr long eight = 499967813989;
    constexpr long nine  = 1701734766;
    
    switch(as_long)
    {
        case one:   return '1';
        case two:   return '2';
        case three: return '3';
        case four:  return '4';
        case five:  return '5';
        case six:   return '6';
        case seven: return '7';
        case eight: return '8';
        case nine:  return '9';
    }
    
    return -1;
}
