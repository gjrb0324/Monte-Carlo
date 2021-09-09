#ifndef _NEEDLE_H
#define _NEEDLE_H

#ifndef NULL
#define NULL((void *)0)
#endif

// The neele struct have two attributes length and angle, we will set those value with random value.
typedef struct needle{
    double length;
    double angle;
    double x;
    double y;
} needle;

#endif
