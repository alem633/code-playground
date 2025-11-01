# Roulette Odds Simulator

A minimal C program that generates a buffer of random bits, counts zeros, ones, and a rare “negative” event, and displays their percentages.

The program prints a table of percentages for each outcome.  

### What it does  
* Creates a buffer of size **1 MB** (`BUFF_SIZE`).  
* Fills it with random bits (0 or 1).  
* With probability **1/37** each bit is marked as a negative event.  
* Calculates the fraction of zeros, ones, and negatives over the total bits.  

### Customization  
* Change `BUFF_SIZE` to alter buffer size.  
* Modify `EXCEPTION_IDX` to adjust negative‑event frequency.  

This tool is a simple demonstration of probability distribution in a finite sample.

#### Demo

```
[LOGGING]

[-1]:      28282
[ 0]:     509379
[ 1]:     510915

[BASIC STATS]

- odds -1:     2.697%
- odds  0:    48.578%
- odds  1:    48.725%

- 1 appeared more often
```
