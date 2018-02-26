#include "GPIO.h"
#include "stm32f10x_gpio.h"

void GPIOInit() {
	GPIO_InitTypeDef gpioADC;
	gpioADC.GPIO_Mode = GPIO_Mode_AIN;
	gpioADC.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &gpioADC);
	gpioADC.GPIO_Mode = GPIO_Mode_AIN;
	gpioADC.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &gpioADC);

	GPIO_InitTypeDef pwm;
	pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	pwm.GPIO_Pin = GPIO_Pin_3;
	pwm.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &pwm);

	GPIO_InitTypeDef fire;
	fire.GPIO_Mode = GPIO_Mode_IPD;
	fire.GPIO_Pin = GPIO_Pin_2;
	fire.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &fire);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
}


