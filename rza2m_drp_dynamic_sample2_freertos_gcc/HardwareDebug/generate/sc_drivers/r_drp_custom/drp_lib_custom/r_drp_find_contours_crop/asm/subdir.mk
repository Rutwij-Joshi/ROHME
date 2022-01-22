################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_find_contours_crop/asm/r_drp_find_contours_crop_t2.asm 

OBJS += \
./generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_find_contours_crop/asm/r_drp_find_contours_crop_t2.o 

ASM_DEPS += \
./generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_find_contours_crop/asm/r_drp_find_contours_crop_t2.d 


# Each subdirectory must supply rules for building sources it contributes
generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_find_contours_crop/asm/%.o: ../generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_find_contours_crop/asm/%.asm
	$(file > $@.in,-mcpu=cortex-a9 -march=armv7-a -marm -mlittle-endian -mfloat-abi=hard -mfpu=neon -mno-unaligned-access -Og -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -Wmaybe-uninitialized -Wstack-usage=100 -g3 -x assembler-with-cpp -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/drp_lib" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/os_abstraction/inc" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo 'arm-none-eabi-gcc -mcpu=cortex-a9 -march=armv7-a -marm -mlittle-endian -mfloat-abi=hard -mfpu=neon -mno-unaligned-access -Og -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -Wmaybe-uninitialized -Wstack-usage=100 -g3 -x assembler-with-cpp -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/drp_lib" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/os_abstraction/inc" -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"'

	@arm-none-eabi-gcc @"$@.in"

