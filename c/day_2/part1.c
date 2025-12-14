#include <stdio.h>
#include <stdlib.h>

int calc(long start, long end)
{
    long total = 0;

    for (int k = 1; k <= 6; k++)
    {
        long base = 1;
        for (int i = 0; i < k; i++)
        {
            base *= 10;
        }
        for (long x = base / 10; x < base; x++)
        {
            long n = x * base + x;

            if (n >= start && n <= end)
            {
                total += n;
            }
            if (n > end)
                break;
        }
    }
    return total;
}

int invalids(const char* line)
{
    long total = 0;

    while (*line)
    {
        char* end;

        long first = strtol(line, &end, 10);
        if (end == line)
            break;
        line = end;

        if (*line != '-')
            break;
        line++;

        long second = strtol(line, &end, 10);
        if (end == line)
            break;
        line = end;

        total += calc(first, second);

        if (',' == *line)
        {
            line++;
        }
        break;
    }
    return total;
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

    char line[512];
    int result = 0;

    while (fgets(line, sizeof(line), input))
    {
        result = invalids(line);
    }
    fclose(input);

    printf("%i", result);
    return 0;
}
