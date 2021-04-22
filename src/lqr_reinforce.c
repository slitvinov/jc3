#include <stdio.h>
#include <math.h>
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

enum {dim = 2};
static double s;
static int L;
static double x;
static double v;
static double F;
static int k;
static double t[dim];
static gsl_rng *r;
static double z[2*dim];

static double reward(void);
static double action(void);
static void sample(const double*, double *);
static void dlog(const double*, const double*, double*);

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
    double R;
    double aux;
    int c;
    int i;
    int j;
    int n;
    const gsl_rng_type *T;
    static double g[2*dim];

    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc(T);    
    L = 5;
    s = 1.0;
    n = 1;
    z[0] = 0; z[1] = 0.0001;
    z[2] = 0; z[3] = 0.0001;
    alpha = 1e-9;
    for (i = 0; i < 1000000; i++) {
      for (c = 0; c < 2 * dim; c++)
        g[c] = 0;
      for (j = 0; j < n; j++) {
        sample(z, t);
        R = episod();
        aux = alpha * R;
        dlog(t, z, g);
      }
      for (c = 0; c < 2 * dim; c++)
        z[c] += aux * g[c] / n;
      if (i % 10000 == 0)        
        printf("%12.6g %12.6g %12.6g\n", R, z[0], z[2]);
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

static void
sample(const double *z, double *t)
{
  double m;
  double s;

  m = z[0];
  s = z[1];
  t[0] = gsl_ran_gaussian(r, s) + m;

  m = z[2];
  s = z[3];
  t[1] = gsl_ran_gaussian(r, s) + m;  
}

static void
dlog(const double *t, const double *z, double *g)
{
  double m;
  double s;
  double x;

  m = z[0];
  s = z[1];
  x = t[0];
  g[0] += (2 * (x - m)) / (s * s);
  g[1] +=
    (2 * (x * x) - (4 * m * x + (s * s)) + 2 * (m * m)) / (s * s * s);

  m = z[2];
  s = z[3];
  x = t[1];
  g[2] += (2 * (x - m)) / (s * s);
  g[3] +=
    (2 * (x * x) - (4 * m * x + (s * s)) + 2 * (m * m)) / (s * s * s);
}
