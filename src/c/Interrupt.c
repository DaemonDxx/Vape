#include "misc.h"
#include "stm32f10x.h"
#include "Interrupt.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"
#include "Config.h"
#include "ADC.h"
#include "stm32f10x_gpio.h"
#include "Timer.h"
#include "stdint.h"

extern uint16_t ADCBuffer[50];
extern float current;
extern float Vbat;
extern float resistanceCoilNow;
extern float resistanceCoil;
extern uint32_t millis;
extern uint8_t flagFire;
extern uint8_t flagUpdateCurrent;
extern uint16_t maxPower;
extern uint16_t nowTemp;
extern uint16_t maxTemp;

void NVICInit() {
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
	NVIC_InitTypeDef exti;
	exti.NVIC_IRQChannel = EXTI2_IRQn;
	exti.NVIC_IRQChannelCmd = ENABLE;
	exti.NVIC_IRQChannelPreemptionPriority = 1;
	exti.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&exti);
}

void EXTInit() {
	EXTI_InitTypeDef exti;
	exti.EXTI_Line = EXTI_Line2;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
}

void DMA1_Channel1_IRQHandler(void) {
	stopUpdateCurrnet();
	float u;
	u = fuckFilter(&ADCBuffer, BUFFER_ADC)*3.3/(4095*K_AMPFILLER);
	current = u/R_MOSFET;
	resistanceCoilNow = Vbat/current - RESISTANCE_CHAIN;
	maxPower = (uint16_t) current*current*resistanceCoilNow;
	nowTemp = ResistanceToTemp();
	if (flagFire == 1) {
		///Код получения значения для ШИМ
		uint16_t pwmCount = getPWMCount(nowTemp, maxTemp);
		setPWM(pwmCount);
		startUpdateCurrent();
	} else {
		///Подсчет значения сопротивления и максимальной мощности
		setPWM(0);
		if (flagUpdateCurrent != 1) {
			resistanceCoil = resistanceCoilNow;
		}
		startUpdateVBat();
	}
	DMA_ClearITPendingBit(DMA1_IT_TC1);
}

void ADC1_2_IRQHandler(void){
	if(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC)) {
		Vbat = ADC_GetConversionValue(ADC2)*K_VBAT_AMPFILLER*K_ADC_TO_VBAT;
		ADC_ClearFlag(ADC2, ADC_IT_EOC);
	}
}

void EXTI2_IRQHandler(void) {

    if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) != 0) {
        	startUpdateCurrent();
        	stopUpdateVbat();
        	flagFire = 1;
        } else {
        	stopUpdateCurrnet();
        	startUpdateVBat();
        	flagFire = 0;
        }

        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}

void SysTick_Handler(void)
{
  millis++;
}
