#include <stdio.h>
#include "cmn_defs.h"
#include "file.h"

void Load (smp_16_t *input_signal,smpn_t *samples){
    FILE *file;
    smpn_t count=1;
    file=fopen("signals.csv","r");
    if(file!=NULL){
        while (!feof(file))
        {
            if (fgetc(file) == '\n')
                count++;
        }
        if(count!=1){
        input_signal=(smp_16_t*) malloc(count * sizeof(smp_16_t));
        if(input_signal!=NULL){
        fseek(file,0,0);
        for(uint64_t i=0;i<count;i++){
            fscanf(file,"%" SCNd16, &input_signal[i]);
        }
        }
        *(samples)=count;
        fclose(file);
        }
        return;
    }else{
        perror("Error open file!\n");
        return;
    }
}
void Save(const smp_16_t *input_signal, const smpn_t samples){
    FILE *file;
    file=fopen("signals.csv","wt");
    if(file!=NULL){
        for(uint32_t i=0;i<samples;i++){
            fprintf(file,"%" SCNd16 "\n",input_signal[i]);
        }
        fclose(file);
        return;
    }else{
        perror("Error open file!\n");
        return;
    }
}
