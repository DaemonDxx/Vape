#include "initFuction.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "misc.h"
#include "stm32f10x.h"


uint16_t ADCBuffer[50] = {'\0'};

void initNVIC() {
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 9;
	nvic.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvic);
	nvic.NVIC_IRQChannel = ADC1_2_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 10;
	nvic.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvic);

}



void initGPIO() {
	GPIO_InitTypeDef gpioADC;
	gpioADC.GPIO_Mode = GPIO_Mode_AIN;
	gpioADC.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &gpioADC);
	gpioADC.GPIO_Mode = GPIO_Mode_AIN;
	gpioADC.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &gpioADC);
}


void setup() {

	initRCC();
	initGPIO();
	initNVIC();
}
