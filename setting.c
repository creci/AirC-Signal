#include <stdio.h>
#include "cmn_defs.h"
#include "resampler.h"
#include "generator.h"
void Setting( ESigType *signal,uint32_t *amplitude,uint32_t *frequency, uint32_t *phase_shift,ms_t *lenght){
    uint32_t item=0;
    while (item!=6) {
        PrinterSettingMenu();
        PrinterSetting(*(signal),*(amplitude),*(frequency),*(phase_shift),*(lenght));
        fflush(stdin);
        printf("Select item (enter number):");
        scanf("%u",&item);
        fflush_stdin();
        switch (item) {
        case 1:
            printf("\nEnter Amplitude(0-4294967295):");
            scanf("%u",amplitude);
            fflush_stdin();
            break;
        case 2:
            printf("\nEnter Frequency(0-4294967295):");
            scanf("%u",frequency);
            fflush_stdin();
            break;
        case 3:
            printf("\nEnter Phase Shift(0-4294967295):");
            scanf("%u",phase_shift);
            fflush_stdin();
            break;
        case 4:
            printf("\nSelect form signal():");
            scanf("%u",signal);
            fflush_stdin();
            break;
        case 5:
            printf("\nEnter length(generated signal length in ms):");
            scanf("%lu",lenght);
            fflush_stdin();
            break;
        default:
            break;
        }
    }

}
