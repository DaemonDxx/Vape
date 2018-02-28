#include "Timer.h"
#include "stm32f10x_tim.h"
#include "Config.h"
#include "stm32f10x.h"

uint16_t getFrequency(uint16_t f) {
	return (uint16_t) 72000000/f;
}

void TimerInit(){
	TIM_TimeBaseInitTypeDef tim2;
	TIM_TimeBaseStructInit(&tim2);
	tim2.TIM_CounterMode = TIM_CounterMode_Up;
	tim2.TIM_ClockDivision = TIM_CKD_DIV2;
	tim2.TIM_Prescaler = 36000;
	tim2.TIM_Period = PERIOD_UPDATE_VBAT;
	TIM_TimeBaseInit(TIM3, &tim2);
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_TimeBaseInitTypeDef tim1;
	TIM_TimeBaseStructInit(&tim1);
	tim1.TIM_CounterMode = TIM_CounterMode_Up;
	tim1.TIM_Prescaler = getFrequency(F_PWM);
	tim1.TIM_Period = 65354;
	tim1.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &tim1);

	TIM_OCInitTypeDef pwm;
	pwm.TIM_OCMode = TIM_OCMode_PWM1;
	pwm.TIM_OCPolarity = TIM_OCPolarity_High;
	pwm.TIM_OutputState = TIM_OutputState_Enable;
	pwm.TIM_Pulse = 0;

	TIM_OC4Init(TIM2, &pwm);
	TIM_Cmd(TIM2, ENABLE);
}

void startUpdateVBat() {
	TIM_Cmd(TIM3, ENABLE);
}


void stopUpdateVbat() {
	TIM_Cmd(TIM3, DISABLE);
}

void setPWM(uint16_t pulse) {
	TIM2 -> CCR4 = pulse;
}
