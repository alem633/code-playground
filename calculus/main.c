#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRECISION 1e-19

typedef struct {
  /* x starts with a value of either 0 or 1 */
  long double x;
  long double fx;

  /* n is a num in N that will be used as denominator of 1/n (epsilon). */
  long double n;
  long double epsilon;
} Equation;

void getFx(Equation*);

/* This program approximates the value of the math expression cosx = x. */
int main(void) {
  srand(time(NULL));

  Equation buff;

  buff.x = rand() % 2;

  buff.n = 1;
  buff.epsilon;
  do {
    getFx(&buff);

    buff.epsilon = 1/buff.n;

    if (buff.fx < 0) 
      buff.x -= buff.epsilon;
    else if (buff.fx > 0) 
      buff.x += buff.epsilon;

    buff.n *= 2;
  } while (fabsl(buff.fx) > PRECISION);

  printf("Given:\n\n\tf(x) = cos(x) - x\n\n"
         "when fx approaches:   %.100Le\n"
         "x is of value:        %.100Le\n"
         "\n"
         "n is of value:        %.100Le\n"
         "epsilon is of value:  %.100Le\n"
         , buff.fx, buff.x, buff.n, buff.epsilon);

  return 0;
}

void getFx(Equation *buff) {
  long double x = buff->x;
  buff->fx = cosl(x) - x;
}
