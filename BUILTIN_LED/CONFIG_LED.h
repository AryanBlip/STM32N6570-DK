#ifndef CONFIG_LD1
#define CONFIG_LD1

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


//Base Addresses
#define PERIPH_BASE     (volatile uint32_t*) 0x40000000UL
#define AHB4PERIPH_BASE ((volatile uint32_t*)(0x40000000UL + 0x12000000UL)) // Adjust per exact STM32N6 Reference Manual (RM0468/RM0495)

/* Note: Verify exact offset addresses in your specific STM32N6 Reference Manual */
#define RCC_BASE ((volatile uint32_t*)(PERIPH_BASE + 0x08123000UL))

// GPIOA
#define GPIOA_BASE ((volatile uint32_t*)(AHB4PERIPH_BASE))
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)

//GPIOB
#define GPIOB_BASE ((volatile uint32_t*)(AHB4PERIPH_BASE + 0x0400UL))
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)


#endif
