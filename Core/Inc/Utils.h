/*
 * Utils.h
 *
 *  Created on: Jan 30, 2024
 *      Author: fbonz
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "stm32l4xx_hal.h"
#include <stdbool.h>
#include <math.h>

typedef struct
{
	GPIO_TypeDef* Port;
	uint16_t Pin;
} GPIO_PinPort;

typedef struct
{
	GPIO_PinPort TRIGOUT;
	GPIO_PinPort ROTA;
	GPIO_PinPort ROTB;
	GPIO_PinPort CHASER;
	GPIO_PinPort BPMOUT;
	GPIO_PinPort LATCH;
	GPIO_PinPort CLK;
	GPIO_PinPort PATTERN;
} Track_GPIOs;

/**
 * Computes the value of the new pattern from the nb of hits and the nb of steps
 * Inspired by arduino code available at http://clsound.com/euclideansequenc.html
 * @param nbSteps the number of steps in the pattern
 * @param the number of hits in the pattern
 */
uint16_t Utils_computePattern(uint8_t nbSteps, uint8_t nbHits);

/**
 * Utility function to concatenate 2 binary patterns
 * @param i/o patternA : first part of the pattern, output of the concatenation
 * @param i patternB : second part of the pattern
 */
void Utils_concatenatePatterns(uint16_t* patternA, const uint8_t* patternB);

GPIO_PinState Utils_boolToPinState(bool value);

#endif /* INC_UTILS_H_ */
