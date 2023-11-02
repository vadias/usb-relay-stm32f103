#include "stm32f103xb.h"
#include "16S2.h"
#include "main.h"

void LCDInit(void);
void WriteByte(uint8_t b, _Bool cd);
void PinSet(GPIO_TypeDef *GPIOx, uint8_t pin);
void PinReset (GPIO_TypeDef *GPIOx, uint8_t pin);
uint8_t LcdRead(void);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
void WriteCmd(uint8_t b) { WriteByte (b,0); }
void WriteData(uint8_t b) { WriteByte(b,1); }
void LcdGoTo(uint8_t x, uint8_t y);
void LcdWriteString(uint8_t * stringToWrite);

#define APB1CLK 24000000

#define LCD_PORT GPIOB
#define LCD_A0	7
#define LCD_RW	6
#define LCD_E		5
#define LCD_DB4	12
#define LCD_DB5	13
#define LCD_DB6	14
#define LCD_DB7	15

#define E1 (PinSet(LCD_PORT, LCD_E); delay_us(100);)


void LCDInit(void)
{
	/* Set GPIO */
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	LCD_PORT->CRL &= ~(0xFFFFFFFF);
	LCD_PORT->CRH &= ~(0xFFFFFFFF);
	/* Pins output pushpull 10Mhz*/
	LCD_PORT->CRL |= ( 1 << (LCD_A0*4)) | ( 1 << (LCD_RW*4)) | ( 1 << (LCD_E*4));
	/* Pins  output pushpull 10Mhz*/
	LCD_PORT->CRH |= (1 << (LCD_DB4-8)*4) | (1 << (LCD_DB5-8)*4) | (1 << (LCD_DB6-8)*4) | (1 << (LCD_DB7-8)*4);
	
	/* Lcd Pins set to 0 */
	LCD_PORT->ODR &= ~(1<<LCD_A0 | 1<<LCD_RW | 1<<LCD_E | 1<<LCD_DB4 | 1<<LCD_DB5 | 1<<LCD_DB6 | 1<<LCD_DB7);
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	// Clocking Tim2
	TIM2->PSC = APB1CLK/1000000;				// Prescaler	period 1us
	//TIM2->CR1 |= TIM_CR1_OPM;          	// One pulse mode
	TIM2->DIER |= TIM_DIER_UIE;
	
	/* Set LCD */
	PinReset(LCD_PORT, LCD_E);
	delay_ms(50);
	PinReset(LCD_PORT, LCD_RW);
	PinReset(LCD_PORT, LCD_A0);
	LCD_PORT->ODR &= ~(1<<LCD_DB4 | 1<<LCD_DB5 | 1<<LCD_DB6| 1<<LCD_DB7);
	LCD_PORT->ODR |= ((0x03 & 0x0F)<<LCD_DB4);
	delay_ms(1);
	PinSet(LCD_PORT, LCD_E); 		delay_us(100);
	PinReset(LCD_PORT, LCD_E);	delay_us(100);
	PinSet(LCD_PORT, LCD_E); 		delay_us(100);
	PinReset(LCD_PORT, LCD_E);	delay_us(100);
	PinSet(LCD_PORT, LCD_E); 		delay_us(100); 
	PinReset(LCD_PORT, LCD_E);	delay_us(100);
	PinSet(LCD_PORT, LCD_E); 		delay_us(100);
	PinReset(LCD_PORT, LCD_E);	delay_us(100);
	/* Set interface 4bit */
	LCD_PORT->ODR &= ~(1<<LCD_DB4 | 1<<LCD_DB5 | 1<<LCD_DB6| 1<<LCD_DB7);
	LCD_PORT->ODR |= ((0x02 & 0x0F)<<LCD_DB4);
	PinSet(LCD_PORT, LCD_E); 
	delay_us(100);
	PinReset(LCD_PORT, LCD_E);
	delay_us(100);
	
	WriteCmd(HD44780_FLAG_DISPLAY_ACTIVE);
	WriteCmd(HD44780_INSTRUCTION_CLEAR);
	WriteCmd(HD44780_LCD_CURSOR_OFF);
}

void LcdGoTo(uint8_t x, uint8_t y)
{
	if (y==0){
		WriteCmd(HD44780_INSTRUCTION_DDRAM_ADDRESS | x);
	}
	if (y==1){
		WriteCmd(HD44780_INSTRUCTION_DDRAM_ADDRESS | 0x40 | x);
	}
}

void LcdWriteString(uint8_t * stringToWrite)
{
	while(*stringToWrite)
  WriteData(*stringToWrite++);
}

void WriteByte(uint8_t b,_Bool cd) 
{	
	/* wait lcd is ready */
	while (LcdRead() & HD44780_FLAG_BUSY);
	/* Set data pins is out mode */
	LCD_PORT->CRH &= ~((15<<(LCD_DB4-8)*4) | (15<<(LCD_DB5-8)*4) | (15<<(LCD_DB6-8)*4) | (15<<(LCD_DB7-8)*4));
	LCD_PORT->CRH	|= (1 << (LCD_DB4-8)*4) | (1 << (LCD_DB5-8)*4) | (1 << (LCD_DB6-8)*4) | (1 << (LCD_DB7-8)*4);
		
	PinReset(LCD_PORT, LCD_RW);	
		
	if (cd == 1) {
			PinSet(LCD_PORT, LCD_A0);
	} else
	PinReset(LCD_PORT, LCD_A0);
	delay_us(100);
	
	LCD_PORT->ODR &= ~(1<<LCD_DB4 | 1<<LCD_DB5 | 1<<LCD_DB6| 1<<LCD_DB7);
	LCD_PORT->ODR |= (b>>4)<<LCD_DB4;
	PinSet(LCD_PORT, LCD_E);
	delay_us(100);
	PinReset(LCD_PORT, LCD_E);
	delay_us(100);
	
	LCD_PORT->ODR &= ~(1<<LCD_DB4 | 1<<LCD_DB5 | 1<<LCD_DB6| 1<<LCD_DB7);
	LCD_PORT->ODR |= (b & 0x0F)<<LCD_DB4;
	PinSet(LCD_PORT, LCD_E);	
	delay_us(100);
	PinReset(LCD_PORT, LCD_E);
	delay_us(100);
}

void PinSet(GPIO_TypeDef *GPIOx, uint8_t pin)
{
	GPIOx->BSRR |= ( 1 << pin );
}

void PinReset(GPIO_TypeDef *GPIOx, uint8_t pin)
{
	GPIOx->BSRR |= ( 1 << (pin+16) );
}

uint8_t LcdRead(void)
{
	uint8_t d;
	//Pin DB7 set as input
	LCD_PORT->CRH &= ~((15<<(LCD_DB4-8)*4) | (15<<(LCD_DB5-8)*4) | (15<<(LCD_DB6-8)*4) | (15<<(LCD_DB7-8)*4));
	LCD_PORT->CRH |= ( (0x8 << (4*(LCD_DB4-8))) | (0x8 << (4*(LCD_DB5-8))) | (0x8 << (4*(LCD_DB6-8))) | (0x8 << (4*(LCD_DB7-8))) );
	LCD_PORT->ODR &= ~(1<<LCD_DB4 | 1<<LCD_DB5 | 1<<LCD_DB6| 1<<LCD_DB7);
	/*Read redy flag */
	PinSet(LCD_PORT, LCD_RW);
	PinReset(LCD_PORT, LCD_A0);
	delay_ms(1);
	PinSet(LCD_PORT, LCD_E);
	delay_ms(1);
	d |= ((LCD_PORT->IDR)>>LCD_DB4)<<4;
	PinReset(LCD_PORT, LCD_E);	
	delay_ms(1);
	PinSet(LCD_PORT, LCD_E);	delay_ms(1);
	d &= ((LCD_PORT->IDR)>>LCD_DB4) & 0x0F;
	PinReset(LCD_PORT, LCD_E);	delay_ms(1);
	return d;
}

void delay_ms(uint32_t ms)
{
	uint32_t tmp;	
	tmp = HAL_GetTick();
	while((tmp + ms) > HAL_GetTick()) {};	
}

void delay_us (uint32_t us)
{
	TIM2->CR1 |= TIM_CR1_ARPE;								// Auto reload enable
	TIM2->ARR = us;
	TIM2->CNT = 0;														// Counter reset
	TIM2->CR1 |= TIM_CR1_CEN;									// Tim - On// Auto reload value
	while(!(TIM2->SR & TIM_SR_UIF)); 					//дождаться конца задержки
	TIM2->CR1 &= ~TIM_CR1_CEN;	
	TIM2->SR &= ~TIM_SR_UIF;	      					//сбросить флаг
}
