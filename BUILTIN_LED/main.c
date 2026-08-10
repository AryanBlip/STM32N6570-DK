
#include <stdint.h>
#include "CONFIG.h"


/* --- Simple Delay Function --- */
static void delay(volatile uint32_t count) {
    while (count--) {
        __asm__("nop");
    }
}

int main(void) {
    //Step 1: Enable Peripheral Clocks for GPIO Ports 
     *(RCC_BASE + 0x30) |= (1U << 0) | (1U << 1); // Enable GPIOA, GPIOB clocks

    //Step 2: Configure GPIO Pins as Push-Pull Outputs 
    // Clear mode bits and set to general purpose output mode (01)
    GPIOA->MODER &= ~(3U << (0 * 2));
    GPIOA->MODER |=  (1U << (0 * 2)); 

    GPIOB->MODER &= ~(3U << (0 * 2));
    GPIOB->MODER |=  (1U << (0 * 2));

    /* Step 3: Superloop to Toggle LEDs */
    while (1) {
        /* Atomic set bits via BSRR (Bits 0-15 to set, 16-31 to reset) */
        GPIOA->BSRR = (1U << 0);       // Turn LED 1 ON
        GPIOB->BSRR = (1U << 0);       // Turn LED 2 ON
        delay(1000000);

        /* Atomic reset bits */
        GPIOA->BSRR = (1U << (0 + 16)); // Turn LED 1 OFF
        GPIOB->BSRR = (1U << (0 + 16)); // Turn LED 2 OFF
        delay(1000000);
    }
}
