#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

#define FREQ 16000000

void spin(volatile uint32_t count);

#endif // SYSTEM_H
