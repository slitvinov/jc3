#include <stdio.h>
#include <math.h>
#include <string.h>

static double s;
static int L;
static double x;
static double v;
static double F;
static int k;
static double t[3];

static double reward(void);
static double action(void);

static double
episod(void)
{
    double r;
    double R;

    x = 1;
    v = 0;
    R = 0;
    for (k = 0;; k++) {
        F = action();
        r = reward();
        R += r;
        if (k == L - 1)
            break;
        x += v;
        v += F;
    }
    return R;
}

int
main(int agrc, char **argv)
{
    double alpha;
    double d[2];
    double Rm;
    double Rp;
    double sigma;
    double t0[2];
    int c;
    int i;

    L = 5;
    s = 1.0;
    t[0] = t[1] = 0;
    sigma = 1e-4;
    alpha = 1e-2;
    for (i = 0; i < 100; i++) {
        for (c = 0; c < 2; c++) {
            memcpy(t, t0, sizeof t0);
            t[c] = t0[c] + sigma;
            Rp = episod();
            memcpy(t, t0, sizeof t0);
            t[c] = t0[c] - sigma;
            Rm = episod();
            d[c] = (Rp - Rm) / (2 * sigma);
        }
        for (c = 0; c < 2; c++)
            t0[c] -= alpha * d[c];
        printf("%12.6g %12.6g %12.6g\n", Rm, t0[0], t0[1]);
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
    return t[0] * x + t[1];
}
