#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "misc.h"

#include "ADC.h"
#include "RCC.h"
#include "Interrupt.h"
#include "GPIO.h"
#include "Timer.h"
#include "Display.h"

extern uint16_t ADCBuffer[50];
extern float current;
extern uint8_t flagFire;
extern uint16_t maxTemp;
extern uint16_t maxPower;

void initMillisFunction() {
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(89999);
}

void updateParam() {

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

	startUpdateVBat();

	maxTemp = 300;
	maxPower = 300;
    while(1)
    {
    	checkButtons();
    	if (1) {

    	}
    }
}


