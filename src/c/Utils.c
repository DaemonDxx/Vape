#include "Utils.h"
#include "stdint.h"
#include "Config.h"
#include "pid.h"

extern uint32_t millis;
extern uint8_t mode;
extern uint16_t maxTemp;
extern uint16_t nowTemp;
extern uint16_t power;
extern uint16_t maxPower;
extern float resistanceCoilNow;

//������� ������ ��� ����������� ���
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

//������������ ��...��
uint32_t getMillis() {
	return millis;
}

//���������� ��������� � ����������� �� ������
void paramUp(uint8_t k) {
  if (mode == TEMP_CONTROL_MODE) {
	  maxTemp += k;
  } else {
	  power += k;
	  if (power > maxPower) {
		  power = maxPower;
	  }
  }
}

//���������� ��������� � ����������� �� ������
void paramDown(uint8_t k) {
	if (mode == TEMP_CONTROL_MODE) {
		  maxTemp -= k;
	  } else {
		  power -= k;
	  }
}

//�������� ��� � �������. ������� � �� � ����� ���������
void delay(uint16_t time) {
	uint32_t startTime = getMillis();
	while (getMillis()- startTime < time){

	}
}

uint16_t getPWMCount() {
	double pwm = pid_Controller(maxTemp, nowTemp);
	return (uint16_t) pwm;
}

void PIDInit() {
	pid_Init(PID_Kp, PID_Ki, PID_Kd);
}

uint16_t ResistanceToTemp() {
	float t = 185.2*(resistanceCoilNow/(resistanceCoil))-165.2;
	return (uint16_t) t;
}

float TempToResistance(uint16_t temp){
	return resistanceCoil*(1+0.0054*(temp-20));
}
