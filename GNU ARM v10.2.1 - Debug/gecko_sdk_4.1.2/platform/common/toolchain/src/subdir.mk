################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2/platform/common/toolchain/src/sl_memory.c 

OBJS += \
./gecko_sdk_4.1.2/platform/common/toolchain/src/sl_memory.o 

C_DEPS += \
./gecko_sdk_4.1.2/platform/common/toolchain/src/sl_memory.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.1.2/platform/common/toolchain/src/sl_memory.o: /Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2/platform/common/toolchain/src/sl_memory.c gecko_sdk_4.1.2/platform/common/toolchain/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG21A010F1024IM32=1' '-DSL_APP_PROPERTIES=1' '-DSL_BOARD_NAME="BRD4181B"' '-DSL_BOARD_REV="A03"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"/Users/clfilho/SimplicityStudio/C-Oct22/conn_interval_central_AM/config" -I"/Users/clfilho/SimplicityStudio/C-Oct22/conn_interval_central_AM/autogen" -I"/Users/clfilho/SimplicityStudio/C-Oct22/conn_interval_central_AM" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/Device/SiliconLabs/EFR32MG21/Include" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//app/common/util/app_assert" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//app/common/util/app_log" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//protocol/bluetooth/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//hardware/board/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/bootloader" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/bootloader/api" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/driver/button/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/CMSIS/Core/Include" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//hardware/driver/configuration_over_swo/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/driver/debug/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/device_init/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/emdrv/common/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/emlib/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/emdrv/gpiointerrupt/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/hfxo_manager/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/iostream/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/driver/leddrv/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/sl_component/sl_mbedtls_support/config" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/sl_component/sl_mbedtls_support/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/mbedtls/include" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/mbedtls/library" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/mpu/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/emdrv/nvm3/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/power_manager/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/sl_component/sl_psa_driver/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/sl_component/sl_psa_driver/inc/public" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/common" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/protocol/ble" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/protocol/ieee802154" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/protocol/zwave" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/plugin/pa-conversions" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/plugin/pa-conversions/efr32xg21" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/plugin/rail_util_pti" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/radio/rail_lib/plugin/rail_util_rf_path" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/sl_component/se_manager/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/sl_component/se_manager/src" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/silicon_labs/silabs_core/memory_manager" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//app/bluetooth/common/simple_timer" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/common/toolchain/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/system/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//platform/service/sleeptimer/inc" -I"/Users/clfilho/SimplicityStudio/SDKs/gecko_sdk_2//util/third_party/crypto/sl_component/sl_protocol_crypto/src" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.1.2/platform/common/toolchain/src/sl_memory.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


