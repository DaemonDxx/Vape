#include "Utils.h"
#include "stdint.h"

extern uint32_t millis;

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

uint32_t getMillis() {
	return millis;
}

void paramUp(uint8_t k) {

}

void delay(uint16_t time) {
	uint32_t startTime = getMillis();
	while (getMillis()- startTime < time){

	}
}
