################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Assembler\ for\ the\ op\ codes.c \
../src/InitDevice.c \
../src/Interrupts.c \
../src/main.c 

OBJS += \
./src/Assembler\ for\ the\ op\ codes.OBJ \
./src/InitDevice.OBJ \
./src/Interrupts.OBJ \
./src/main.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/Assembler\ for\ the\ op\ codes.OBJ: ../src/Assembler\ for\ the\ op\ codes.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/Assembler\ for\ the\ op\ codes.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STDIO.H C:/SiliconLabs/SimplicityStudio/v4/developer/toolchains/keil_8051/9.53/INC/STRING.H C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/EFM8BB3/inc/SI_EFM8BB3_Register_Enums.h C:/Users/rsyed/SimplicityStudio/v4_workspace/emptyCProject/inc/signal.h C:/Users/rsyed/SimplicityStudio/v4_workspace/emptyCProject/inc/bsp.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/EFM8BB3/inc/SI_EFM8BB3_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/stdbool.h

src/%.OBJ: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/EFM8BB3/inc/SI_EFM8BB3_Register_Enums.h C:/Users/rsyed/SimplicityStudio/v4_workspace/emptyCProject/inc/InitDevice.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/EFM8BB3/inc/SI_EFM8BB3_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/stdbool.h

src/Interrupts.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/EFM8BB3/inc/SI_EFM8BB3_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/EFM8BB3/inc/SI_EFM8BB3_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/stdbool.h

src/main.OBJ: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/EFM8BB3/inc/SI_EFM8BB3_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/EFM8BB3/inc/SI_EFM8BB3_Defs.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/8051/v4.0.0/Device/shared/si8051Base/stdbool.h


