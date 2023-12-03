#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(FILE *file);
void part2(FILE *file);

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
    
    part2(file);
}

void part1(FILE *file)
{
    enum {
        RED_MAX = 12,
        GREEN_MAX = 13,
        BLUE_MAX = 14
    };
    
    unsigned int game_counter = 1;
    unsigned int sum = 0;
    while(!feof(file))
    {
        fscanf(file, "Game %*u:");
        
        char color[6] = { 0 };
        unsigned int num;
        int nb_reads = 3;
        char seperator[2];
        while(nb_reads == 3)
        {
            nb_reads = fscanf(file, "%u %[a-z]%[,;]", &num, color, seperator);
            if(
                (color[0] == 'r' && num > RED_MAX)   ||
                (color[0] == 'g' && num > GREEN_MAX) ||
                (color[0] == 'b' && num > BLUE_MAX))
            {
                goto impossible;
            }
        }
        
        sum += game_counter;
        
        impossible:
        fscanf(file, "%*[^\n]");
        fgetc(file);
        game_counter++;
    }
    
    printf("%u\n", sum);
}

void part2(FILE *file)
{
    char line[256] = { 0 };
    char *lineptr = line;
    unsigned int sum = 0;
    int game_num_str_length = 1;
    int next_level = 10;
    int game_number = 1;
    while(!feof(file))
    {
        int line_len;
        fscanf(file, "%255[^\n]%n\n", line, &line_len);
        lineptr = line;
        lineptr += sizeof("Game ") - 1;
        lineptr += game_num_str_length;
        lineptr += 2;
        
        unsigned int max_red = 0;
        unsigned int max_green = 0;
        unsigned int max_blue = 0;
        
        const char *limit = line + line_len;
        while(lineptr < limit)
        {
            unsigned int num;
            int after_letter;
            sscanf(lineptr, "%u%n", &num, &after_letter);
            lineptr += after_letter + 1;
            char color = lineptr[0];
            
            if(color == 'r' && num > max_red)
                max_red = num;
            if(color == 'g' && num > max_green)
                max_green = num;
            if(color == 'b' && num > max_blue)
                max_blue = num;
            
            switch(color)
            {
                case 'r': lineptr += 3 - 1 + 2; break;
                case 'g': lineptr += 5 - 1 + 2; break;
                case 'b': lineptr += 4 - 1 + 2; break;
            }
        }
        
        unsigned int power = (max_red * max_green * max_blue);
        sum += power;
        game_number++;
        if(game_number == next_level)
        {
            game_num_str_length++;
            next_level *= 10;
        }
    }
    
    printf("%u\n", sum);
}

