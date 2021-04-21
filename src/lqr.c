#include <stdio.h>
#include <math.h>

static double f0;
static double x;
static double v;
static double F;

static double reward(void);
static double action(void);

int
main()
{
  int i;
  int L;
  double r;
  double R;
  
  x = 1;
  v = 0;
  L = 100;
  f0 = 1.0;
  
  R = 0;
  for (i = 0; i < L; i++) {
    F = action();
    r = reward();
    R += r;
    x += v;
    v += F;
  }
}

static double
reward(void)
{
  return x*x + f0 * F;
}

static double 
action(void) {
  return -1;
}
