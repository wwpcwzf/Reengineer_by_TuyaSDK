/****************************************************************************************
> File Name: wwpc_main_loop.h
> Description：
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#ifndef _wwpc_MAIN_LOOP_H
#define _WWPC_MAIN_LOOP_H

//=========================引用=================================
#include "wwpc_config.h"




//==========================宏==================================





//=======================外部引用===============================





//=========================申明=================================
void lutec_main_init(void);

void lutec_main_loop(void);

void lutec_mesh_state_callback(mesh_state_t stat);

void lutec_save_data_setvariable(LIGHT_CUST_DATA_FLASH_T *tSaveCustData);

void lutec_read_data_setvariable(LIGHT_CUST_DATA_FLASH_T tReadCustData);

void lutec_send_group_sddr(void);

#endif
/*************************************File end********************************************/
