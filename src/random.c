#include <stdio.h>
#include <math.h>

static double R(double);

int
main()
{
    double alpha;
    double sigma;
    double d;
    double t;
    int k;

    t = 0.0;
    alpha = 1e-1;
    sigma = 1e-4;
    for (k = 0; k < 40; k++) {
        d = (R(t + sigma) - R(t - sigma)) / (2 * sigma);
        t += alpha * d;
        if (k % 10 == 0)
            fprintf(stderr, "%d %g\n", k, t);
    }
}


static double
R(double z)
{
    return -z * (z - 2);
}
