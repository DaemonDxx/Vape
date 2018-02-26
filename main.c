#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x.h"
#include "misc.h"

#include "ADC.h"
#include "RCC.h"
#include "Interrupt.h"
#include "GPIO.h"
#include "Timer.h"
#include "Display.h"

#define MAX_ADC_VALUE 3730
#define ADC_K = 1
#define Ky = 10

extern uint16_t ADCBuffer[50];
extern float current;
extern uint8_t flagFire;

void initMillisFunction() {
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(89999);
}


int main(void)
{
	RCCInit();
	PeriphON();
	GPIOInit();
	NVICInit();
	initADC_DMA();
	TimerInit();
	EXTInit();
	initMillisFunction();
	//DisplayInit();

	__enable_irq();
	startUpdateCurrent();
	startUpdateVBat();
	//startUpdateCurrent();
    while(1)
    {
    	delay(5000);
    	delay(10000);
    }
}


