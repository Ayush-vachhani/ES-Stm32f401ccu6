#include "stm32f4xx.h"
#include "general.h"
#include "interrupts_conf.h"

//Interrupt for PA0 button
void EXTI0_IRQHandler(void) {
    if (EXTI->PR & (1 << 0)) {        // Check if the interrupt flag for PA0 is set ( == 0 since active low )
        GPIOB->ODR ^= (1 << 9);
        GPIOC->ODR ^= (1 << 13);
        GPIOC->ODR ^= (1 << 14);      // Toggle the LED on PC13
    }
    EXTI->PR |= (1 << 0);         // Clear the interrupt flag by writing a '1'
}

//Interrupt for PA6 button
void EXTI9_5_IRQHandler(void)
{
    EXTI->PR & (1U << 6);
}

//Interrupt for PB10 button
void EXTI15_10_IRQHandler(void)
{
    EXTI->PR & (1U << 10);
}

//Interrupt for ADC
void ADC_IRQHandler(void)
{
    if(ADC1->SR & (1U << 1))
    {
        int adcData = ADC1->DR;
    }
}

//Interrupt for Timer
void SysTick_Handler(void)
{
    GPIOC->ODR ^= (1U << 14);
}

int main(void) {
    RCC->AHB1ENR = 15;
    RCC->APB2ENR |= (1U << 8);   //Enable ADC clock
    RCC->APB2ENR |= (1U << 14);   //Enable serial clock for interrupts

    SysTick->LOAD = 16000000 - 1; //Load the timer with number of cycles
    SysTick->VAL = 0; //Clear current value
    SysTick->CTRL = 7; //Enables everything ( bits 0, 1, 2 )


    //Configuring input pins
    configure_PA0();
    configure_PA6();
    configure_PB10();

    //Configuring output pins
    configure_PB9();
    configure_C13();
    configure_C14();

    configure_Interrupt_PA0();
    configure_Interrupt_PA6();
    configure_Interrupt_B10();

    GPIOA->MODER |= (3U << 0); //Set PA0 to analog mode ( 11 )
    GPIOA->MODER |= (3U << 2); //Set PA1 to analog mode ( 11 )

    //Set CR1 & CR2 to 0
    ADC1->CR1 = 0;
    ADC1->CR2 = 0;

    ADC1->CR2 |= (1U << 1); // Enable continous conversion mode

    ADC1->SQR1 = 0; //Set conversion length to one ( Potentiometer )
    ADC1->SQR3 = 0; // Choose ADC channel TODO : Potentiometer = 0
    ADC1->SQR3 = 1; // Choose ADC channel TODO : LDR = 1

    ADC1->CR2 |= 1; //Enable ADC by setting the ADON bit in CR2 (bit 0)

    while((ADC1->CR2 & 1) == 0) {} //Wait until the ADC is ready (ADON bit is set)

    ADC1->CR2 |= (1 << 30);//Start the conversion by setting the SWSTART bit (bit 30) in CR2

    // const int a0_pressed =  (GPIOA->IDR & (1U << 0)) == 0;
    // const int a6_pressed =  (GPIOA->IDR & (1U << 6)) == 0;
    // const int b10_pressed = (GPIOB->IDR & (1U << 10)) == 0;

    NVIC_EnableIRQ(EXTI0_IRQn);     //A0 Interrupt
    NVIC_SetPriority(EXTI0_IRQn, 0);
    NVIC_EnableIRQ(EXTI9_5_IRQn);   //A6 Interrupt
    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI15_10_IRQn); //B10 Interrupt
    NVIC_SetPriority(EXTI0_IRQn, 2);
    NVIC_EnableIRQ(ADC_IRQn);       //ADC Interrupt

    while (1) {

    }
}
