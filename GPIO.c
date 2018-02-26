#include "GPIO.h"
#include "Config.h"
#include "stm32f10x_gpio.h"
#include "Utils.h"

uint32_t timePress;

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
	fire.GPIO_Pin = BUTTON_FIRE|BUTTON_UP;
	fire.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &fire);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
}

void checkButtons() {
	if (GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) != 0) {
		timePress = getMillis();
		uint8_t k;
		while (GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) != 0) {
			k = (uint8_t) 1 +(getMillis()-timePress)/1000;
			paramUp(k);
		}
	}
}

