#include "CVSequencer.h"

void CVSeq_initCVSequencer(CVSequencer* cvSeq, GPIO_PinPort TRIG, ADC_HandleTypeDef* CVIn, DAC_HandleTypeDef* CVOut,
		 uint8_t dacChannel, GPIO_PinPort CHANGEFREQ, GPIO_PinPort DISPLAY)
{
	cvSeq->_adcValues[0] = 0;
	cvSeq->_adcValues[1] = 0;
	cvSeq->_outValue = 0;
	cvSeq->_freq = 0;
	cvSeq->_hadc = CVIn;
	cvSeq->_currentStep = 0;
	cvSeq->_hdac = CVOut;
	cvSeq->_dacChannel = dacChannel;
	cvSeq->_DISPLAY = DISPLAY;
	cvSeq->_CHANGEFREQ = CHANGEFREQ;
	cvSeq->_TRIG = TRIG;
}

void CVSeq_updateCVValue(CVSequencer* cvSeq)
{
	HAL_ADC_Start_DMA(cvSeq->_hadc, (uint32_t*)cvSeq->_adcValues, 2);

	if(cvSeq->_freq != 0 && cvSeq->_currentStep == cvSeq->_freq)
	{
		cvSeq->_outValue = cvSeq->_adcValues[1];
		cvSeq->_currentStep = 1;
	} else
	{
		cvSeq->_outValue = cvSeq->_adcValues[0];
		++cvSeq->_currentStep;
	}
	HAL_DAC_Start(cvSeq->_hdac, DAC_CHANNEL_1);
	HAL_DAC_SetValue(cvSeq->_hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, cvSeq->_outValue);
}

void CVSeq_changeFrequency(CVSequencer* cvSeq)
{
	switch(cvSeq->_freq)
	{
	case 0 || 1 || 2 || 3:
		++cvSeq->_freq;
		CVSeq_incrementDisplay(cvSeq);
		break;
	default:
		CVSeq_resetDisplay(cvSeq);
		cvSeq->_freq = 0;
	}
}

void CVSeq_incrementDisplay(CVSequencer* cvSeq)
{
	HAL_GPIO_WritePin(cvSeq->_DISPLAY.Port, cvSeq->_DISPLAY.Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(cvSeq->_DISPLAY.Port, cvSeq->_DISPLAY.Pin, GPIO_PIN_RESET);
}

void CVSeq_resetDisplay(CVSequencer* cvSeq)
{
	for(int i=0; i < 7; ++i)
	{
		HAL_GPIO_WritePin(cvSeq->_DISPLAY.Port, cvSeq->_DISPLAY.Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(cvSeq->_DISPLAY.Port, cvSeq->_DISPLAY.Pin, GPIO_PIN_RESET);
	}
}
