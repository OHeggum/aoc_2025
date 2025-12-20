#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint64_t battery_joltage(char *line) {

  int num_indexes[9][100] = {0};
  uint64_t total = 0;

  int line_length = strlen(line);
  for (int i = 0; i < line_length; i++) {

    if (line[i] < '0' || line[i] > '9')
      continue;

    int num = line[i] - '0';

    num_indexes[num][i] = 1;
  }
  int solution[12] = {0};
  for (int i = 9; i > 0; i--) {
  }
  return total;
}

int main() {
  FILE *input;
  input = fopen("input_2", "r");
  if (!input) {
    perror("fopen");
    return 1;
  }

  char line[512];
  uint64_t result = 0;
  while (fgets(line, sizeof(line), input)) {
    result += battery_joltage(line);
  }
  fclose(input);

  printf("total: %lu", result);
  return 0;
}
