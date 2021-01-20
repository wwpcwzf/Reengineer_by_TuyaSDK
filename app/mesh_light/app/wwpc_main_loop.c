/****************************************************************************************
> File Name: wwpc_main_loop.h
> Description：
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#include "wwpc_main_loop.h"

#include "wwpc_light_control.h"
#include "wwpc_xm_camera.h"





/*****************************************************************
*简  介：
*参  数：
*返回值：
*****************************************************************/
void lutec_main_init(void)
{
    

}

/*****************************************************************
*简  介：
*参  数：
*返回值：
*****************************************************************/
void lutec_main_loop(void)
{

#if LUTEC_DEBUG_UART_ENABLE
        
#endif //LUTEC_DEBUG_UART_ENABLE
    lutec_wifimodule_thread();//WiFi模块通讯
    lutec_scenes_runing();//自定义场景
}

/*****************************************************************
*简  介：
*参  数：
*返回值：
*****************************************************************/
void lutec_mesh_state_callback(mesh_state_t stat)
{
    static char LastMeshStat = 0xFF;
    //OPERATE_LIGHT opRet = 1;
    
    if(LastMeshStat != stat)
    {
        #if LUTEC_DEBUG_UART_ENABLE
        //hal_uart_send(par, par_len);
        #endif //LUTEC_DEBUG_UART_ENABLE

        switch(stat) 
        {
            case NODE_POWER_ON_UNPROVISION:
                lutec_set_own_addr(0x0000);
                app_light_ctrl_data_switch_set(TRUE);
                app_light_ctrl_prompt_start();
                break;
            case NODE_POWER_ON_IN_MESH:                
                lutec_set_own_addr(get_primary_ele_addr());
                app_light_ctrl_prompt_stop();
                break;
            case NODE_PROVISION_SUCCESS:
                lutec_set_own_addr(get_primary_ele_addr());
                break;
            case NODE_KICK_OUT:
                break;
            case NODE_MESH_RESET:
                lutec_set_own_addr(0x0000);
                break;
            case NODE_RECOVER_IN_MESH:
                lutec_set_own_addr(get_primary_ele_addr());
                break;
            case TY_OTA_START:
                break;
            case TY_OTA_SUCCESS:
            case TY_OTA_FAIL:
                break;
            case TY_GROUP_SUB_ADD:
                lutec_send_group_sddr();
                break;
            case TY_GROUP_SUB_DEL:
                lutec_send_group_sddr();
                break;
            default:
                break;
        }
        LastMeshStat = stat;
    }
}
/*****************************************************************
*简  介：
*参  数：
*返回值：
*****************************************************************/
void lutec_save_data_setvariable(LIGHT_CUST_DATA_FLASH_T *tSaveCustData)
{
    //tSaveCustData->lutec_wifi_name = 
    //tSaveCustData->lutec_wifi_passward = 
}
/*****************************************************************
*简  介：
*参  数：
*返回值：
*****************************************************************/
void lutec_read_data_setvariable(LIGHT_CUST_DATA_FLASH_T tReadCustData)
{
        // = tReadCustData.lutec_wifi_passward;
        // = tReadCustData.lutec_wifi_name;


}

void lutec_send_group_sddr(void)
{
    uint16_t *addr_buf = 0;
    uint8_t send_buf[16] = {0};
    uint8_t sub_i = 0;

    addr_buf = tuya_group_addr_sub_list_get();

    for(sub_i = 0; sub_i < 8; sub_i++)
    {
        send_buf[sub_i << 1] = (uint8_t)(addr_buf[sub_i] >> 8);
        send_buf[(sub_i << 1) + 1] = (uint8_t)(addr_buf[sub_i]);
    }
    hal_uart_send(send_buf, 16);
}



/*************************************File end********************************************/
