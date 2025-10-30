# Fixed-Point Cosine Solver

A tiny C program that numerically solves the equation **cos(x) = x** using a simple iterative method.

## How it works
- Starts with `x = 0` or `x = 1` (randomly chosen)
- Repeatedly adjusts `x` by $` \pm \upvarepsilon `$ (where $` \upvarepsilon = \frac{1}{n}`$, n doubles each iteration)
- Stops when |cos(x) − x| < 1e−19

## Build & Run
```bash
gcc -o solver solver.c -lm
./solver
```

Outputs the solution `x`, final function value, and iteration details with 100-digit precision.
