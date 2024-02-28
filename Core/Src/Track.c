#include "Track.h"



void Track_initTrack(Track* track, Track_GPIOs GPIOs, int nbTrig)/*GPIO_PinPort TRIGOUT,
		GPIO_PinPort ROTA, GPIO_PinPort ROTB, GPIO_PinPort CHASER, GPIO_PinPort BPMOUT)*/
{
	track->_currentStep = 1;
	track->_sub = E_NOIRE;
	track->_TRIGOUT = GPIOs.TRIGOUT;
	track->_ROTA = GPIOs.ROTA;
	track->_ROTB = GPIOs.ROTB;
	track->_CHASER = GPIOs.CHASER;
	track->_BPMOUT = GPIOs.BPMOUT;
	track->_PATTERN = GPIOs.PATTERN;
	track->_CLK = GPIOs.CLK;
	track->_LATCH = GPIOs.LATCH;
	Track_updatePattern(track, 8, nbTrig);
}

void Track_TriggerNextBeat(Track* track)
{
	track->_TrigNextBeat = Utils_boolToPinState((track->_pattern & (1 << (track->_nbSteps - track->_currentStep))) > 0);
}

void Track_updatePattern(Track* track, uint8_t nbSteps, uint8_t nbHits)
{
	track->_nbHits = nbHits;
	track->_nbSteps = nbSteps;
	track->_pattern = Utils_computePattern(track->_nbSteps, track->_nbHits);
	DisplayPattern(track->_pattern, track->_nbSteps, track->_CLK, track->_PATTERN, track->_LATCH);
}

void Track_updateSteps(Track* track, uint16_t pin)
{
	if(pin == track->_ROTA.Pin)
	{
		GPIO_PinState pinState = HAL_GPIO_ReadPin(track->_ROTB.Port, track->_ROTB.Pin);
		switch(pinState)
		{
		case GPIO_PIN_SET:
			if(track->_nbSteps < MAX_SEQUENCER_STEPS)
			{
				++track->_nbSteps;
			}
			break;
		case GPIO_PIN_RESET:
			if(track->_nbSteps > MIN_SEQUENCER_STEPS)
			{
				--track->_nbSteps;
			}
			break;
		default:
			break;
		}
		Track_updatePattern(track, track->_nbSteps, track->_nbHits);
	}
}

void Track_updateHits(Track* track, uint16_t pin)
{
	if(pin == track->_ROTA.Pin)
	{
		uint8_t pinState = HAL_GPIO_ReadPin(track->_ROTB.Port, track->_ROTB.Pin);
		switch(pinState)
		{
		case GPIO_PIN_SET:
			if(track->_nbHits < track->_nbSteps)
			{
				++track->_nbHits;
			}
			break;
		case GPIO_PIN_RESET:
			if(track->_nbHits > MIN_SEQUENCER_STEPS)
			{
				--track->_nbHits;
			}
			break;
		default:
			break;
		}
		Track_updatePattern(track, track->_nbSteps, track->_nbHits);
	}
}

void Track_offsetPattern(Track* track, uint16_t pin)
{

	if(pin == track->_ROTA.Pin)
	{
		track->_pattern = ((track->_pattern - ((track->_pattern >> 1 ) << 1)) << (track->_nbSteps - 1)) | (track->_pattern >> 1 );
		DisplayPattern(track->_pattern, track->_nbSteps, track->_CLK, track->_PATTERN, track->_LATCH);
	}
}

void Track_updateSubdivision(Track* track, uint16_t pin)
{
	if(pin == track->_ROTA.Pin)
	{
		uint8_t pinState = HAL_GPIO_ReadPin(track->_ROTB.Port, track->_ROTB.Pin);
		switch(pinState)
		{
		case GPIO_PIN_SET: // encoder turns clockwise : increments subdivision
			switch(track->_sub)
			{
			case E_NOIRE:
				track->_sub = E_CROCHE;
				break;
			case E_CROCHE:
				track->_sub = E_D_CROCHE;
				break;
			default:
				track->_sub = E_NOIRE;
				break;
			}
			break;
		case GPIO_PIN_RESET: // encode turns counterclockwise : decrements subdivision
			switch(track->_sub)
			{
			case E_CROCHE:
				track->_sub = E_NOIRE;
				break;
			case  E_D_CROCHE:
				track->_sub = E_CROCHE;
				break;
			default:
				track->_sub = E_D_CROCHE;
				break;
			}
			break;
		default:
			track->_sub = E_NOIRE;
			break;
		}
	}
}

void Track_TogglePin(Track* track, bool toggle)
{
	if(toggle)
	{
		HAL_GPIO_WritePin(track->_TRIGOUT.Port, track->_TRIGOUT.Pin, track->_TrigNextBeat);
		HAL_GPIO_WritePin(track->_BPMOUT.Port, track->_BPMOUT.Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(track->_CHASER.Port, track->_CHASER.Pin, Utils_boolToPinState(track->_currentStep==1));
		track->_currentStep = track->_currentStep < track->_nbSteps ? (track->_currentStep + 1) : 1;
	}
}
