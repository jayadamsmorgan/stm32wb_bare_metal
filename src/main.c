// Copyright (c) 2022 Cesanta Software Limited
// All rights reserved

#include <inttypes.h>
#include <stdbool.h>

#include "gpio.h"

static inline void spin(volatile uint32_t count) {
    while (count--)
        asm("nop");
}

int main(void) {
    // *(volatile uint32_t *)(0x58000000 + 0x04C) = 2;
    gpio_turn_on_port(GPIO_PORT_B);
    // *(volatile uint32_t *)(0x48000400) = 0b11111111111111111111011010111111;
    // *(volatile uint32_t *)(0x48000400 + 0x18) = 32;

    gpio_set_mode(PIN_LED_BLUE,
                  GPIO_MODE_OUTPUT); // Set blue LED to output mode
    for (;;) {
        gpio_write(PIN_LED_BLUE, HIGH);
        spin(999999);
        gpio_write(PIN_LED_BLUE, LOW);
        spin(999999);
    }
    return 0;
}

// Startup code
__attribute__((naked, noreturn)) void _reset(void) {
    // memset .bss to zero, and copy .data section to RAM region
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss; dst < &_ebss; dst++)
        *dst = 0;
    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;)
        *dst++ = *src++;

    main(); // Call main()
    for (;;)
        (void)0; // Infinite loop in the case if main() returns
}

extern void _estack(void); // Defined in link.ld

// 16 standard and 91 STM32-specific handlers
__attribute__((section(".vectors"))) void (*const tab[16 + 91])(void) = {
    _estack, _reset};
