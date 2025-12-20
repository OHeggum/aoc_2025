#include <stdio.h>
#include <string.h>

int battery_joltage(char *line) {
  int a = 0;
  int b = 0;
  int line_length = strlen(line);
  for (int i = 0; i < line_length; i++) {

    if (line[i] < '0' || line[i] > '9')
      continue;

    int num = line[i] - '0';
    if (i == line_length - 2 && num > b) {
      b = num;
      continue;
    }
    if (num > a) {
      a = num;
      b = 0;
      continue;
    }
    if (num > b) {
      b = num;
      continue;
    }
  }
  return a * 10 + b;
}

int main() {
  FILE *input;
  input = fopen("input_2", "r");
  if (!input) {
    perror("fopen");
    return 1;
  }

  char line[512];
  long result = 0;
  while (fgets(line, sizeof(line), input)) {
    result += battery_joltage(line);
  }
  fclose(input);

  printf("total: %lu", result);
  return 0;
}
