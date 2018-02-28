#include "ADC.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "Config.h"

uint16_t ADCBuffer[BUFFER_ADC];

void initADC_DMA() {

	DMA_InitTypeDef dma;
	dma.DMA_BufferSize = BUFFER_ADC;
	dma.DMA_DIR = DMA_DIR_PeripheralSRC;
	dma.DMA_M2M = DMA_M2M_Disable;
	dma.DMA_MemoryBaseAddr = (uint32_t)ADCBuffer;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_PeripheralBaseAddr = (uint32_t)&ADC1 -> DR;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_Priority = DMA_Priority_High;

	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	DMA_Init(DMA1_Channel1, &dma);
	DMA_Cmd(DMA1_Channel1, ENABLE);


	ADC_InitTypeDef adc;
	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc.ADC_Mode = ADC_Mode_Independent;
	adc.ADC_NbrOfChannel = 1;
	adc.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &adc);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_71Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
    ADC_DMACmd(ADC1, ENABLE);

    ADC_InitTypeDef adc2;
    adc2.ADC_ContinuousConvMode = DISABLE;
    adc2.ADC_DataAlign = ADC_DataAlign_Right;
    adc2.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
    adc2.ADC_Mode = ADC_Mode_Independent;
    adc2.ADC_NbrOfChannel = 1;
    adc2.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC2, &adc2);
    ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
    ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE);
    ADC_ResetCalibration(ADC2);
    while(ADC_GetCalibrationStatus(ADC2));
    ADC_StartCalibration(ADC2);
    while (ADC_GetCalibrationStatus(ADC2));
    ADC_Cmd(ADC2, ENABLE);
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);

}

void startUpdateCurrent(){
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


void stopUpdateCurrnet() {
	ADC_SoftwareStartConvCmd(ADC1, DISABLE);
	ADC_Cmd(ADC1, DISABLE);
}
