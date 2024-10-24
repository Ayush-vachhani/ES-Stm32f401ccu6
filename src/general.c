#include "general.h"
void setup_gpio_clocks()
{
    // RCC->AHB1ENR |= (1U << 0);
    // RCC->AHB1ENR |= (1U << 1);
    // RCC->AHB1ENR |= (1U << 2);
    // RCC->AHB1ENR |= (1U << 3);
    RCC->AHB1ENR = 15;
}

void configure_PA0()
{
    GPIOA->MODER &= ~(3 << 0);
    GPIOA->PUPDR &= ~(3 << 0);
    GPIOA->PUPDR |= (1 << 0);
}

void configure_PA6()
{
    GPIOA->MODER &= ~(3 << 12);
    GPIOA->PUPDR &= ~(3 << 12);
    GPIOA->PUPDR |= (1 << 12);
}

void configure_PB10()
{
    GPIOB->MODER &= ~(3 << 20);
    GPIOB->PUPDR &= ~(3 << 20);
    GPIOB->PUPDR |= (1 << 20);
}

//Outputs
void configure_PB9()
{
    GPIOB->MODER &= ~(3 << 18);
    GPIOB->MODER |= (1 << 18);
}

void configure_C13()
{
    GPIOC->MODER &= ~(3 << 26);
    GPIOC->MODER |= (1 << 26);
}

void configure_C14()
{
    GPIOC->MODER &= ~(3 << 26);
    GPIOC->MODER |= (1 << 26);
}