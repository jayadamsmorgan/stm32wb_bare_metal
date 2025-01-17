#ifndef CLOCK_H
#define CLOCK_H

typedef enum { HSE, HSI } CLOCK_SOURCE;

static volatile unsigned system_clock_freq = 16000000;

void select_clock_source(CLOCK_SOURCE source);

#endif // CLOCK_H
