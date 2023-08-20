/////////////////////////////////////////////////////////////
// 과제명: 
// 과제개요: 
// 사용한 하드웨어(기능): 
// 제출일: 
// 제출자 클래스: 
// 학번: 
// 이름: 
////////////////////////////////////////////////////////////
#include "stm32f4xx.h"
#include "GLCD.h"
#include "FRAM.h"

void _GPIO_Init(void);
void _EXTI_Init(void);
void DisplayInitScreen(void);
uint16_t KEY_Scan(void);

void BEEP(void);
void DelayMS(unsigned short wMS);
void DelayUS(unsigned short wUS);

int8_t ope_a, ope_b;

int main(void) {
        _GPIO_Init(); // GPIO (LED & SW) init
        _EXTI_Init(); // EXTI init
        LCD_Init(); // GLCD init
        Fram_Init();
        Fram_Status_Config();
        DelayMS(100);
        
        DisplayInitScreen(); // Display initial screen
        
        ope_a = 0; ope_b = 0;
        
        while (1) {
                switch (KEY_Scan()) {
                case 0xFE00 :
                        ope_a ^= (1UL << 1);
                        break;
                case 0xFD00:
                        ope_a ^= (1UL << 0);
                        break;
                }
        }
}

/* Initial screen for GLCD */
void DisplayInitScreen(void) {
        LCD_Clear(RGB_WHITE);
        LCD_SetFont(&Gulim8);
        LCD_SetTextColor(RGB_BLACK);
        LCD_DisplayText(0, 0, "Elevator");
}

/* GPIO Initialization */
void _GPIO_Init(void) {
      	// LED (GPIO G) Configuration
    	RCC->AHB1ENR	|=  0x00000040;	// RCC_AHB1ENR : GPIOG(bit#6) Enable							
	GPIOG->MODER 	|=  0x00005555;	// GPIOG 0~7 : Output mode (0b01)						
	GPIOG->OTYPER	&= ~0x00FF;	        // GPIOG 0~7 : Push-pull  (GP8~15:reset state)	
 	GPIOG->OSPEEDR 	|=  0x00005555;	// GPIOG 0~7 : Output speed 25MHZ Medium speed 
    
	// SW (GPIO H) Configuration
	RCC->AHB1ENR    |=  0x00000080;	        // RCC_AHB1ENR : GPIOH(bit#7) Enable							
	GPIOH->MODER 	&= ~0xFFFF0000;	// GPIOH 8~15 : Input mode (reset state)				
	GPIOH->PUPDR 	&= ~0xFFFF0000;	// GPIOH 8~15 : Floating input (No Pull-up, pull-down) :reset state

	// Buzzer (GPIO F) Configuration 
    	RCC->AHB1ENR	|=  0x00000020;         // RCC_AHB1ENR : GPIOF(bit#5) Enable							
	GPIOF->MODER 	|=  0x00040000;	// GPIOF 9 : Output mode (0b01)						
	GPIOF->OTYPER 	&= ~0x0200;	        // GPIOF 9 : Push-pull  	
 	GPIOF->OSPEEDR 	|=  0x00040000;	// GPIOF 9 : Output speed 25MHZ Medium speed 
}	

/* EXTI initialization  */
// GPIOI 5~9 : JOYSTICK, GPIOH 8~15 : SW
void _EXTI_Init(void) {
    RCC->AHB1ENR 	|= 0x00000080;	// RCC_AHB1ENR GPIOH Enable
    RCC->APB2ENR 	|= 0x00004000;	// Enable System Configuration Controller Clock	
    
    GPIOH->MODER 	&= ~0xFFFF0000;	// GPIOH PIN8~PIN15 Input mode (reset state)
            
    // Enable EXTI15 for GPIOH
    SYSCFG->EXTICR[3] |= 0x7000; // EXTICR4

    EXTI->FTSR |= 0x008000;		// EXTI : Falling Trigger Enable
    EXTI->IMR  |= 0x008000;		// EXTI IMR (Interrupt Enable)
		
    NVIC->ISER[1] |= (1 << 8);  // Enable EXTI10~EXTI15
                                                // NVIC->ISER[0] is for interrupt 0~31
                                                // NVIC->ISER[1] is for interrupt 32~63
                                                // vector table position 23 & 40 are for EXTI5~EXTI9 & EXTI10~EXTI15
}

/* EXTI10~15 interrupt handler */
void EXTI15_10_IRQHandler(void) {
        
}

void EXTI9_5_IRQHandler(void) {
        
}

uint8_t key_flag = 0;
uint16_t KEY_Scan(void)	// input key SW0 - SW7 
{ 
	uint16_t key;
	key = GPIOH->IDR & 0xFF00;	// any key pressed ?
	if(key == 0xFF00)		// if no key, check key off
	{  	if(key_flag == 0)
        		return key;
      		else
		{	DelayMS(10);
        		key_flag = 0;
        		return key;
        	}
    	}
  	else				// if key input, check continuous key
	{	if(key_flag != 0)	// if continuous key, treat as no key input
        		return 0xFF00;
      		else			// if new key,delay for debounce
		{	key_flag = 1;
			DelayMS(10);
 			return key;
        	}
	}
}

void BEEP(void)			/* beep for 30 ms */
{ 	
	GPIOF->ODR |=  0x0200;	// PF9 'H' Buzzer on
	DelayMS(30);		// Delay 30 ms
	GPIOF->ODR &= ~0x0200;	// PF9 'L' Buzzer off
}

void DelayMS(unsigned short wMS)
{
    register unsigned short i;
    for (i=0; i<wMS; i++)
        DelayUS(1000);         		// 1000us => 1ms
}

void DelayUS(unsigned short wUS)
{
    volatile int Dly = (int)wUS*17;
    for(; Dly; Dly--);
}
