#include "tuning_targets.h"
#include "encoder.h"
#include "spi_reference.h"
#include "cla_cpu_shared.h"

volatile TuningTarget_e gTuningTarget = TUNING_TARGET_FREQUENCY;

static uint16_t gVrefACode10 = 512U;
static uint16_t gVrefBCode10 = 512U;

#define VREF_STEP_CODE 10U 
#define VREF_CODE_MIN 0U
#define VREF_CODE_MAX 1023U

static int16_t gAuxDutyOffsetQ8 = 0;

#define AUX_DUTY_STEP_Q8 256
#define AUX_DUTY_OFFSET_LIMIT 16000

void tuningTargetsInit(void){
    spiReferenceWriteCode(SPI_REF_CHANNEL_A, gVrefACode10);
    spiReferenceWriteCode(SPI_REF_CHANNEL_B, gVrefBCode10);

    cpuToClaMsg.manual_aux_duty_override = 0U;
    cpuToClaMsg.manual_offset_value = gAuxDutyOffsetQ8;
}

void tuningApplyStep(int16_t direction){
    switch(gTuningTarget){
        case TUNING_TARGET_FREQUENCY:
            cpuToClaMsg.manual_aux_duty_override = 0U;
            encoderStepFrequency(direction);
            break;

        case TUNING_TARGET_VREFA:
            cpuToClaMsg.manual_aux_duty_override = 0U;
            if(direction > 0){
                if(gVrefACode10 <= (VREF_CODE_MAX - VREF_STEP_CODE)){
                    gVrefACode10 += VREF_STEP_CODE;
                }
                else{
                    gVrefACode10 = VREF_CODE_MAX;
                }
            }
            else{
                if(gVrefACode10 >= (VREF_CODE_MIN + VREF_STEP_CODE)){
                    gVrefACode10 -= VREF_STEP_CODE;
                }
                else{
                    gVrefACode10 = VREF_CODE_MIN;
                }
            }
            spiReferenceWriteCode(SPI_REF_CHANNEL_A, gVrefACode10);
            break;
        
        case TUNING_TARGET_VREFB:
            cpuToClaMsg.manual_aux_duty_override = 0U;
            if(direction > 0){
                if(gVrefBCode10 <= (VREF_CODE_MAX - VREF_STEP_CODE)){
                    gVrefBCode10 += VREF_STEP_CODE;
                }
                else{
                    gVrefBCode10 = VREF_CODE_MAX;
                }
            }
            else{
                if(gVrefBCode10 >= (VREF_CODE_MIN + VREF_STEP_CODE)){
                    gVrefBCode10 -= VREF_STEP_CODE;
                }
                else{
                    gVrefBCode10 = VREF_CODE_MIN;
                }
            }
            spiReferenceWriteCode(SPI_REF_CHANNEL_A, gVrefBCode10);
            break;

        case TUNING_TARGET_AUX_DUTY:
            if(direction > 0){
                if(gAuxDutyOffsetQ8 <= (AUX_DUTY_OFFSET_LIMIT - AUX_DUTY_STEP_Q8)){
                    gAuxDutyOffsetQ8 += AUX_DUTY_STEP_Q8;
                }
                else{
                    gAuxDutyOffsetQ8 = AUX_DUTY_OFFSET_LIMIT;
                }
            }
            else{
                if(gAuxDutyOffsetQ8 >= (-AUX_DUTY_OFFSET_LIMIT + AUX_DUTY_STEP_Q8)){
                    gAuxDutyOffsetQ8 -= AUX_DUTY_STEP_Q8;
                }
                else{
                    gAuxDutyOffsetQ8 = -AUX_DUTY_OFFSET_LIMIT;
                }
            }
            cpuToClaMsg.manual_offset_value = gAuxDutyOffsetQ8;
            cpuToClaMsg.manual_aux_duty_override = 1U;
            break;
        
        default:
            break;
    }
}

uint16_t tuningGetVrefACode(void){
    return gVrefACode10;
}

uint16_t tuningGetVrefBCode(void){
    return gVrefBCode10;
}

uint16_t tuningGetAuxDutyOffset(void){
    return gAuxDutyOffsetQ8;
}