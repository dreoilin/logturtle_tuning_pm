################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../2837xD_RAM_lnk_cpu1.cmd 

SYSCFG_SRCS += \
../logturtle.syscfg 

CLA_SRCS += \
../cla_tasks.cla 

C_SRCS += \
../F2837xD_GlobalVariableDefs.c \
./syscfg/board.c \
./syscfg/c2000ware_libraries.c \
../main.c 

GEN_FILES += \
./syscfg/board.c \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt \
./syscfg/c2000ware_libraries.c 

CLA_DEPS += \
./cla_tasks.d 

GEN_MISC_DIRS += \
./syscfg 

C_DEPS += \
./F2837xD_GlobalVariableDefs.d \
./syscfg/board.d \
./syscfg/c2000ware_libraries.d \
./main.d 

GEN_OPTS += \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt 

OBJS += \
./F2837xD_GlobalVariableDefs.obj \
./cla_tasks.obj \
./syscfg/board.obj \
./syscfg/c2000ware_libraries.obj \
./main.obj 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/board.cmd.genlibs \
./syscfg/board.json \
./syscfg/pinmux.csv \
./syscfg/epwm.dot \
./syscfg/c2000ware_libraries.cmd.genlibs \
./syscfg/c2000ware_libraries.h \
./syscfg/clocktree.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg" 

OBJS__QUOTED += \
"F2837xD_GlobalVariableDefs.obj" \
"cla_tasks.obj" \
"syscfg\board.obj" \
"syscfg\c2000ware_libraries.obj" \
"main.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\board.cmd.genlibs" \
"syscfg\board.json" \
"syscfg\pinmux.csv" \
"syscfg\epwm.dot" \
"syscfg\c2000ware_libraries.cmd.genlibs" \
"syscfg\c2000ware_libraries.h" \
"syscfg\clocktree.h" 

C_DEPS__QUOTED += \
"F2837xD_GlobalVariableDefs.d" \
"syscfg\board.d" \
"syscfg\c2000ware_libraries.d" \
"main.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" \
"syscfg\board.opt" \
"syscfg\c2000ware_libraries.opt" \
"syscfg\c2000ware_libraries.c" 

CLA_DEPS__QUOTED += \
"cla_tasks.d" 

C_SRCS__QUOTED += \
"../F2837xD_GlobalVariableDefs.c" \
"./syscfg/board.c" \
"./syscfg/c2000ware_libraries.c" \
"../main.c" 

SYSCFG_SRCS__QUOTED += \
"../logturtle.syscfg" 


