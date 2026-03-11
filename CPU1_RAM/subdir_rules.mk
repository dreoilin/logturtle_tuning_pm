################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm" --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm/device" --include_path="C:/ti/C2000Ware_6_00_01_00/driverlib/f2837xd/driverlib/" --include_path="C:/ti/C2000Ware_6_00_01_00/libraries/calibration/hrpwm/f2837xd/include/" --include_path="C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/include" --include_path="C:/ti/C2000Ware_6_00_01_00/device_support/f2837xd/headers/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.cla $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm" --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm/device" --include_path="C:/ti/C2000Ware_6_00_01_00/driverlib/f2837xd/driverlib/" --include_path="C:/ti/C2000Ware_6_00_01_00/libraries/calibration/hrpwm/f2837xd/include/" --include_path="C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/include" --include_path="C:/ti/C2000Ware_6_00_01_00/device_support/f2837xd/headers/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1189490314: ../logturtle.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2041/ccs/utils/sysconfig_1.26.0/sysconfig_cli.bat" -s "C:/ti/C2000Ware_6_00_01_00/.metadata/sdk.json" -d "F2837xD" -p "F2837xD_176PTP" -r "F2837xD_176PTP" --script "C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm/logturtle.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1189490314 ../logturtle.syscfg
syscfg/board.h: build-1189490314
syscfg/board.cmd.genlibs: build-1189490314
syscfg/board.opt: build-1189490314
syscfg/board.json: build-1189490314
syscfg/pinmux.csv: build-1189490314
syscfg/epwm.dot: build-1189490314
syscfg/c2000ware_libraries.cmd.genlibs: build-1189490314
syscfg/c2000ware_libraries.opt: build-1189490314
syscfg/c2000ware_libraries.c: build-1189490314
syscfg/c2000ware_libraries.h: build-1189490314
syscfg/clocktree.h: build-1189490314
syscfg: build-1189490314

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm" --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm/device" --include_path="C:/ti/C2000Ware_6_00_01_00/driverlib/f2837xd/driverlib/" --include_path="C:/ti/C2000Ware_6_00_01_00/libraries/calibration/hrpwm/f2837xd/include/" --include_path="C:/ti/ccs2041/ccs/tools/compiler/ti-cgt-c2000_22.6.3.LTS/include" --include_path="C:/ti/C2000Ware_6_00_01_00/device_support/f2837xd/headers/include" --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/ciano/workspace_ccstheia/logturtle_tuning_pm/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


