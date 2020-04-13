#pragma once
#include "cmn_defs.h"

enum ESigType
{
    eSin,
    eTriangle
};

typedef enum ESigType ESigType;

smp_16_t* generate_signal(ESigType sig_type, amp_8_t amplitude, ms_t length, freq_t sample_rate, freq_t base_freq, uint8_t harmonics_n, uint32_t phase_shift,smpn_t *signal_samples);
