#include "stdint.h"

//���������� ��������� U �� MOSFET �� ����������
#define BUFFER_ADC 50
//����������� �������� ������������� �� MOSFET
#define K_AMPFILLER 10
//������������� MOSFET � �������� ���������
#define R_MOSFET 0.008
//����������� �������� ��� �������� �� �������
#define K_VBAT_AMPFILLER 3.03
//������� � ����� �������� �����
#define K_ADC_TO_VBAT 0.0008059
//����� � ��, ����� ������� ����� ����������� ���������� �� �������
#define PERIOD_UPDATE_VBAT 5000
//������� ���
#define F_PWM 5000
//������������� ���� ���� ��� MOSFET
#define RESISTANCE_CHAIN 0
//������ UP
#define BUTTON_UP GPIO_Pin_10
//������ FIRE
#define BUTTON_FIRE GPIO_Pin_2
//������ DOWN
#define BUTTON_DOWN GPIO_Pin_9
//�����, � ������� �������� ����� ������ ��� ������, ����� ����������� �����
#define TIME_PRESS_BUTTON 400

//������������ ��� ��� ����������
#define PID_Kp 5.0

#define PID_Kd 1.0

#define PID_Ki 1.0


//������� ��� � ����
float current;
//������� ���������� �� �������
float Vbat;
//������������� ����� ��� 25 ��������
float resistanceCoil;
//������������� ����� �� ������ ������ � ������ �����������
float resistanceCoilNow;
//������ �� ������ FIRE
uint8_t flagFire;
////����� ������. 1 - �������, 0 - �������������
uint8_t mode;
#define VERIWATT_MODE 1
#define TEMP_CONTROL_MODE 0

//���������� �� � ������� ������ ���������
uint32_t millis;
//������ ����������� ��� �������������
uint16_t maxTemp;
//����������� �� ������ ������
uint16_t nowTemp;
//������ �������� ��� ��������
uint16_t power;
//������������ ��������, ������� ����� ��������
uint16_t maxPower;

uint8_t flagUpdateCurrent;
