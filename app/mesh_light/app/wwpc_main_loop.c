/****************************************************************************************
> File Name: wwpc_main_loop.h
> Description��
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#include "wwpc_main_loop.h"



/*****************************************************************
*��  �飺
*��  ����
*����ֵ��
*****************************************************************/
void lutec_main_loop(void)
{

#if LUTEC_DEBUG_UART_ENABLE
        
#endif //LUTEC_DEBUG_UART_ENABLE
    lutec_scenes_runing();
}

/*****************************************************************
*��  �飺
*��  ����
*����ֵ��
*****************************************************************/
void lutec_save_data_setvariable(LIGHT_CUST_DATA_FLASH_T *tSaveCustData)
{
    //tSaveCustData->lutec_wifi_name = 
    //tSaveCustData->lutec_wifi_passward = 
}
/*****************************************************************
*��  �飺
*��  ����
*����ֵ��
*****************************************************************/
void lutec_read_data_setvariable(LIGHT_CUST_DATA_FLASH_T tReadCustData)
{
        // = tReadCustData.lutec_wifi_passward;
        // = tReadCustData.lutec_wifi_name;


}

/*************************************File end********************************************/
