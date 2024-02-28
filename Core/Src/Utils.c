/*
 * Utils.c
 *
 *  Created on: Jan 30, 2024
 *      Author: fbonz
 */

#include "Utils.h"



void Utils_concatenatePatterns(uint16_t* patternA, const uint8_t* patternB)
{
	*patternA = (*patternA << ((int)floor(log2((double)(*patternB)))+1)) | *patternB;
}

uint16_t Utils_computePattern(uint8_t nbSteps, uint8_t nbHits)
{
	if (nbHits > nbSteps)
		nbHits = nbSteps;

	//Each iteration is a process of pairing strings X and Y and the remainder from the pairings
	//X will hold the "dominant" pair (the pair that there are more of)
	uint8_t A_pattern = 1;
	uint8_t A_length = nbHits;
	uint8_t B_pattern = 0;
	uint8_t B_length = nbSteps - nbHits;

	do
	{
		// New dominant pattern
		uint8_t temp_pattern = B_pattern;

		//Check which is the dominant pair
		if (A_length >= B_length)
		{
			//Set the new number of pairs for X and Y
			uint8_t A_length_temp = A_length;
			A_length = B_length;
			B_length = A_length_temp - B_length;

			//The previous dominant pair becomes the new non dominant pair
			B_pattern = A_pattern;
		}
		else
		{
			B_length -= A_length;
		}
		Utils_concatenatePatterns((uint16_t*)&A_pattern, &temp_pattern);
	} while (A_length > 1 && B_length > 1);//iterate as long as the non dominant pair can be paired (if there is 1 Y left, all we can do is pair it with however many Xs are left, so we're done)

	//By this point, we have strings X and Y formed through a series of pairings of the initial strings "1" and "0"
	//X is the final dominant pair and Y is the second to last dominant pair
	uint16_t pattern = 0;
	for (int i = 1; i <= A_length; i++)
		Utils_concatenatePatterns(&pattern, &A_pattern);
	for (int i = 1; i <= B_length; i++)
		Utils_concatenatePatterns(&pattern, &B_pattern);
	return pattern;
}

GPIO_PinState Utils_boolToPinState(bool value)
{
	return value ? GPIO_PIN_SET : GPIO_PIN_RESET;
}


