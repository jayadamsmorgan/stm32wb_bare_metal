#ifndef CLOCK_H
#define CLOCK_H

enum CLOCK_SOURCE { HSE, HSI };

static volatile unsigned system_clock_freq = 16000000;

void select_clock_source(enum CLOCK_SOURCE source);

#endif // CLOCK_H
