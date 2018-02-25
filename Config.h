#define BUFFER_ADC 50
#define K_AMPFILLER 10
#define R_MOSFET 0.008
#define K_VBAT_AMPFILLER 3.03
#define K_ADC_TO_VBAT 0.0008059
#define PERIOD_UPDATE_VBAT 5000
#define F_PWM 5000
#define RESISTANCE_CHAIN 0

float current;
float Vbat;
float resistanceCoil;
float resistanceCoilNow;
