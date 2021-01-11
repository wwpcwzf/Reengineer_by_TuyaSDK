C_SRC = ../app/app_adc.c ../app/app_common.c ../app/app_factory_test.c ../app/app_light_cmd.c ../app/app_light_control.c ../app/app_light_prompt.c ../app/app_light_uart.c ../app/app_rssi.c ../app/app_uart.c ../app/tuya_node_init.c ../app/wwpc_battery.c ../app/wwpc_config.c ../app/wwpc_key.c ../app/wwpc_light_control.c ../app/wwpc_main_loop.c ../app/wwpc_xm_camera.c
USER_OBJ = ./app/app_adc.o ./app/app_common.o ./app/app_factory_test.o ./app/app_light_cmd.o ./app/app_light_control.o ./app/app_light_prompt.o ./app/app_light_uart.o ./app/app_rssi.o ./app/app_uart.o ./app/tuya_node_init.o ./app/wwpc_battery.o ./app/wwpc_config.o ./app/wwpc_key.o ./app/wwpc_light_control.o ./app/wwpc_main_loop.o ./app/wwpc_xm_camera.o
INC = -I../_build -I../app
 
C_SRCS += ${C_SRC}
OBJS += ${USER_OBJ}
INCS += ${INC}
 
./app/%.o: ../app/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	$(CC) $(CFLAGS) ${INCS} -o $@ -c $< ${CMACROS}
	@echo 'Finished building: $<'
	@echo ' '
