/****************************************************************************************
> File Name: wwpc_xm_camera.h
> Description：
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#ifndef _wwpc_XM_CAMERA_H
#define _WWPC_XM_CAMERA_H

//=========================引用=================================
#include "wwpc_config.h"



//==========================宏==================================





//=======================外部引用===============================





//=========================申明=================================
void lutec_wifimodule_thread(void);

void lutec_wifimodule_data(void);

void lutec_protocol_wifimodul_data(uint8_t *data_ptr, uint8_t data_len);

void lutec_updata_by_wifi(uint8_t *data_ptr, uint8_t data_len);


#endif
/*************************************File end********************************************/
