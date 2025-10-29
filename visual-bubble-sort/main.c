#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ARR_SIZE 32
#define MAX_NOISE 64

#if defined(__linux__) || defined(_WIN32)
  #define SHOULD_SHOW_SORTING_VISUALLY 1 // Change this if sorting should be silent
#else
  #define SHOULD_SHOW_SORTING_VISUALLY 0
#endif

#if SHOULD_SHOW_SORTING_VISUALLY

  #ifdef __linux__
    #include <unistd.h>
    void sleep_t(size_t ms) {
      usleep(ms * 1000);
    }
  #endif

  #ifdef _WIN32
    #include <windows.h>
    void sleep_t(size_t ms) {
      Sleep(ms);
    }
  #endif

#endif

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void bubbleSort(int arr[], size_t size);
void clearScreen();
void fillWithNoise(int arr[], int max_noise, size_t size);
/* void printArray(int arr[], size_t size, bool shouldPrintIndex); [DEBUG] */
void printArrayVisually(int arr[], size_t size);
void swap(int*, int*);

int main(void) {
  srand(time(NULL));

  int arr[ARR_SIZE];
  fillWithNoise(arr, MAX_NOISE, ARR_SIZE);

  bubbleSort(arr, ARR_SIZE);

  return 0;
}

void bubbleSort(int arr[], size_t size) {
  if (size <= 1) 
    return;

  for (size_t i=0;i<size-1;i++) {

    if (arr[i] > arr[i+1]) 
      swap(&arr[i], &arr[i+1]);

    if (SHOULD_SHOW_SORTING_VISUALLY) {
      /* [WARNING] this uses ARR_SIZE instead of local var size */
      printArrayVisually(arr, ARR_SIZE); 
      clearScreen();
      sleep_t(25);
    }

  }

  bubbleSort(arr, size-1);
}

void clearScreen() {
  printf("\e[1;1H\e[2J");
}

void fillWithNoise(int arr[], int max_noise, size_t size) {
  for (size_t i=0;i<size;i++) 
    arr[i] = rand() % max_noise;
}

/* [DEBUG]
void printArray(int arr[], size_t size, bool shouldPrintIndex) {
  for (size_t i=0;i<size;i++) {
    printf("[");

    if (shouldPrintIndex)
      printf("(i: %d) ", i);

    printf("%d]", arr[i]);

    if (i != size-1)
      printf(", ");
    else 
      printf("\n");

  }
}
*/

void printArrayVisually(int arr[], size_t size) {
  const char delimiterCh = '|';
  const char *valueCh = "\u25A0";

  for (size_t row=0;row<size;row++) {
    printf(ANSI_COLOR_RED "%4zu%c " ANSI_COLOR_RESET, row, delimiterCh);

    for (size_t i=0;i<arr[row];i++) {
      printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, valueCh);
    }

    printf("\n");
  }

}

void swap(int *val1, int *val2) {
  *val1 = *val1 ^ *val2;
  *val2 = *val1 ^ *val2;
  *val1 = *val1 ^ *val2;
}
