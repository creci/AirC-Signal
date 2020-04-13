#pragma once
#include "cmn_defs.h"
#include "generator.h"

void fflush_stdin();
void PrinterStartMenu();
void PrinterSetting(const ESigType signal,const uint32_t amplitude,const uint32_t frequency, const uint32_t phase_shift,const ms_t lenght);
void PrinterSettingMenu ();
void PrintMenu ();
void Setting( ESigType *signal,uint32_t *amplitude,uint32_t *frequency, uint32_t *phase_shift,ms_t *lenght);
void Load (smp_16_t *input_signal,smpn_t *samples);
void Save(const smp_16_t *input_signal, const smpn_t samples);
void Start();
void menu();
