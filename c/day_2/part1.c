#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t calc(uint64_t start, uint64_t end) {

  uint64_t total = 0;
  for (uint64_t i = start; i <= end; i++) {
    char buf[11];
    snprintf(buf, sizeof(buf), "%lu", i);
    if (strlen(buf) % 2 != 0)
      continue;

    int half_len = strlen(buf) / 2;
    char *half1 = malloc(half_len + 1);
    char *half2 = malloc(half_len + 1);
    memcpy(half1, buf, half_len);
    memcpy(half2, buf + half_len, half_len);
    half1[half_len] = '\0';
    half2[half_len] = '\0';

    if (strcmp(half1, half2) == 0) {
      total += i;
    }

    free(half1);
    free(half2);
  }
  printf("total for range: %lu\n", total);
  return total;
}

uint64_t invalids(char *line) {
  uint64_t total = 0;
  char *pair = strtok(line, ",");
  while (pair != NULL) {
    printf("%s\n", pair);
    uint64_t first, last;

    if (sscanf(pair, "%lu-%lu", &first, &last) == 2) {
      total += calc(first, last);
    }
    pair = strtok(NULL, ",");
  }
  return total;
}

int main() {
  FILE *input;
  input = fopen("input", "r");
  if (!input) {
    perror("fopen");
    return 1;
  }

  char line[512];
  uint64_t result = 0;

  while (fgets(line, sizeof(line), input)) {
    result = invalids(line);
  }
  fclose(input);

  printf("%lu", result);
  return 0;
}
