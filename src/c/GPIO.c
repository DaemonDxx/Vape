#include "GPIO.h"
#include "Config.h"
#include "stm32f10x_gpio.h"
#include "Utils.h"
#include "Timer.h"
#include "ADC.h"

//����� ���������� ������� �� ������ UP ��� DOWN
uint32_t timePress;
extern uint8_t mode;

void GPIOInit() {
	//��� �1 ��� ������ ������� ���������� � MOSFET
	GPIO_InitTypeDef gpioADC;
	gpioADC.GPIO_Mode = GPIO_Mode_AIN;
	gpioADC.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &gpioADC);
	gpioADC.GPIO_Mode = GPIO_Mode_AIN;
	gpioADC.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &gpioADC);

	//��� �3 ��� ��������� ���
	GPIO_InitTypeDef pwm;
	pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	pwm.GPIO_Pin = GPIO_Pin_3;
	pwm.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &pwm);

	//��� FIRE, Button up, Button down -- ������, ����� ����� � ����� Config.h
	GPIO_InitTypeDef fire;
	fire.GPIO_Mode = GPIO_Mode_IPD;
	fire.GPIO_Pin = BUTTON_FIRE|BUTTON_UP|BUTTON_DOWN;
	fire.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &fire);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
}

//������������ ������ ������� - ���������
void toggleMode () {
	if (mode == TEMP_CONTROL_MODE) {
		mode = VERIWATT_MODE;
	} else {
		mode = TEMP_CONTROL_MODE;
	}
	delay(1000);
}

void updateResistanceCoil(){
	stopUpdateVbat();
	startUpdateCurrent();
}

//�������� � �������� ����� ��������� ����� ������� ������
void checkButtons() {

	//���� ������ ������� �����, �� �������� ������� paramUp, �������
	//���������� ������ �������� � ����������� �� ������
	if (GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) != 0) {
		timePress = getMillis();
		//���� TIME_PRESS_BUTTON �������, ����� ��������� ����� ������ ������
		//������ ��� ���, �.�. ���������� �� ������������ ������
		while (getMillis() - timePress < TIME_PRESS_BUTTON) {
			if (GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN) != 0) {
				toggleMode();
			}
		}
		uint8_t k;
		//���� ������ ������ ���������� ������ 500 ��� � ��������� ��������
		//������� ������������� �� ��������
		while (GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) != 0) {
			k = (uint8_t) 1 +(getMillis()-timePress)/1000;
			paramUp(k);
			delay(500);
		}
	}

	//������ ��� ���������� ���������. ���������� ���� ����
	if (GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN) != 0) {
			timePress = getMillis();
			uint8_t k;
			//����� ���������� ������������� �������
			while (getMillis() - timePress < TIME_PRESS_BUTTON) {
				if (GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) != 0) {
					updateResistanceCoil();
				}
			}
			while (GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN) != 0) {
				k = (uint8_t) 1 +(getMillis()-timePress)/1000;
				paramDown(k);
				delay(500);
			}
		}

	//��������� ������. ���� ������ FIRE �� ������, �� ��� �� ���������� ������
	if (GPIO_ReadInputDataBit(GPIOA, BUTTON_FIRE) == 0) {
			setPWM(0);
	}
}

