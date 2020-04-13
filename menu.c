#include <stdio.h>
#include "cmn_defs.h"
#include "resampler.h"
#include "generator.h"
#define SIZE_MENU 2
#define SIZE_SETTING_MENU 6
#define SIZE_START_MENU 6
void fflush_stdin(){
    int c;
    do{
        c=getchar();
    }while(c!='\n' && c!=EOF);
}
void PrinterStartMenu(){
    const char LineMenu[SIZE_SETTING_MENU][14]={
        "Generate    ",
        "Add signal  ",
        "Settings    ",
        "Save        ",
        "Load        ",
        "Done        "};
    system("clear");
    for(uint8_t i=0;i<SIZE_START_MENU;i++)
        printf("%u. %s\n",(i+1),LineMenu[i]);
}
smp_16_t* SumSignal (const smp_16_t * first, const smpn_t samples_first,const smp_16_t *last, const smpn_t samples_last){
    smp_16_t *result=NULL;
    smpn_t samples=0;
    int32_t buffer=0;
    if(samples_first>samples_last){
        samples=samples_first;
        result=(smp_16_t*) malloc(samples * sizeof(smp_16_t));
        if(result!=NULL){
            for(smpn_t i=0;i<samples;i++){
                if(i<samples_last){
                    buffer=first[i]+last[i];
                    if(buffer<0){
                        if(buffer<INT16_MIN){
                            result[i]=INT16_MIN;
                        }else{
                            result[i]=buffer;
                        }
                    }else if (buffer>INT16_MAX) {
                        result[i]=INT16_MAX;
                    }else{
                        result[i]=buffer;
                    }
                }else {
                    result[i]=first[i];
                }
              }
        }else{
            return  NULL;
        }
    }else{
        samples=samples_last;
        result=(smp_16_t*) malloc(samples * sizeof(smp_16_t));
        if(result!=NULL){
            for(smpn_t i=0;i<samples_last;i++){
                if(i<samples_first){
                    buffer=first[i]+last[i];
                    if(buffer<0){
                        if(buffer<INT16_MIN){
                            result[i]=INT16_MIN;
                        }else{
                            result[i]=buffer;
                        }
                    }else if (buffer>INT16_MAX) {
                        result[i]=INT16_MAX;
                    }else{
                        result[i]=buffer;
                    }
                }else {
                    result[i]=last[i];
                }
            }
        }
        else{
            return  NULL;
        }
    }
    return result;
}
void PrinterSetting(const ESigType signal,const uint32_t amplitude,const uint32_t frequency, const uint32_t phase_shift,const ms_t lenght){
    printf("1. Amplitude- %u\n"
           "2. Frequency - %u\n"
           "3. Phase shift - %u\n"
           "4. Signal form- %u\n"
           "5. Lenght- %lu\n",amplitude,frequency,phase_shift,signal,lenght);
}
void PrinterSettingMenu ()
{
    const char LineMenu[SIZE_SETTING_MENU][14]={
        "Amplitude   ",
        "Frequency   ",
        "Phase shift ",
        "Signal form ",
        "Length      ",
        "Return      "};
    system("clear");
    for(uint8_t i=0;i<SIZE_SETTING_MENU;i++)
        printf("%u. %s\n",(i+1),LineMenu[i]);
}
void PrintMenu (){
    const char menu[SIZE_MENU][11]={
        "Start    ",
        "Exit     "
    };
    system("clear");
    for(uint8_t i=0;i<SIZE_MENU;i++)
        printf("%u. %s\n",(i+1),menu[i]);

}


void Start(){
    uint32_t amplitude=1000, frequency=44100, phase_shift=0;
    ms_t length=2000;
    ESigType signal=0;
    smpn_t samples = 0;
    smp_16_t* input_signal=NULL;

    uint32_t item=0;
    while (item!=6) {
        PrinterStartMenu();
        scanf("%u",&item);
        fflush_stdin();
        switch (item) {
        case 1:
            /* Generator*/
            if(amplitude==0){
                printf("Error value Amplitude. Press enter to continue\n");
                getchar();
                break;
            }
            if(frequency==0){
                printf("Error value Frequency. Press enter to continue\n");
                getchar();
                break;
            }
            if(signal!=0 && signal !=1){
                printf("Error type signal\n. Press enter to continue");
                getchar();
                break;
            }
            input_signal = generate_signal(signal, amplitude,length, frequency, 1000, 5, phase_shift,&samples);
            printf("Done!\n Press enter to continue!\n");
            getchar();

            break;
        case 2:
            {
            uint32_t amplitude_buffer=1000, frequency_buffer=44100, phase_shift_buffer=0;
            ms_t length_buffer=2000;
            ESigType signal_buffer=0;
            smpn_t samples_buffer = 0;
            smp_16_t* input_signal_buffer=NULL;
            Setting(&signal_buffer,&amplitude_buffer,&frequency_buffer,&phase_shift_buffer, &length_buffer);
            input_signal_buffer=generate_signal(signal_buffer, amplitude_buffer,length_buffer, frequency_buffer, 1000, 5, phase_shift_buffer,&samples_buffer);
            input_signal=SumSignal(input_signal,samples,input_signal_buffer,samples_buffer);
            printf("Done mix signal!\n");
            free(input_signal_buffer);
            }
            break;
        case 3:
            /*Settings*/
            Setting(&signal,&amplitude,&frequency,&phase_shift, &length);
            break;
        case 4:
            /* Save */
            Save(input_signal,samples);
            break;
        case 5:
             /* Load */
            Load(input_signal,&samples);
            break;
        case 6:
            break;
        default:
            system("clear");
            printf("Error select!Select again\n");
            break;
        }
    }
    free(input_signal);

}
void menu(){
    uint32_t item=0;
    while(item!=2){
        PrintMenu();
        scanf("%u",&item);
        fflush_stdin();
        switch (item) {
        case 1:
            Start();
            break;
        case 2:
            break;
        default:
            system("clear");
            printf("Error select!Select again\n");
            break;
        }
    }
}
