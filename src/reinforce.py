import random

def R(z):
    return - z * (z - 2)

def p(t):
    m, s = t
    return random.gauss(m, s)

def dlog(z, t):
    m, s = t
    return (2*(z-m))/s**2,  (2*z**2-(4*m*z+s**2)+2*m**2)/s**3

a = 1e-6
t = [0, 1]
for i in range(10000000):
    z = p(t)
    d = dlog(z, t)
    t[0] += a * R(z) * d[0]
    t[1] += a * R(z) * d[1]
    if i % 100000 == 0:
        print(t[0], t[1])
