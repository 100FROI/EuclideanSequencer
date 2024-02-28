#include "DisplayPattern.h"

void DisplayPattern(uint16_t pattern, uint8_t patternSize, GPIO_PinPort CLK, GPIO_PinPort PATTERN, GPIO_PinPort LATCH)
{
	//uint32_t patternAndSize = 0;
	GPIO_PinState pinState = GPIO_PIN_RESET;
	HAL_GPIO_WritePin(PATTERN.Port, PATTERN.Pin, pinState);
	HAL_GPIO_WritePin(LATCH.Port, LATCH.Pin, GPIO_PIN_RESET);
	for(int i = 0; i < MAX_SEQUENCER_STEPS; ++i)
	{
		HAL_GPIO_WritePin(CLK.Port, CLK.Pin, GPIO_PIN_RESET);
		pinState = Utils_boolToPinState(i<patternSize);
		HAL_GPIO_WritePin(PATTERN.Port, PATTERN.Pin, pinState); // SER Input SIZE
		HAL_GPIO_WritePin(CLK.Port, CLK.Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(CLK.Port, CLK.Pin, GPIO_PIN_RESET);
		pinState = Utils_boolToPinState((pattern & (1 << (patternSize - (i+1)))) > 0);
		HAL_GPIO_WritePin(PATTERN.Port, PATTERN.Pin, pinState); // SER Input PATTERN
		HAL_GPIO_WritePin(CLK.Port, CLK.Pin, GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(LATCH.Port, LATCH.Pin, GPIO_PIN_SET);
}
