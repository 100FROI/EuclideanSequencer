#ifndef __CVSEQUENCER_H
#define __CVSEQUENCER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include "stm32l4xx_hal.h"
#include "Utils.h"

/**
 * The CV Sequencer struct
 */
typedef struct
{
	uint8_t _freq;
	ADC_HandleTypeDef* _hadc;
	DAC_HandleTypeDef* _hdac;
	uint8_t _dacChannel;
	uint8_t _currentStep;
	volatile uint16_t _adcValues[2];
	volatile uint16_t _outValue;
	GPIO_PinPort _TRIG;
	GPIO_PinPort _DISPLAY;
	GPIO_PinPort _CHANGEFREQ;
} CVSequencer;

/**
 * Initializes a CV sequencer with values in parameter
 * @param cvSeq the cv sequencer to initialize
 * @param trigPin the trigger pin
 * @param freq the frequency of occurence of CV2
 * @param CV1 the voltage value out for hits 1
 * @param CV2 the voltage value out for hits 2
 * @return void
 */
void CVSeq_initCVSequencer(CVSequencer* cvSeq, GPIO_PinPort TRIG, ADC_HandleTypeDef* CVIn, DAC_HandleTypeDef* CVOut,
		uint8_t dacChannel, GPIO_PinPort CHANGEFREQ, GPIO_PinPort DISPLAY);
void CVSeq_updateCVValue(CVSequencer* cvSeq);
void CVSeq_changeFrequency(CVSequencer* cvSeq);
void CVSeq_incrementDisplay(CVSequencer* cvSeq);
void CVSeq_resetDisplay(CVSequencer* cvSeq);

#ifdef __cplusplus
}
#endif

#endif  /*__CVSEQUENCER_H*/
