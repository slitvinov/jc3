#include <stdio.h>
#include <math.h>

static double s;
static double x;
static double v;
static double F;
static int k;

static double reward(void);
static double action(void);

int
main(int agrc, char **argv)
{
    int L;
    double r;
    double R;

    x = 1;
    v = 0;
    L = 5;
    s = 1.0;
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
}

static double
reward(void)
{
    return x * x + s * F * F;
}

static double
action0(void)
{
    return -0.196078431372549;
}

static double
action1(void)
{
    double f[] = { -0.4705882352941176,
        0.08823529411764705,
        0.1176470588235294,
        0
    };
    return f[k];
}

static double
action2(void)
{
    return -0.2272025184027502 * x;
}

static double
action(void)
{
    return -0.2534710463934982 * x + 0.04087719298245614;
}
