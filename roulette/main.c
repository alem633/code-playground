#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../ansi_colors.h"

#define KB (1024)
#define MB (KB * 1024)

#define BUFF_SIZE MB
#define EXCEPTION_IDX 37

#define ROULETTE_MODE 0

typedef struct {
  size_t negs;
  size_t zeros;
  size_t ones;

  long double negs_occurances; 
  long double zeros_occurances;
  long double ones_occurances;

} Log;

void get_occurances(Log *stats, size_t buff_size);
void init_buffer(signed char *buff, size_t buff_size, size_t exception_idx, size_t *score);
void log_stats(Log *stats,signed char *buff, size_t buff_size);

int main(void) {
  srand(time(NULL));

  Log stats = {0};

  signed char *buff = malloc(BUFF_SIZE);
  if (!buff) {
    fprintf(stderr, "[FATAL] malloc failed\n");
    exit(EXIT_FAILURE);
  }

  #if ROULETTE_MODE
    size_t score;
    init_buffer(buff, BUFF_SIZE, EXCEPTION_IDX, &score);
  #else
    init_buffer(buff, BUFF_SIZE, EXCEPTION_IDX, NULL);
  #endif

  log_stats(&stats, buff, BUFF_SIZE);

  printf("[LOGGING]\n\n");

  printf( DARK_GREEN  "[%2d]:" RESET "  %9zu\n" , -1, stats.negs);
  printf( DARK_BLUE   "[%2d]:" RESET "  %9zu\n" ,  0, stats.zeros);
  printf( DARK_YELLOW "[%2d]: " RESET " %9zu\n" ,  1, stats.ones);

  printf("\n[BASIC STATS]\n\n");

  get_occurances(&stats, BUFF_SIZE);

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
 stats->negs_occurances  = ( (long double) stats->negs / buff_size) * 100;
 stats->zeros_occurances = ( (long double)stats->zeros / buff_size) * 100;
 stats->ones_occurances  = ( (long double) stats->ones / buff_size) * 100;
}

static void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void init_buffer(signed char *buff, size_t buff_size, size_t exception_idx, size_t *score) {
  /* if variable score is not null roulette mode is activated */
  char roulette_mode = 0;
  if (score != NULL)
    roulette_mode = 1;

  for (size_t i=0;i<buff_size;i++) {
    buff[i] = rand() % 2;

    if (rand() % exception_idx == 0)
      buff[i] = -1;
    
    if (roulette_mode == 1) { // [TODO] i hate this code

      int guess = 0;
      do {

        printf(DARK_RED "[ROULETTE MODE]" RESET " guess [-1, 0, 1] (2 to quit): ");

        if (scanf("%d", &guess) != 1 || guess < -1 || guess > 2) {
          printf("Invalid input\n");
          clear_input_buffer(); 
          continue;
        }

        clear_input_buffer();

        if (guess == 2) {
          printf("Quitting...\n");
          roulette_mode = 0;
          break;
        }

        if (guess < -1 || guess > 1) {
          printf(DARK_RED "[ROULETTE MODE]" RESET " guess [-1, 0, 1] (2 to quit): ");
          continue;
        }

        if (guess == buff[i]) {
          printf("You guessed: %d\n", guess);
          (*score)++;
        }

        break;

      } while (1);

    }

  }

}

void log_stats(Log *stats,signed char *buff, size_t buff_size) {
  for (size_t i=0;i<buff_size;i++) {
    switch (buff[i]) {
      case -1:
        stats->negs++;
        break;
      case 0:
        stats->zeros++;
        break;
      case 1:
        stats->ones++;
        break;
    }
  }
}
