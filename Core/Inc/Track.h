#ifndef __TRACK_H
#define __TRACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Utils.h"
#include "stm32l4xx_hal.h"
#include "DisplayPattern.h"
#include <stdbool.h>
#include <math.h>

/**
 * Subdivision enum
 * E_NOIRE : sequencer BPM = global BPM
 * E_CROCHE : sequencer BPM = global BPM x 2
 * E_D_CROCHE : sequencer BPM = global BPM x 4
 */
typedef enum
{
	E_NOIRE=4, E_CROCHE=2, E_D_CROCHE=1
} Subdiv;

typedef struct
{
	// Pattern Data
	uint16_t _pattern;
	uint8_t _nbSteps;
	uint8_t _currentStep;
	uint8_t _nbHits;
	Subdiv _sub;
	GPIO_PinState _TrigNextBeat;

	// TRIG I/O
	GPIO_PinPort _TRIGOUT;
	GPIO_PinPort _BPMOUT;

	// EDIT I/O
	GPIO_PinPort _ROTA;
	GPIO_PinPort _ROTB;

	// DISPLAY I/O
	GPIO_PinPort _CHASER;
	GPIO_PinPort _LATCH;
	GPIO_PinPort _CLK;
	GPIO_PinPort _PATTERN;
} Track;

void Track_initTrack(Track* track, Track_GPIOs GPIOs, int nbTrig);/*GPIO_TypeDef* TRIGOUT_Port, uint16_t TRIGOUT_Pin,
		uint16_t ROTA_Pin, GPIO_TypeDef* ROTB_Port, uint16_t ROTB_Pin, GPIO_TypeDef* CHASER_Port, uint16_t CHASER_Pin, GPIO_TypeDef* BPMOUT_Port, uint16_t BPMOUT_Pin);*/

/**
 * Checks if the sequencer outputs a trigger or not
 * @param seq the sequencer
 * @return pinState the value it outputs for a certain step
 */
void Track_TriggerNextBeat(Track* track);

/**
 * updates pattern when the number of steps or the number of hits has been modified
 * @param seq the sequencer to update
 * @param nbSteps the new number of steps
 * @param nbHits the new number of hits
 */
void Track_updatePattern(Track* track, uint8_t nbSteps, uint8_t nbHits);

/**
 * Updates the number of steps in the pattern according to the value of the pinState in parameter
 * @param i/o seq : the sequencer whose pattern is to be modified
 * @param i pinState : the pin controlling the behavior (pin for encoder's rotB)
 */
void Track_updateSteps(Track* track, uint16_t pin);

/**
 * Updates the number of hits in the pattern according to the value of the pinState in parameter
 * @param i/o seq : the sequencer whose pattern is to be modified
 * @param i pinState : the pin controlling the behavior (pin for encoder's rotB)
 */
void Track_updateHits(Track* track, uint16_t pin);

/**
 * Offsets the pattern of the sequencer seq according to the value of the pinState in parameter
 * @param i/o seq : the sequencer whose pattern is to be modified
 * @param i pinState : the pin controlling the behavior (pin for encoder's rotB)
 */
void Track_offsetPattern(Track* track, uint16_t pin);

/**
 * Updates sequencers BPM by modifying its subdivision according to the value of the pinState in parameter
 * @param i/o seq : the sequencer whose subdivision is to be modified
 * @param i pinState : the pin controlling the behavior (pin for encoder's rotB)
 */
void Track_updateSubdivision(Track* seq, uint16_t pin);

/**
 * Toggles pin according to the boolean in args, and increments current step
 * @param toggle : bool, toggles TRIGOUT if true, nothing if false
 */
void Track_TogglePin(Track* track, bool toggle);


#endif // __TRACK_H
