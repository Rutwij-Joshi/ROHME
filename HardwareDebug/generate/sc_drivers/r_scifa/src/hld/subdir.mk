################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../generate/sc_drivers/r_scifa/src/hld/r_scifa_drv_api.c \
../generate/sc_drivers/r_scifa/src/hld/r_scifa_hld_prv.c 

C_DEPS += \
./generate/sc_drivers/r_scifa/src/hld/r_scifa_drv_api.d \
./generate/sc_drivers/r_scifa/src/hld/r_scifa_hld_prv.d 

OBJS += \
./generate/sc_drivers/r_scifa/src/hld/r_scifa_drv_api.o \
./generate/sc_drivers/r_scifa/src/hld/r_scifa_hld_prv.o 


# Each subdirectory must supply rules for building sources it contributes
generate/sc_drivers/r_scifa/src/hld/%.o: ../generate/sc_drivers/r_scifa/src/hld/%.c
	$(file > $@.in,-mcpu=cortex-a9 -march=armv7-a -marm -mlittle-endian -mfloat-abi=hard -mfpu=neon -mno-unaligned-access -Og -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -Wmaybe-uninitialized -Wstack-usage=100 -g3 -I"C:\\Users\\rj7356s\\e2-new\\workspace\\rza2m_drp_dynamic_sample2_freertos_gcc\\src\\FreeRTOS\\include" -I"C:\\Users\\rj7356s\\e2-new\\workspace\\rza2m_drp_dynamic_sample2_freertos_gcc\\src\\FreeRTOS\\include\\private" -I"C:\\Users\\rj7356s\\e2-new\\workspace\\rza2m_drp_dynamic_sample2_freertos_gcc\\src\\FreeRTOS\\portable\\GCC\\ARM_CA9_RZA2M" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/compiler/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/configuration" -I"C:\\Users\\rj7356s\\e2-new\\workspace\\rza2m_drp_dynamic_sample2_freertos_gcc\\src\\config_files" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/system/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/src/renesas/application/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_riic/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_rvapi/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_mipi/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_ceu/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_vdc/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_ostm/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_scifa/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/system/iodefine" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_lrgb2lcrop/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_lrgb2l_gaussian_blur/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_bayer2lrgb_color_correction/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_bayer2lrgb/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_find_contours_crop/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_resize_bilinear_crop/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/src" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/drp_lib" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_stb/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_gpio/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/os_abstraction/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_intc/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_cache/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_cbuffer/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_mmu/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_cpg/inc" -fabi-version=0 -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo 'arm-none-eabi-gcc -mcpu=cortex-a9 -march=armv7-a -marm -mlittle-endian -mfloat-abi=hard -mfpu=neon -mno-unaligned-access -Og -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wnull-dereference -Wmaybe-uninitialized -Wstack-usage=100 -g3 -I"C:\\Users\\rj7356s\\e2-new\\workspace\\rza2m_drp_dynamic_sample2_freertos_gcc\\src\\FreeRTOS\\include" -I"C:\\Users\\rj7356s\\e2-new\\workspace\\rza2m_drp_dynamic_sample2_freertos_gcc\\src\\FreeRTOS\\include\\private" -I"C:\\Users\\rj7356s\\e2-new\\workspace\\rza2m_drp_dynamic_sample2_freertos_gcc\\src\\FreeRTOS\\portable\\GCC\\ARM_CA9_RZA2M" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/compiler/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/configuration" -I"C:\\Users\\rj7356s\\e2-new\\workspace\\rza2m_drp_dynamic_sample2_freertos_gcc\\src\\config_files" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/system/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/src/renesas/application/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_riic/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_rvapi/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_mipi/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_ceu/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_vdc/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_ostm/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_scifa/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/system/iodefine" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_lrgb2lcrop/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_lrgb2l_gaussian_blur/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_bayer2lrgb_color_correction/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_bayer2lrgb/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_find_contours_crop/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp_custom/drp_lib_custom/r_drp_resize_bilinear_crop/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/src" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_drp/drp_lib" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_stb/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_gpio/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/os_abstraction/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_intc/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_cache/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/sc_drivers/r_cbuffer/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_mmu/inc" -I"C:/Users/rj7356s/e2-new/workspace/rza2m_drp_dynamic_sample2_freertos_gcc/generate/drivers/r_cpg/inc" -fabi-version=0 -Wa,-adhlns="$@.lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"'

	@arm-none-eabi-gcc @"$@.in"

