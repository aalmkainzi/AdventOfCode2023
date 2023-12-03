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
        int read_something = 3;
        char last_read[2] = { 0 };
        
        while(read_something == 3)
        {
            read_something = fscanf(file, "%u %[a-z]%[,;]", &num, color, last_read);
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
    unsigned int sum = 0;
    while(!feof(file))
    {
        fscanf(file, "Game %*u:");
        
        char color[6] = { 0 };
        unsigned int num;
        int read_something = 1;
        char last_read[2] = { 0 };
        
        unsigned int max_red = 0;
        unsigned int max_green = 0;
        unsigned int max_blue = 0;
        
        while(read_something > 0 && last_read[0] != '\n')
        {
            read_something = fscanf(file, "%u %[a-z]%[,;\n]", &num, color, last_read);
            if(color[0] == 'r' && num > max_red)
                max_red = num;
            if(color[0] == 'g' && num > max_green)
                max_green = num;
            if(color[0] == 'b' && num > max_blue)
                max_blue = num;
        }
        
        sum += (max_red * max_green * max_blue);
    }
    
    printf("%u\n", sum);
}

