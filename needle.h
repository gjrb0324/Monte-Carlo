#ifndef _NEEDLE_H
#define _NEEDLE_H

#ifndef NULL
#define NULL ((void *)0)
#endif

// The neele struct have two attributes length and angle, we will set those value with random value.
typedef struct needle{
    double length;
    double angle;
    double x;
    double y;
} needle;

extern double mean(double *pi_list, int size);
extern double sd(double *pi_list, double avg, int size);
#endif
