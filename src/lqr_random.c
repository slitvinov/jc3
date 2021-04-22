#include <stdio.h>
#include <math.h>
#include <string.h>

enum {dim = 3};
static double s;
static int L;
static double x;
static double v;
static double F;
static int k;
static double t[dim];

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
        printf("%12.6g %12.6g %12.6g\n", x, v, R);
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
    double d[dim];
    double Rm;
    double Rp;
    double sigma;
    double t0[dim];
    int c;
    int i;

    L = 5;
    s = 1.0;
    t0[0] = t0[1] = 0;
    sigma = 1e-3;
    alpha = 1e-2;
    for (i = 0; i < 300; i++) {
        printf("episode %d\n", i + 1);
        for (c = 0; c < dim; c++) {
            memcpy(t, t0, sizeof t0);
            t[c] = t0[c] + sigma;
            Rp = episod();
            memcpy(t, t0, sizeof t0);
            t[c] = t0[c] - sigma;
            Rm = episod();
            d[c] = (Rp - Rm) / (2 * sigma);
        }
        for (c = 0; c < dim; c++)
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
