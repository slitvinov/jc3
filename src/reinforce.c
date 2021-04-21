#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

static gsl_rng *r;
static double p(const double *);
static int dlog(const double *, double, /**/ double *);
static double R(double);

int
main()
{
    const gsl_rng_type *T;
    double alpha;
    double d0[2];
    double d[2];
    double t[2];
    double aux;
    double z;
    int k;
    int j;
    int n;

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);
    t[0] = 0.0;
    t[1] = 1.0;
    alpha = 1e-5;
    n = 1;
    for (k = 0; k < 1000000; k++) {
        z = p(t);
        d[0] = 0;
        d[1] = 0;
        for (j = 0; j < n; j++) {
            dlog(t, z, d0);
            d[0] += d0[0];
            d[1] += d0[1];
        }
        aux = alpha * R(z) / n;
        t[0] += aux * d[0];
        t[1] += aux * d[1];
        if (k % 100000 == 0)
            fprintf(stderr, "%d %g %g\n", k, t[0], t[1]);
    }
    gsl_rng_free(r);
}

static double
p(const double *t)
{
    double m;
    double s;

    m = t[0];
    s = t[1];
    return gsl_ran_gaussian(r, s) + m;
}

static int
dlog(const double *t, double z, double *d)
{
    double m;
    double s;

    m = t[0];
    s = t[1];
    d[0] = (2 * (z - m)) / (s * s);
    d[1] =
        (2 * (z * z) - (4 * m * z + (s * s)) + 2 * (m * m)) / (s * s * s);
}

static double
R(double z)
{
    return -z * (z - 2);
}
