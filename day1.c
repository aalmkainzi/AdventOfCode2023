#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define min(a, b) (a < b ? a : b)

int letter_to_num(const char *str, int n)
{
    char digit_str[8] = { 0 };
    memcpy(digit_str, str, min(n, 8));
    
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
        if(digit_str[1] == 'o')
        {
            memset(digit_str + 4, 0, 8 - 4);
        }
        else if(digit_str[1] == 'i')
        {
            memset(digit_str + 4, 0, 8 - 4);
        }
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

int main()
{
    FILE *file = fopen("day1_input.txt", "r");
    
    char **lines = NULL;
    arrput(lines, NULL);
    
    int i = 0;
    while(!feof(file))
    {
        int c = fgetc(file);
        if(c == '\n')
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
    
    arrput(lines[i], '\0');
    
    long nb_lines = i;
    
    char (*results)[3] = calloc(nb_lines, sizeof(char[3]));
    
    for(int i = 0 ; i < nb_lines ; i++)
    {
        long linelen = strlen(lines[i]);
        char f = 0, l = 0;
        for(int j = 0, k = linelen - 1 ; f == 0 || l == 0 ; j++, k--)
        {
            int left_letter_as_num = letter_to_num(lines[i] + j, linelen - j);
            int right_letter_as_num = letter_to_num(lines[i] + k, linelen - k);
            if(!f)
            {
                if(isdigit(lines[i][j]))
                    f = lines[i][j];
                else if(left_letter_as_num != -1)
                    f = left_letter_as_num;
            }
            if(!l)
            {
                if(isdigit(lines[i][k]))
                    l = lines[i][k];
                else if(right_letter_as_num != -1)
                    l = right_letter_as_num;
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
