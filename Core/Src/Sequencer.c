#include "Sequencer.h"

void Seq_initSequencer(Sequencer* seq, GPIO_PinPort SWITCH, GPIO_PinPort BPM_ROTA, GPIO_PinPort BPM_ROTB,
		GPIO_PinPort BPMOUT, GPIO_PinPort BPMDISPLAY, GPIO_PinPort MODEDisplay, TIM_HandleTypeDef* htim, Track_GPIOs* T_GPIOs)
{
	seq->_SWITCH = SWITCH;
	seq->_BPM_ROTA = BPM_ROTA;
	seq->_BPM_ROTB = BPM_ROTB;
	seq->_BPMOUT = BPMOUT;
	seq->_BPMDisplay = BPMDISPLAY;
	seq->_MODEDisplay = MODEDisplay;
	seq->_htim = htim;
	for(int i=0; i < NBTRACKS; ++i)
	{
		Track_initTrack(&(seq->_tracks[i]), T_GPIOs[i], i+1);
	}
	seq->_BPM = 60;
	for(int i=0; i <= seq->_BPM; ++i)
	{
		Seq_IncrementBPMDisplay(*seq);
	}
	seq->_htim->Init.Period = ((65536*20)/(seq->_BPM))-1;
	seq->_BPM_Update = true;
	Seq_updateBPM(seq);
	seq->_mode = E_STEPS;
}

void Seq_IncrementBPMDisplay(Sequencer seq)
{
	HAL_GPIO_WritePin(seq._BPMDisplay.Port, seq._BPMDisplay.Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(seq._BPMDisplay.Port, seq._BPMDisplay.Pin, GPIO_PIN_RESET);
}

void Seq_DecrementBPMDisplay(Sequencer seq)
{
	for(int i=0; i<999; ++i)
	{
		HAL_GPIO_WritePin(seq._BPMDisplay.Port, seq._BPMDisplay.Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(seq._BPMDisplay.Port, seq._BPMDisplay.Pin, GPIO_PIN_RESET);
	}
}

void Seq_IncrementModeDisplay(Sequencer seq)
{
	HAL_GPIO_WritePin(seq._MODEDisplay.Port, seq._MODEDisplay.Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(seq._MODEDisplay.Port, seq._MODEDisplay.Pin, GPIO_PIN_RESET);
}

void Seq_ResetModeDisplay(Sequencer seq)
{
	for(int i=0; i<7; ++i)
	{
		HAL_GPIO_WritePin(seq._MODEDisplay.Port, seq._MODEDisplay.Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(seq._MODEDisplay.Port, seq._MODEDisplay.Pin, GPIO_PIN_RESET);
	}
}

void Seq_ChangeMode(Sequencer* seq)
{
	switch(seq->_mode)
	{
	case E_STEPS:
		seq->_mode = E_HITS;
		Seq_IncrementModeDisplay(*seq);
		break;
	case E_HITS:
		seq->_mode = E_SUB;
		Seq_IncrementModeDisplay(*seq);
		break;
	case E_SUB:
		seq->_mode = E_OFFSET;
		Seq_IncrementModeDisplay(*seq);
		break;
	case E_OFFSET:
		seq->_mode = E_STEPS;
		Seq_ResetModeDisplay(*seq);
		break;
	default:
		seq->_mode = E_STEPS;
		Seq_ResetModeDisplay(*seq);
		break;
	}
}

void Seq_modifyBPM(Sequencer* seq)
{
	switch(HAL_GPIO_ReadPin(seq->_BPM_ROTB.Port, seq->_BPM_ROTB.Pin))
	{
	case GPIO_PIN_SET:
		if(seq->_BPM < 250)
		{
			++(seq->_BPM);
			Seq_IncrementBPMDisplay(*seq);
		}
		break;
	case GPIO_PIN_RESET:
		if(seq->_BPM > 20)
		{
			--(seq->_BPM);
			Seq_DecrementBPMDisplay(*seq);
		}
		break;
	default:
		break;
	}
	seq->_htim->Init.Period = ((65536*20)/(seq->_BPM))-1;
	seq->_BPM_Update = true;
}

void Seq_updateBPM(Sequencer* seq)
{
	if(seq->_BPM_Update)
	{
		if (HAL_TIM_Base_Init(seq->_htim) != HAL_OK)
		{
			Seq_Error_Handler();
		}
		HAL_TIM_Base_Start_IT(seq->_htim);
		seq->_BPM_Update = false;
	}
}

void Seq_Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

void Seq_computeTriggers(Sequencer* seq)
{
	if(!seq->_computed)
	{
		seq->_BPMTrig = Utils_boolToPinState(seq->_step % 4 == 0);
		for(int i=0; i < NBTRACKS; ++i)
		{
			seq->_SeqTrig[i] = seq->_step % seq->_tracks[i]._sub == 0;
			Track_TriggerNextBeat(&(seq->_tracks[i]));
		}
		seq->_step = (seq->_step + 1) % 4;
		seq->_computed = true;
	}
}

void Seq_Trigger(Sequencer* seq)
{
	HAL_GPIO_WritePin(seq->_BPMOUT.Port, seq->_BPMOUT.Pin, seq->_BPMTrig);
	for(int i=0; i < NBTRACKS; ++i)
	{
		Track_TogglePin(&(seq->_tracks[i]), seq->_SeqTrig[i]);
	}
	seq->_computed = false;
	Seq_updateBPM(seq);
}

void Seq_TracksExternalInterruption(Sequencer* seq, uint16_t pin)
{
	switch(seq->_mode)
	{
	case E_STEPS:
		Seq_updateSteps(seq, pin);
		break;
	case E_HITS:
		Seq_updateHits(seq, pin);
		break;
	case E_SUB:
		Seq_updateSubdivision(seq, pin);
		break;
	case E_OFFSET:
		Seq_offsetPattern(seq, pin);
		break;
	default:
		break;
	}
}

void Seq_updateSteps(Sequencer* seq, uint16_t pin)
{
	for(int i = 0 ; i < NBTRACKS ; ++i)
	{
		Track_updateSteps(&(seq->_tracks[i]), pin);
	}
}

void Seq_updateHits(Sequencer* seq, uint16_t pin)
{
	for(int i = 0 ; i < NBTRACKS ; ++i)
	{
		Track_updateHits(&(seq->_tracks[i]), pin);
	}
}

void Seq_offsetPattern(Sequencer* seq, uint16_t pin)
{
	for(int i = 0 ; i < NBTRACKS ; ++i)
	{
		Track_offsetPattern(&(seq->_tracks[i]), pin);
	}
}

void Seq_updateSubdivision(Sequencer* seq, uint16_t pin)
{
	for(int i = 0 ; i < NBTRACKS ; ++i)
	{
		Track_updateSubdivision(&(seq->_tracks[i]), pin);
	}
}

void Seq_resetTriggers(Sequencer seq)
{
	//HAL_GPIO_WritePin(seq._tracks[i]._TRIGOUT.Port, seq._tracks[i]._TRIGOUT.Pin, GPIO_PIN_RESET);
	for(int i = 0; i < 109000; ++i) asm("NOP");
	HAL_GPIO_WritePin(seq._BPMOUT.Port, seq._BPMOUT.Pin, GPIO_PIN_RESET);
	for(int i = 0 ; i < NBTRACKS ; ++i)
	{
		HAL_GPIO_WritePin(seq._tracks[i]._TRIGOUT.Port, seq._tracks[i]._TRIGOUT.Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(seq._tracks[i]._BPMOUT.Port, seq._tracks[i]._BPMOUT.Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(seq._tracks[i]._CHASER.Port, seq._tracks[i]._CHASER.Pin, GPIO_PIN_RESET);
	}
}
