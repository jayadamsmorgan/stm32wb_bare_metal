#include "uart.h"

#include "gpio.h"
#include "rcc.h"
#include "system.h"

void uart_init(unsigned long baud) {
    gpio_set_mode(PB6, GPIO_MODE_AF); // TX
    gpio_set_mode(PB7, GPIO_MODE_AF); // RX
    *RCC_APB2_ENR_REG |= 0b100000000000000;
    GPIO_B_REG->AFRL |= 0b01000110000000000000000000000000;
    USART1->CR1 = 0;
    USART1->BRR = FREQ / baud;
    USART1->CR1 = 0b00100000000000000000000000001101;
}

int uart_read_ready() {
    return USART1->ISR & 0b100000; // If RXNE bit is set, data is ready
}

uint8_t uart_read_byte() { return (uint8_t)(USART1->RDR & 255); }

void uart_write_byte(uint8_t byte) {
    USART1->TDR = byte;
    while ((USART1->ISR & 0b10000000) == 0)
        spin(1);
}

void uart_write_buf(char *buf, size_t len) {
    while (len-- > 0)
        uart_write_byte(*(uint8_t *)buf++);
}
