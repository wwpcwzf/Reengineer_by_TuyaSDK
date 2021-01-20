/****************************************************************************************
> File Name: wwpc_light_control.h
> Description：
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#ifndef _wwpc_LIGHT_CONTROL_H
#define _WWPC_LIGHT_CONTROL_H

//=========================引用=================================
#include "wwpc_config.h"



//==========================宏==================================





//=======================外部引用===============================





//=========================申明=================================
void lutec_protocol_bluetooth_dp(uint16_t src_addr, uint16_t dst_addr, uint8_t *par, int par_len);

void lutec_ack(uint8_t point_to, uint8_t ack_id, uint16_t sent_to_addr);

uint8_t lutec_protocol_dp_data(uint8_t *par);

void lutec_scenes_start(void);

void lutec_scenes_runing(void);

void lutec_set_own_addr(uint16_t new_addr);

uint16_t lutec_get_own_addr(void);





#endif
/*************************************File end********************************************/
