/****************************************************************************************
> File Name: wwpc_light_control.h
> Description：
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#include "wwpc_light_control.h"




static uint16_t lutec_own_addr = 0;

static uint8_t lutec_onoff_flag = 0;






///-------------------------------------------------LUTEC Protocol------------------------------
/********************************************************************************************************
*简  介：
*参  数：
*返回值：
*********************************************************************************************************/
void lutec_protocol_bluetooth_dp(uint16_t src_addr, uint16_t dst_addr, uint8_t *par, int par_len)
{
#if LUTEC_DEBUG_UART_ENABLE //int hal_uart_send(u8 *datas, u8 length);
    hal_uart_send(par, par_len);
    //测试数据流app_light_vendor_data_publish(IN u16 DstAddr,IN u8 *VendorData,IN u8 DataLen)
    //par[5] = (uint8_t)((src_addr >> 8) & 0xFF);
    //par[6] = (uint8_t)((src_addr >> 0) & 0xFF);
    //app_light_vendor_data_publish(src_addr, par, par_len);
#endif //LUTEC_DEBUG_UART_ENABLE

    //---自定义协议网络luyou--------------------------------------------
    //par[4]指令流向(0x01:WiFi下行; 0x02:WiFi上行; 0x03:Bluetooth下行; 0x04:Buluetooth上行; 0x06:转发;)
    if(((par[4] == 0x03) || (par[4] == 0x01)) && (dst_addr >= 0xc000))//下行组播广播数据---转发
    {
        par[4] = 0x06;//转发
        app_light_vendor_data_publish(dst_addr, par, par_len);
        lutec_ack(par[4], par[1], src_addr);//lutec_ack(uint8_t point_to, uint8_t ack_id, uint16_t sent_to_addr)
    }
    if(par[4] == 0x02)//WiFi上行(不解析)---通过串口发出
    {
        lutec_updata_by_wifi(&par[1], par_len - 1);//mesh中的wifi数据上行
    }
    else
    {   
        uint8_t ack_len = 0;
        ack_len = lutec_protocol_dp_data(&par[1]);//指令解析
        if(ack_len >= 6)//回复 （dpID*1 数据类型*1 长度*1 指向*1 地址*2）== 6
        {
            par[0] = 0x01;
            app_light_vendor_data_publish(src_addr, par, ack_len + 1);
        }
    }
    
    
}
/********************************************************************************************************
*简  介：
*参  数：
*返回值：
*********************************************************************************************************/
void lutec_ack(uint8_t point_to, uint8_t ack_id, uint16_t sent_to_addr)
{
    uint8_t data_buffer[16] = {0};
    
    if((point_to == 0x01) || (point_to == 0x03))
    {
        if(point_to == 0x01)//远程指令简单回复
        {
            data_buffer[0]  = 0x55;
            data_buffer[1]  = 0xAA;
            data_buffer[2]  = 0x00;
            data_buffer[3]  = 0x07;
            data_buffer[4]  = 0x00;
            data_buffer[5]  = 0x09;
            data_buffer[6]  = 0x7C;  
            data_buffer[7]  = 0x00;     
            data_buffer[8]  = 0x00; 
            data_buffer[9]  = 0x05; 
            data_buffer[10] = point_to + 1; 
            data_buffer[11] = (lutec_own_addr >> 8) & 0xFF;
            data_buffer[12] = (lutec_own_addr >> 0) & 0xFF;
            data_buffer[13] = ack_id;
            data_buffer[14] = 0x06;
            data_buffer[15] = lutec_check_sum(data_buffer, 15);        

            hal_uart_send(data_buffer, 16);
        }
        else   //本地指令简单回复
        {
            data_buffer[0]  = 0x01;
            data_buffer[1]  = 0x7C;
            data_buffer[2]  = 0x00;
            data_buffer[3]  = 0x05;
            data_buffer[4]  = point_to + 1; 
            data_buffer[5]  = (lutec_own_addr >> 8) & 0xFF;
            data_buffer[6]  = (lutec_own_addr >> 0) & 0xFF;
            data_buffer[7]  = ack_id;
            data_buffer[8]  = 0x06;

            app_light_vendor_data_publish(sent_to_addr, data_buffer, 9);
        }
    }
    
}

/********************************************************************************************************
*简  介：DP指令解析
*参  数：
        uint16_t src_addr：指令来源，0x0000表示蓝牙未配网或者WiFi指令
        uint8_t *par：指令数据，首字节为dpID
*返回值：
        回复数据长度，回复参数存储于*par
*********************************************************************************************************/
uint8_t lutec_protocol_dp_data(uint8_t *par)
{
    switch(par[0])
    {
        case 0x65://开关
            switch (par[6])
            {
                case 0:
                    app_light_ctrl_data_switch_set(0);
                    app_light_ctrl_data_countdown_set(0);
                    lutec_onoff_flag = 0;
                    break;
                case 1:
                    app_light_ctrl_data_switch_set(1);
                    app_light_ctrl_data_countdown_set(0);
                    lutec_onoff_flag = 1;
                    break;
                case 2:
                    app_light_ctrl_data_switch_set(1);
                    app_light_ctrl_data_countdown_set(1000);
                    lutec_onoff_flag = 2;
                    break;
                default:
                    break;
            }
            app_light_ctrl_data_auto_save_start(5000);
            app_light_ctrl_proc();

            if((((uint16_t)par[4] << 8) + par[5]) < 0xC000)//点播---回复
            {
                par[1] = 0x00;              
                par[2] = 0x04;
                par[6] = lutec_onoff_flag;
                if((par[3] == 0x01) || (par[3] == 0x03))
                {
                    par[3] = par[3] + 1; 
                    return 7;
                }
                else
                {
                    return 0;
                } 
            }
            break;
        case 0x66://灯光调节
            //sys_execution_0x66();
            break;
        case 0x6A://延时调光
            //sys_execution_0x6A();
            break;
        case 0x6B://wifi配网
            //sys_execution_0x6B();
            break;
        case 0x6C://重启
            //sys_execution_0x6C();
            break;
        case 0x6D://感应器配置
            //sys_execution_0x6D();
            break;
        case 0x6E://感应灯控设置
            //sys_execution_0x6E();
            break;
        case 0x6F://感应查询、上报及设置
            //sys_execution_0x6F();
            break;
        case 0x70://云台控制
            //sys_ack_0x7C(0x03);//指令未实现
            break;
        case 0x71://时钟同步
            //sys_execution_0x71();
            break;
        case 0x72://电源信息   
            //sys_execution_0x72();
            break;
        case 0x73://环境照度    
            //sys_execution_0x73();
            break;
        case 0x74://环境湿度
            //sys_ack_0x7C(0x03);//指令未实现
            break;
        case 0x75://环境温度
            //sys_ack_0x7C(0x03);//指令未实现
            break;
        case 0x76://设备温度
            //sys_ack_0x7C(0x03);//指令未实现
            break;
        case 0x77://情景模式
            //sys_execution_0x77();
            break;
        case 0x78://设备状态
            //sys_execution_0x78();
            break;
        case 0x79://报警
            //sys_execution_0x79();
            break;
        case 0x7A://产测
            //sys_execution_0x7A();
            break;
        case 0x7B://更新固件
            //sys_execution_0x7B();
            break;
        //case 0x7C://应答
        //break;
        case 0x7D://注册指令（设置地址，分组）
            //sys_execution_0x7D();
            break;
        case 0x7E://设备识别号
            //sys_execution_0x7E();
            break;
        case 0x7F://wifi状态
            //sys_execution_0x7F();
            break;
        case 0x80: //wifi模块信息
            //sys_execution_0x80();
            break;
        default:
        break;
    }
    return 0;
}

///-------------------------------------------------LUTEC 灯控---------------------------------
static uint8_t scense_start_flag = 0;

/*****************************************************************
*简  介：
*参  数：
*返回值：
*****************************************************************/
void lutec_scenes_start(void)
{
    scense_start_flag = 1;
}
/*****************************************************************
*简  介：
*参  数：
*返回值：
*****************************************************************/
void lutec_scenes_runing(void)
{
    if(scense_start_flag != 1)
    {
        return;
    }






}





void lutec_set_own_addr(uint16_t new_addr)
{
    lutec_own_addr = new_addr;
}


uint16_t lutec_get_own_addr(void)
{
    return lutec_own_addr;
}

//ty_light_driver_set_rgbcw(0, 0, 0, 0, 0);









/*---------------------------------------------------------------------------------------*/
/*************************************File end********************************************/
