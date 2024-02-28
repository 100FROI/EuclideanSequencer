#ifndef __DISPLAYPATTERN_H
#define __DISPLAYPATTERN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"
#include "Utils.h"


#define MAX_SEQUENCER_STEPS 16
#define MIN_SEQUENCER_STEPS 1

void DisplayPattern(uint16_t pattern, uint8_t patternSize, GPIO_PinPort CLK, GPIO_PinPort PATTERN, GPIO_PinPort LATCH);

#ifdef __cplusplus
}
#endif

#endif /*__DISPLAYPATTERN_H*/
