#include <stdio.h>
#include <stdlib.h>

int handle_line(const char* line, int* dial)
{
    if (!line || line[0] == '\n' || line[0] == '\0')
    {
        return 0;
    }

    char dir = line[0];
    if (dir != 'L' && dir != 'R')
    {
        return 0;
    }

    int clicks = atoi(&line[1]);
    int amount = clicks % 100;

    if ('L' == dir)
    {
        *dial = (*dial - amount) % 100;
        if (*dial < 0)
        {
            *dial += 100;
        }
    }
    if ('R' == dir)
    {
        *dial = (*dial + amount) % 100;
    }
    return (0 == *dial);
}

int main()
{
    FILE* input;
    input = fopen("input", "r");
    if (!input)
    {
        perror("fopen");
        return 1;
    }

    char line[5];
    int dial = 50;
    int total = 0;

    while (fgets(line, sizeof(line), input))
    {
        total += handle_line(line, &dial);
    }
    fclose(input);

    printf("%i", total);
    return 0;
}
