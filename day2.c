#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

enum {
    RED_MAX = 12,
    GREEN_MAX = 13,
    BLUE_MAX = 14
};

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
    
    unsigned int game_counter = 1;
    unsigned int sum = 0;
    while(!feof(file))
    {
        fscanf(file, "Game %*u:");
        
        char color[6] = { 0 };
        unsigned int num;
        int read_something = 1;
        char last_read[2] = { 0 };
        while(read_something > 0 && last_read[0] != '\n')
        {
            read_something = fscanf(file, "%u %[a-z]%[,;\n]", &num, color, last_read);
            if(
                (color[0] == 'r' && num > RED_MAX)   ||
                (color[0] == 'g' && num > GREEN_MAX) ||
                (color[0] == 'b' && num > BLUE_MAX))
            {
                goto impossible;
            }
        }
        
        sum += game_counter++;
        continue;
        
        impossible:
        if(last_read[0] != '\n') fscanf(file, "%*[^\n]\n");
        game_counter++;
    }
    
    printf("%u\n", sum);
}



