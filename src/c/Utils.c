#include "Utils.h"
#include "stdint.h"
#include "Config.h"

extern uint32_t millis;
extern uint8_t mode;
extern uint16_t temp;
extern uint16_t power;
extern uint16_t maxPower;

//Обычный фильтр для результатов АЦП
uint16_t fuckFilter(uint16_t *mass, uint8_t lenght) {
	uint32_t sum = 0;
	uint8_t k = 0;

	for (uint8_t i = 0; i<lenght; i++) {
		if (*mass < 4000) {
			sum += *mass;
			mass++;
			k++;
		}
	}
	return sum/k;
}

//Ардуиновская за...па
uint32_t getMillis() {
	return millis;
}

//Увеличение параметра в зависимости от режима
void paramUp(uint8_t k) {
  if (mode == TEMP_CONTROL_MODE) {
	  temp += k;
  } else {
	  power += k;
	  if (power > maxPower) {
		  power = maxPower;
	  }
  }
}

//Уменьшение параметра в зависимости от режима
void paramDown(uint8_t k) {
	if (mode == TEMP_CONTROL_MODE) {
		  temp -= k;
	  } else {
		  power -= k;
	  }
}

//Задержка как в ардуино. Считает в мс в своем измерении
void delay(uint16_t time) {
	uint32_t startTime = getMillis();
	while (getMillis()- startTime < time){

	}
}
