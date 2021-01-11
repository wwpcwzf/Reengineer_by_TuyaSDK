/****************************************************************************************
> File Name: wwpc_main_loop.h
> Description£º
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#include "wwpc_main_loop.h"



/******************************************************************
*?  ????????
*?  ??
*????
*******************************************************************/
void lutec_main_loop(void)
{

#if LUTEC_DEBUG_UART_ENABLE
        
#endif //LUTEC_DEBUG_UART_ENABLE
    lutec_scenes_runing();
}

/******************************************************************
*?  ????????????? ??app_light_ctrl_data_auto_save(TYPE_USER_DATA)??
*?  ??
*????
************************************S*******************************/
void lutec_save_data_setvariable(LIGHT_CUST_DATA_FLASH_T *tSaveCustData)
{
    //tSaveCustData->lutec_wifi_name = 
    //tSaveCustData->lutec_wifi_passward = 
}
/******************************************************************
*?  ???????Flash?? app_light_ctrl_data_auto_read(TYPE_USER_DATA)??
*?  ??
*????
*******************************************************************/
void lutec_read_data_setvariable(LIGHT_CUST_DATA_FLASH_T tReadCustData)
{
        // = tReadCustData.lutec_wifi_passward;
        // = tReadCustData.lutec_wifi_name;


}

/*************************************File end********************************************/
