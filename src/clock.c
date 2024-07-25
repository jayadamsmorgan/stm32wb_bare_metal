#include "clock.h"

#include "rcc.h"
#include "system.h"

void select_clock_source(enum CLOCK_SOURCE source) {
    switch (source) {
    case HSE:
        while ((*RCC_CR_REG & BIT(17)) == 0) {
            spin(1);
        }
        *RCC_CR_REG &= ~(BIT(8));
        *RCC_CR_REG |= BIT(16);
        system_clock_freq = 64000000;
        break;
    case HSI:
        while ((*RCC_CR_REG & BIT(10)) == 0) {
            spin(1);
        }
        *RCC_CR_REG &= ~(BIT(16));
        *RCC_CR_REG |= BIT(8);
        system_clock_freq = 16000000;
        break;
    }
}
