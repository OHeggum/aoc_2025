#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Checks if a string represents a repeating pattern */
bool is_repetition(const char *s) {
  size_t len = strlen(s);
  if (len < 2)
    return false;

  for (size_t block = 1; block * 2 <= len; block++) {
    if (len % block != 0)
      continue;

    bool match = true;
    for (size_t i = block; i < len; i++) {
      if (s[i] != s[i % block]) {
        match = false;
        break;
      }
    }
    if (match)
      return true;
  }

  return false;
}

/* Calculates sum of numbers in range [start, end] whose decimal representation
 * repeats */
uint64_t sum_repetitions_in_range(uint64_t start, uint64_t end) {
  if (start > end)
    return 0; // guard against invalid ranges

  uint64_t total = 0;
  char buf[21]; // uint64_t max digits + null

  for (uint64_t i = start; i <= end; i++) {
    snprintf(buf, sizeof(buf), "%" PRIu64, i);
    if (is_repetition(buf)) {
      total += i;
    }
    if (i == UINT64_MAX)
      break; // prevent wraparound
  }

  return total;
}

/* Parses a line like "12-34,56-78" and sums all repetitions in all ranges */
uint64_t sum_repetitions_in_line(char *line) {
  uint64_t total = 0;
  line[strcspn(line, "\r\n")] = '\0'; // remove newline

  char *pair = strtok(line, ",");
  while (pair) {
    uint64_t start, end;
    if (sscanf(pair, "%" SCNu64 "-%" SCNu64, &start, &end) == 2) {
      if (start > end) {
        fprintf(stderr, "Warning: start > end in range '%s'\n", pair);
      } else {
        total += sum_repetitions_in_range(start, end);
      }
    } else {
      fprintf(stderr, "Warning: invalid range '%s'\n", pair);
    }
    pair = strtok(NULL, ",");
  }

  return total;
}

int main(void) {
  FILE *input = fopen("input", "r");
  if (!input) {
    perror("fopen");
    return 1;
  }

  char line[512];
  uint64_t final_total = 0;

  while (fgets(line, sizeof(line), input)) {
    final_total += sum_repetitions_in_line(line);
  }

  fclose(input);

  printf("Final total: %" PRIu64 "\n", final_total);
  return 0;
}
