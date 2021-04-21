.POSIX:
.SUFFIXES:
.SUFFIXES: .c
CFLAGS = -Ofast -g
GSL_FLAGS = `gsl-config --libs --cflags`
0 = \
lqr\
lqr_random\
random\
reinforce\

all: $0
.c:; $(CC) $< $(CFLAGS) $(LDFLAGS) $(GSL_FLAGS) -o $@
clean:; @-rm $0
