/****************************************************************************************
> File Name: wwpc_config.h
> Description：
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#ifndef _wwpc_CONFIG_H
#define _WWPC_CONFIG_H

//=========================引用=================================
#include <stdint.h>

#include "ty_fifo.h"
#include "ty_light_save_user_flash.h"
#include "tuya_sigmesh_hal.h"



//==========================宏==================================
#define LUTEC_DEBUG_UART_ENABLE           1  //调试串口输出开关










//=======================外部引用===============================





//=========================申明=================================
uint8_t lutec_check_sum(uint8_t *data, uint8_t len);







#endif
/*************************************File end********************************************/
