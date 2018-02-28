#include "RCC.h"
#include "stm32f10x_rcc.h"

void RCCInit() {
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	ErrorStatus status = RCC_WaitForHSEStartUp();

		if (status == SUCCESS) {
			RCC_HCLKConfig(RCC_SYSCLK_Div1);
			RCC_PCLK1Config(RCC_HCLK_Div2);
			RCC_PCLK2Config(RCC_HCLK_Div1);
			RCC_ADCCLKConfig(RCC_PCLK2_Div6);
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
			RCC_PLLCmd(ENABLE);

			while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET) {
			}

			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

			while(RCC_GetSYSCLKSource() != 0x08){}
		} else {
			while(1) {

			}
		}
}

void PeriphON() {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}
