#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t check_thirds(uint64_t num, size_t length) {
  char buf[11];
  snprintf(buf, sizeof(buf), "%lu", num);
  int sequence_size = length / 3;
  char *third1 = malloc(sequence_size + 1);
  char *third2 = malloc(sequence_size + 1);
  char *third3 = malloc(sequence_size + 1);
  memcpy(third1, buf, sequence_size);
  memcpy(third2, buf + sequence_size, sequence_size);
  memcpy(third3, buf + sequence_size * 2, sequence_size);
  third1[sequence_size] = '\0';
  third2[sequence_size] = '\0';
  third3[sequence_size] = '\0';
  if (strcmp(third1, third2) == 0 && strcmp(third1, third3) == 0) {
    free(third1);
    free(third2);
    free(third3);
    return num;
  }
  free(third1);
  free(third2);
  free(third3);
  return 0;
}

uint64_t check_continuous(uint64_t num) {
  char buf[11];
  snprintf(buf, sizeof(buf), "%lu", num);
  for (int i = 1; buf[i] != '\0'; i++) {
    if (buf[0] != buf[i]) {
      return 0;
    }
  }
  return num;
}

uint64_t fifths_compare(uint64_t num) {
  char buf[11];
  snprintf(buf, sizeof(buf), "%lu", num);
  char *fifth1 = malloc(3);
  char *fifth2 = malloc(3);
  char *fifth3 = malloc(3);
  char *fifth4 = malloc(3);
  char *fifth5 = malloc(3);
  memcpy(fifth1, buf, 2);
  memcpy(fifth2, buf + 2, 2);
  memcpy(fifth3, buf + 4, 2);
  memcpy(fifth4, buf + 6, 2);
  memcpy(fifth5, buf + 8, 2);
  fifth1[2] = '\0';
  fifth2[2] = '\0';
  fifth3[2] = '\0';
  fifth4[2] = '\0';
  fifth5[2] = '\0';
  if (strcmp(fifth1, fifth2) == 0 && strcmp(fifth1, fifth3) == 0 &&
      strcmp(fifth1, fifth4) == 0 && strcmp(fifth1, fifth5) == 0) {
    free(fifth1);
    free(fifth2);
    free(fifth3);
    free(fifth4);
    free(fifth5);
    return num;
  }
  free(fifth1);
  free(fifth2);
  free(fifth3);
  free(fifth4);
  free(fifth5);
  return 0;
}
uint64_t calc(uint64_t start, uint64_t end) {

  uint64_t total = 0;
  for (uint64_t i = start; i <= end; i++) {
    char buf[11];
    snprintf(buf, sizeof(buf), "%lu", i);
    if (strlen(buf) == 1) {
      continue;
    }

    if (strlen(buf) % 3 == 0 && strlen(buf) != 3) {
      uint64_t result = check_thirds(i, strlen(buf));
      if (result > 0) {
        total += result;
        printf("instance_thirds: %lu\n", i);
        continue;
      }
    }
    if (strlen(buf) % 2 != 0) {
      uint64_t result = check_continuous(i);
      if (result > 0) {
        total += result;
        printf("instance_continuous: %lu\n", i);
      }
      continue;
    }
    if (strlen(buf) == 10) {
      uint64_t result = fifths_compare(i);
      if (result > 0) {
        total += result;
        printf("instance_fifths: %lu\n", i);
        continue;
      }
    }

    int half_len = strlen(buf) / 2;
    char *half1 = malloc(half_len + 1);
    char *half2 = malloc(half_len + 1);
    memcpy(half1, buf, half_len);
    memcpy(half2, buf + half_len, half_len);
    half1[half_len] = '\0';
    half2[half_len] = '\0';

    if (strcmp(half1, half2) == 0) {
      total += i;
      printf("instance_halves: %lu\n", i);
    }
    free(half1);
    free(half2);
  }
  printf("start: %lu, end: %lu, total: %lu\n", start, end, total);
  return total;
}

uint64_t invalids(char *line) {
  uint64_t total = 0;
  char *pair = strtok(line, ",");
  while (pair != NULL) {
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

  printf("total: %lu", result);
  return 0;
}
