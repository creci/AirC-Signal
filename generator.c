#include <stdlib.h>
#include <math.h>
#include "generator.h"

smp_16_t* generate_signal(ESigType sig_type, amp_8_t amplitude, ms_t length, freq_t sample_rate, freq_t base_freq, uint8_t harmonics_n, uint32_t phase_shift,smpn_t *signal_samples)
{
    static const float pi = 3.14;
    smpn_t samples = sample_rate * (length / 1000.0);
    smp_16_t* signal = (smp_16_t*) malloc(samples * sizeof(smp_16_t));

    if (!signal)
    {
        return NULL;
    }
    switch (sig_type) {
        case eSin:
        for (uint8_t harmonic_ind = 0; harmonic_ind < harmonics_n; harmonic_ind++)
        {
             freq_t freq = base_freq * (harmonic_ind + 1);
             float amp = 1.0 / (harmonic_ind + 1);
             for (smpn_t smp_ind = 0,k=1; smp_ind < samples; smp_ind++,k+=2)
             {
                 float t = (float) smp_ind / sample_rate;
                 signal[smp_ind] = amplitude*amp * sin(2 * pi * freq * t+phase_shift*pi);
             }
         }
         *signal_samples = samples;
         break;
        case eTriangle:
        {
            float w=(float)(2*pi)/base_freq;
            float sum=0;
            for (smpn_t smp_ind = 0; smp_ind < samples; smp_ind++)
            {
                sum=0;
                for(uint8_t harmonic_ind=0,k=1;harmonic_ind<harmonics_n;k+=2,harmonic_ind++){
                    sum+=pow((-1),((k-1)/2))*(sin(k*w*smp_ind+phase_shift*pi)/(k*k));
                }
                signal[smp_ind]=((8*amplitude)/(pi*pi))*sum;
            }
            *signal_samples = samples;
        }
         break;
            break;
        default:
            break;
    }
    return signal;

}
