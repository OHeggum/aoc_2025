#include <math.h>
#include <stdio.h>
#include <string.h>

static int digits(long n)
{
    int d = 0;
    do
    {
        d++;
        n /= 10;
    } while (n);
    return d;
}

int calc(long start, long end)
{
    long total = 0;

    int d_start = digits(start);
    int d_end = digits(end);

    if (d_start == d_end && (d_start % 2) != 0)
    {
        long lower = (long)pow(10, d_start - 1);
        long upper = (long)pow(10, d_start);

        if (start >= lower && end < upper)
        {
            return 0;
        }
    }

    long num = start / (long)pow(10, d_start / 2);

    for (long i = start; i <= end; i++)
    {
        if (num != 0 && (i % num) == 0)
        {
            total += num;
        }
    }

    printf("total: %ld\n", total);
    return total;
}

int invalids(char* line)
{
    int total = 0;
    char* pair = strtok(line, ",");
    while (pair != NULL)
    {
        printf("%s\n", pair);
        long first, last;

        if (sscanf(pair, "%ld-%ld", &first, &last) == 2)
        {
            total += calc(first, last);
        }
        pair = strtok(NULL, ",");
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
