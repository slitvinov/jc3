#include <stdio.h>
#include <math.h>

static double s;
static double x;
static double v;
static double F;

static double reward(void);
static double action(void);

int
main(int agrc, char **argv)
{
    int k;
    int L;
    double r;
    double R;

    x = 1;
    v = 0;
    L = 5;
    s = 1.0;
    R = 0;
    for (k = 0; ; k++) {
        F = action();
        r = reward();
        R += r;
        printf("%12.6g %12.6g\n", x, R);
        if (k == L - 1)
          break;
        x += v;
        v += F;
    }
}

static double
reward(void)
{
    return x * x + s * F * F;
}

static double
action(void)
{
  return -0.196078431372549;
}
