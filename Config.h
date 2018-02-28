#include "stdint.h"

//Количество измерений U на MOSFET до прерывания
#define BUFFER_ADC 50
//Коэффициент усиления операционника на MOSFET
#define K_AMPFILLER 10
//Сопротивление MOSFET в открытом состоянии
#define R_MOSFET 0.008
//Коэффициент усиления для делителя на батарее
#define K_VBAT_AMPFILLER 3.03
//Сколько в одной дискрете вольт
#define K_ADC_TO_VBAT 0.0008059
//Время в мс, через которое будет проверяться напряжение на батарее
#define PERIOD_UPDATE_VBAT 5000
//Частота ШИМ
#define F_PWM 5000
//Сопротивление всей цепи без MOSFET
#define RESISTANCE_CHAIN 0
//Кнопка UP
#define BUTTON_UP GPIO_Pin_10
//Кнопка FIRE
#define BUTTON_FIRE GPIO_Pin_2
//Кнопка DOWN
#define BUTTON_DOWN GPIO_Pin_9
//Время, в течении которого нужно нажать две кнопки, чтобы переключить режим
#define TIME_PRESS_BUTTON 400

//Коэффициенты для пид регулятора
#define PID_Kp 5.0

#define PID_Kd 1.0

#define PID_Ki 1.0


//Текущий ток в цепи
float current;
//Текущее напряжение на батарее
float Vbat;
//Сопротивление койла при 25 градусах
float resistanceCoil;
//Сопротивление койла на данный момент с учетом температуры
float resistanceCoilNow;
//Нажата ли кнопка FIRE
uint8_t flagFire;
////Режим работы. 1 - вериват, 0 - термоконтроль
uint8_t mode;
#define VERIWATT_MODE 1
#define TEMP_CONTROL_MODE 0

//Количество мс с момента начала программы
uint32_t millis;
//Предел температуры для термоконтроля
uint16_t maxTemp;
//Температура на данный момент
uint16_t nowTemp;
//Предел мощности для веривата
uint16_t power;
//Максимальная мощность, которую можно получить
uint16_t maxPower;

uint8_t flagUpdateCurrent;
