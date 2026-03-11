################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
OBJ_SRCS += \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c2000ISR.obj \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xGPIO.obj \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xGlobalInterrupts.obj \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_board.obj \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_csl.obj \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_pwm.obj \
../Modelling/Simulink/TestBlink_ert_rtw/TestBlink.obj \
../Modelling/Simulink/TestBlink_ert_rtw/TestBlink_data.obj \
../Modelling/Simulink/TestBlink_ert_rtw/c2000HardwareTimerConfig.obj \
../Modelling/Simulink/TestBlink_ert_rtw/c2000HardwareTimerSupport.obj \
../Modelling/Simulink/TestBlink_ert_rtw/c28004xBoard_Realtime_Support.obj \
../Modelling/Simulink/TestBlink_ert_rtw/c28004xSchedulerTimer0.obj \
../Modelling/Simulink/TestBlink_ert_rtw/clb.obj \
../Modelling/Simulink/TestBlink_ert_rtw/datamodify_xcp.obj \
../Modelling/Simulink/TestBlink_ert_rtw/dma.obj \
../Modelling/Simulink/TestBlink_ert_rtw/ert_main.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_adc.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_codestartbranch.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_cputimers.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_defaultisr.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_globalvariabledefs.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_gpio.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_piectrl.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_pievect.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_sysctrl.obj \
../Modelling/Simulink/TestBlink_ert_rtw/f28004x_usdelay.obj \
../Modelling/Simulink/TestBlink_ert_rtw/mw_soc_c2000_ipc.obj \
../Modelling/Simulink/TestBlink_ert_rtw/rtiostream_serial_c28x.obj \
../Modelling/Simulink/TestBlink_ert_rtw/sysctl.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_calibration.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_daq.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_drv_rtiostream.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_ext_classic_trigger.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_ext_common.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_ext_mode.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_ext_param_default_serial.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_fifo.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_frame_serial.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_mem_default.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_standard.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_transport.obj \
../Modelling/Simulink/TestBlink_ert_rtw/xcp_utils.obj 

C_SRCS += \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_board.c \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_csl.c \
../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_pwm.c \
../Modelling/Simulink/TestBlink_ert_rtw/TestBlink.c \
../Modelling/Simulink/TestBlink_ert_rtw/TestBlink_data.c \
../Modelling/Simulink/TestBlink_ert_rtw/ert_main.c 

C_DEPS += \
./Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_board.d \
./Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_csl.d \
./Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_pwm.d \
./Modelling/Simulink/TestBlink_ert_rtw/TestBlink.d \
./Modelling/Simulink/TestBlink_ert_rtw/TestBlink_data.d \
./Modelling/Simulink/TestBlink_ert_rtw/ert_main.d 

OBJS += \
./Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_board.obj \
./Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_csl.obj \
./Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_pwm.obj \
./Modelling/Simulink/TestBlink_ert_rtw/TestBlink.obj \
./Modelling/Simulink/TestBlink_ert_rtw/TestBlink_data.obj \
./Modelling/Simulink/TestBlink_ert_rtw/ert_main.obj 

OBJS__QUOTED += \
"Modelling\Simulink\TestBlink_ert_rtw\MW_c28xx_board.obj" \
"Modelling\Simulink\TestBlink_ert_rtw\MW_c28xx_csl.obj" \
"Modelling\Simulink\TestBlink_ert_rtw\MW_c28xx_pwm.obj" \
"Modelling\Simulink\TestBlink_ert_rtw\TestBlink.obj" \
"Modelling\Simulink\TestBlink_ert_rtw\TestBlink_data.obj" \
"Modelling\Simulink\TestBlink_ert_rtw\ert_main.obj" 

C_DEPS__QUOTED += \
"Modelling\Simulink\TestBlink_ert_rtw\MW_c28xx_board.d" \
"Modelling\Simulink\TestBlink_ert_rtw\MW_c28xx_csl.d" \
"Modelling\Simulink\TestBlink_ert_rtw\MW_c28xx_pwm.d" \
"Modelling\Simulink\TestBlink_ert_rtw\TestBlink.d" \
"Modelling\Simulink\TestBlink_ert_rtw\TestBlink_data.d" \
"Modelling\Simulink\TestBlink_ert_rtw\ert_main.d" 

C_SRCS__QUOTED += \
"../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_board.c" \
"../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_csl.c" \
"../Modelling/Simulink/TestBlink_ert_rtw/MW_c28xx_pwm.c" \
"../Modelling/Simulink/TestBlink_ert_rtw/TestBlink.c" \
"../Modelling/Simulink/TestBlink_ert_rtw/TestBlink_data.c" \
"../Modelling/Simulink/TestBlink_ert_rtw/ert_main.c" 


