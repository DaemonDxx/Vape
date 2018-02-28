#include "GPIO.h"
#include "Config.h"
#include "stm32f10x_gpio.h"
#include "Utils.h"
#include "Timer.h"
#include "ADC.h"

//Время последнего нажатия на кнопку UP или DOWN
uint32_t timePress;
extern uint8_t mode;

void GPIOInit() {
	//Пин А1 для снятие падения напряжения с MOSFET
	GPIO_InitTypeDef gpioADC;
	gpioADC.GPIO_Mode = GPIO_Mode_AIN;
	gpioADC.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA, &gpioADC);
	gpioADC.GPIO_Mode = GPIO_Mode_AIN;
	gpioADC.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &gpioADC);

	//Пин А3 для генерации ШИМ
	GPIO_InitTypeDef pwm;
	pwm.GPIO_Mode = GPIO_Mode_AF_PP;
	pwm.GPIO_Pin = GPIO_Pin_3;
	pwm.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &pwm);

	//Пин FIRE, Button up, Button down -- кнопки, выбор пинов в файле Config.h
	GPIO_InitTypeDef fire;
	fire.GPIO_Mode = GPIO_Mode_IPD;
	fire.GPIO_Pin = BUTTON_FIRE|BUTTON_UP|BUTTON_DOWN;
	fire.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &fire);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
}

//Переключение режима вериват - веривольт
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

//Проверка в основном цикле программы какие клавиши нажаты
void checkButtons() {

	//Если нажата клавиша вверх, то вызываем функцию paramUp, которая
	//увеличиает нужный параметр в зависимости от режима
	if (GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) != 0) {
		timePress = getMillis();
		//Ждем TIME_PRESS_BUTTON времени, чтобы проверить будет нажата вторая
		//кнопка или нет, т.е. происходит ли переключение режима
		while (getMillis() - timePress < TIME_PRESS_BUTTON) {
			if (GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN) != 0) {
				toggleMode();
			}
		}
		uint8_t k;
		//Пока нажата кнопка прибавляем каждые 500 мкс к параметру значение
		//которое увеличивается со временем
		while (GPIO_ReadInputDataBit(GPIOA, BUTTON_UP) != 0) {
			k = (uint8_t) 1 +(getMillis()-timePress)/1000;
			paramUp(k);
			delay(500);
		}
	}

	//Кнопка для уменьшения параметра. Аналогично коду выше
	if (GPIO_ReadInputDataBit(GPIOA, BUTTON_DOWN) != 0) {
			timePress = getMillis();
			uint8_t k;
			//Режим обновления сопротивления спирали
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

	//Небольшая защита. Если кнопка FIRE не нажата, то ШИМ не генерирует ничего
	if (GPIO_ReadInputDataBit(GPIOA, BUTTON_FIRE) == 0) {
			setPWM(0);
	}
}

