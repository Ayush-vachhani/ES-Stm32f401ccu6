#include "interrupts_conf.h"
void configure_Interrupt_PA0()
{
    SYSCFG->EXTICR[0] &= ~(0xF << 0); // Clear EXTI0 bits in EXTICR
    SYSCFG->EXTICR[0] |= (0 << 0);    // Set EXTI0 to be triggered by PA0 (0b0000)
    EXTI->IMR |= (1 << 0);            // Unmask EXTI0 (enable interrupt)
    EXTI->FTSR |= (1 << 0);           // Set falling edge trigger for PA0
}

void configure_Interrupt_PA6()
{
    SYSCFG->EXTICR[1] &= ~(0xF << 8);
    SYSCFG->EXTICR[1] |= (0 << 8);
    EXTI->IMR |= (1 << 6);
    EXTI->FTSR |= (1 << 6);
}

void configure_Interrupt_B10()
{
    SYSCFG->EXTICR[2] &= ~(0xF << 8);
    SYSCFG->EXTICR[2] |= (0 << 8);
    EXTI->IMR |= (1 << 10);
    EXTI->FTSR |= (1 << 10);
}