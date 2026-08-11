/*
 * Bare-metal LED blink code for STM32N6570-DK
 * Target: STM32N657X0 (Cortex-M55)
 */

#include <stdint.h>
#include "CONFIG.h"

/* --- Simple Delay Function --- */
//SysTick: Basic function only—counts down to zero and triggers an interrupt.
//static void delay(volatile uint32_t count) {
//    while (count--) {
//        __asm__("nop");
//    }
//}

static void delay_ms(uint32_t ms) {
	uint32_t sys_clk_hz = 64000000U;
    SYSTICK_LOAD = (sys_clk_hz / 1000U) - 1U; // Set reload value for 1 ms
    SYSTICK_VAL  = 0U;                        // Clear current count
    SYSTICK_CTRL = (1U << 0) | (1U << 2);      // Enable SysTick with processor clock

    for (uint32_t i = 0; i < ms; i++) {
        /* Wait until COUNTFLAG (bit 16) is set to 1 */
        while (!(SYSTICK_CTRL & (1U << 16))) {
            __asm__("nop");
        }
    }

    SYSTICK_CTRL = 0U; // Disable SysTick when done
}

int main(void) {
    //Step 1: Enable Peripheral Clocks for GPIO Ports
    *(volatile uint32_t *)((uintptr_t)RCC_BASE + 0x30UL) |= (1U << 0) | (1U << 1); // Enable GPIOA, GPIOB clocks

    // Clear mode bits and set to general purpose output mode (01)
    GPIOA->MODER &= ~(3U << (0 * 2));
    GPIOA->MODER |=  (1U << (0 * 2));

    GPIOB->MODER &= ~(3U << (0 * 2));
    GPIOB->MODER |=  (1U << (0 * 2));

    //Toggle LEDs
    while (1) {
        /* Atomic set bits via BSRR (Bits 0-15 to set, 16-31 to reset) */
        GPIOA->BSRR = (1U << 0);        // Turn LED 1 ON
        GPIOB->BSRR = (1U << 0);        // Turn LED 2 ON
        delay_ms(1000000);

        /* Atomic reset bits */
        GPIOA->BSRR = (1U << (0 + 16)); // Turn LED 1 OFF
        GPIOB->BSRR = (1U << (0 + 16)); // Turn LED 2 OFF
        delay_ms(1000000);
    }
}
