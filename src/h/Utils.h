#include "stdint.h"

uint16_t fuckFilter(uint16_t *mass, uint8_t lenght);
uint32_t getMillis();
void paramUp(uint8_t k);
void paramDown(uint8_t k);
void delay(uint16_t time);
uint16_t getPWMCount(uint16_t tempNow, uint16_t tempMax);
uint16_t ResistanceToTemp(float resistance);
float TempToResistance(uint16_t temp);
void PIDInit();
