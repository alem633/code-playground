#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../ansi_colors.h"

#define KB (1024)
#define MB (KB * 1024)

#define BUFF_SIZE MB
#define EXCEPTION_IDX 37

typedef struct {
  long long negs;
  long long zeros;
  long long ones;

  long double negs_occurances; 
  long double zeros_occurances;
  long double ones_occurances;

} Log;

void get_occurances(Log *stats, size_t buff_size);
void init_buffer_get_stats(uint8_t *buff, Log *stats, size_t buff_size, int exception_idx);

static bool get_bit(uint8_t *buff, size_t bit_pos);
static void set_bit(uint8_t *buff, size_t bit_pos, bool val);

int main(void) {
  srand(time(NULL));

  Log stats = {0};

  uint8_t *buff = malloc(BUFF_SIZE);
  if (!buff) {
    fprintf(stderr, "[FATAL] malloc failed\n");
    exit(EXIT_FAILURE);
  }

  init_buffer_get_stats(buff, &stats, BUFF_SIZE, EXCEPTION_IDX);

  get_occurances(&stats, BUFF_SIZE);

  printf("[LOGGING]\n\n");

  printf( DARK_GREEN  "[%2d]:" RESET "  %12lld\n" , -1, stats.negs);
  printf( DARK_BLUE   "[%2d]:" RESET "  %12lld\n" ,  0, stats.zeros);
  printf( DARK_YELLOW "[%2d]: " RESET " %12lld\n" ,  1, stats.ones);

  printf("\n[BASIC STATS]\n\n");

  printf( DARK_GREEN  "- odds %2d:" RESET " %9.3Lf%%\n" , -1, stats.negs_occurances);
  printf( DARK_BLUE   "- odds %2d:" RESET " %9.3Lf%%\n" ,  0, stats.zeros_occurances);
  printf( DARK_YELLOW "- odds %2d:" RESET " %9.3Lf%%\n" ,  1, stats.ones_occurances);

  if (stats.zeros_occurances >= stats.ones_occurances) 
    printf( DARK_BLUE   "\n- %d appeared more often\n" RESET,  0);
  else if (stats.zeros_occurances < stats.ones_occurances) 
    printf( DARK_YELLOW "\n- %d appeared more often\n" RESET,  1);
  else
    printf( DARK_YELLOW "\n- %d appeared more often\n" RESET, -1);
  

  #if ROULETTE_MODE
    printf("\n[ROULETTE MODE]\n\n");
    printf( DARK_RED "score:" RESET " %9d", score);
  #endif

  free(buff);
  return 0;
}


void get_occurances(Log *stats, size_t buff_size) {
 stats->negs_occurances  = ( (long double) stats->negs / (buff_size * 8)) * 100;
 stats->zeros_occurances = ( (long double)stats->zeros / (buff_size * 8)) * 100;
 stats->ones_occurances  = ( (long double) stats->ones / (buff_size * 8)) * 100;
}

static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void init_buffer_get_stats(uint8_t *buff, Log *stats, size_t buff_size, int exception_idx) {
  for (size_t i=0;i<buff_size * 8;i++) {
    int val = rand() % 2;
    switch (val) {
      case 0:
        set_bit(buff, i, val);
        if (!(rand() % exception_idx)) {
          stats->negs++;
          break;
        }
        stats->zeros++;
        break;
      case 1:
        set_bit(buff, i, val);
        if (!(rand() % exception_idx)) {
          stats->negs++;
          break;
        }
        stats->ones++;
        break;
    }
  }
}

static bool get_bit(uint8_t *buff, size_t bit_pos) {
  if (buff[bit_pos >> 3] & (1 << (bit_pos & 7)))
    return 1;
  return 0;
}

static void set_bit(uint8_t *buff, size_t bit_pos, bool val) {
  if (val == 1)
    buff[bit_pos >> 3] |=  (1 << (bit_pos & 7));
  else
    buff[bit_pos >> 3] &= ~(1 << (bit_pos & 7));
}
