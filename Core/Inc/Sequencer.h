#ifndef __SEQUENCER_H
#define __SEQUENCER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include "stm32l4xx_hal.h"
#include "Track.h"
#include <stdbool.h>

#define NBTRACKS 3

typedef enum
{
	E_STEPS=0, E_HITS=1, E_SUB=2, E_OFFSET=3
} Mode;

typedef struct
{
	Track _tracks[NBTRACKS]; // Array of tracks
	bool _SeqTrig[NBTRACKS];
	GPIO_PinState _BPMTrig;
	uint8_t _step;

	// I/O
	GPIO_PinPort _SWITCH; // Pin of the Change Edition Mode switch
	GPIO_PinPort _BPM_ROTA; // Pin of ROTA of the BPM encoder
	GPIO_PinPort _BPM_ROTB; // ROTB of the BPM encoder
	uint16_t _BPM; // BPM Value
	bool _BPM_Update;
	GPIO_PinPort _BPMOUT; // BPMOUT
	GPIO_PinPort _BPMDisplay; // BPMDisplay pin
	GPIO_PinPort _MODEDisplay; // MODEDisplay pin

	// Timer
	TIM_HandleTypeDef* _htim; // Pointer to the global BPM Timer

	Mode _mode; // Current Edition Mode

	bool _computed; // Knows if the main loop has computed the next values or no (avoids computing values endlessly, only once each bpm tick
} Sequencer;

/**
 * Initializes sequencer seq with values in parameters
 * @param seq : the sequencer to initialize
 * @param pattern : base pattern value
 * @param nbSteps : base number of steps
 * @param nbHits : base number of hits per pattern
 * @param htim : attached timer
 * @param GPIOx : attached out bus
 * @param GPIO_Pin : attached pin
 * @return void
 */
/*void Seq_initSequencer(Sequencer* seq, GPIO_PinPort SWITCH, GPIO_PinPort BPM_ROTA, GPIO_PinPort BPM_ROTB,
		GPIO_PinPort BPMOUT, GPIO_PinPort BPMDISPLAY, TIM_HandleTypeDef* htim, Track* tracks, uint8_t nbTracks);*/
void Seq_initSequencer(Sequencer* seq, GPIO_PinPort SWITCH, GPIO_PinPort BPM_ROTA, GPIO_PinPort BPM_ROTB,
		GPIO_PinPort BPMOUT, GPIO_PinPort BPMDISPLAY, GPIO_PinPort MODEDISPLAY, TIM_HandleTypeDef* htim, Track_GPIOs* T_GPIOs);

/**
 * Modify Sequencer seq current BPM, according to the BPMROTB Pin State
 */
void Seq_modifyBPM(Sequencer* seq);

void Seq_IncrementBPMDisplay(Sequencer seq);

void Seq_DecrementBPMDisplay(Sequencer seq);

void Seq_IncrementModeDisplay(Sequencer seq);

void Seq_ResetModeDisplay(Sequencer seq);

/**
 * After modifying the BPM, restarts the timer with the new BPM value
 */
void Seq_updateBPM(Sequencer* seq);

/**
 * Error handler for the Sequencer class
 */
void Seq_Error_Handler(void);

void Seq_computeTriggers(Sequencer* seq);

/**
 * Updates the number of steps in the pattern according to the value of the pinState in parameter
 * @param i/o seq : the sequencer whose pattern is to be modified
 * @param i pinState : the pin controlling the behavior (pin for encoder's rotB)
 */
void Seq_updateSteps(Sequencer* seq, uint16_t pin);

/**
 * Updates the number of hits in the pattern according to the value of the pinState in parameter
 * @param i/o seq : the sequencer whose pattern is to be modified
 * @param i pinState : the pin controlling the behavior (pin for encoder's rotB)
 */
void Seq_updateHits(Sequencer* seq, uint16_t pin);

/**
 * Offsets the pattern of the sequencer seq according to the value of the pinState in parameter
 * @param i/o seq : the sequencer whose pattern is to be modified
 * @param i pinState : the pin controlling the behavior (pin for encoder's rotB)
 */
void Seq_offsetPattern(Sequencer* seq, uint16_t pin);

/**
 * Updates sequencers BPM by modifying its subdivision according to the value of the pinState in parameter
 * @param i/o seq : the sequencer whose subdivision is to be modified
 * @param i pinState : the pin controlling the behavior (pin for encoder's rotB)
 */
void Seq_updateSubdivision(Sequencer* seq, uint16_t pin);

void Seq_resetTriggers(Sequencer seq);

void Seq_Trigger(Sequencer* seq);

void Seq_ChangeMode(Sequencer* seq);

void Seq_TracksExternalInterruption(Sequencer* seq, uint16_t pin);

#ifdef __cplusplus
}
#endif

#endif // __SEQUENCER_H
