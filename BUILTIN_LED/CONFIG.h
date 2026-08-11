#ifndef CONFIG_LD1
#define CONFIG_LD1

#include <stdint.h>

/* --- Register Access Structures --- */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

/* Base Addresses (raw 32-bit integer addresses) */
#define PERIPH_BASE     (0x40000000UL)
#define AHB4PERIPH_BASE (PERIPH_BASE + 0x12000000UL)
#define RCC_BASE        (PERIPH_BASE + 0x08123000UL)

/* GPIO Base Addresses & Peripheral Pointers */
#define GPIOA_BASE      (AHB4PERIPH_BASE)
#define GPIOA           ((GPIO_TypeDef *) GPIOA_BASE)

#define GPIOB_BASE      (AHB4PERIPH_BASE + 0x0400UL)
#define GPIOB           ((GPIO_TypeDef *) GPIOB_BASE)

// SYSTICK TIMERS
#define SYSTICK_BASE (0xE000E010UL)
#define SYSTICK_CTRL (*(volatile uint32_t *)(SYSTICK_BASE + 0x00UL))
#define SYSTICK_LOAD (*(volatile uint32_t *)(SYSTICK_BASE + 0x04UL))
#define SYSTICK_VAL  (*(volatile uint32_t *)(SYSTICK_BASE + 0x08UL))

#endif
