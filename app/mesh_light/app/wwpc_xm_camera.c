/****************************************************************************************
> File Name: wwpc_xm_camera.h
> Description：
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#include "wwpc_xm_camera.h"

#include "app_common.h"

#define MAX_PACKET_LEN                    255    //数据包最大长度
#define MIN_PACKET_LEN                    7      //数据包最小长度


static uint8_t buf[256] = {0};

/*****************************************************************
*简  介：wifi模块通讯流程
*参  数：
*返回值：
*****************************************************************/
void lutec_wifimodule_thread(void)
{


}


/*****************************************************************
*简  介：wifi模块数据接收
*参  数：
*返回值：
*****************************************************************/
void lutec_wifimodule_data(void)
{
    uint8_t num = ty_fifo_get_size();
    //0、是否收到数据
    if(num < MIN_PACKET_LEN)//没有完整的数据包
        return;
    
    //1.judge head
    ty_fifo_read(buf,MIN_PACKET_LEN);//get head length datas,judge if it's head 
    //0x55AA00:Mesh数据(WiFi透传)；0x55CC00:WiFi模块数据------------其他数据包暂时不处理
    if(((buf[0] != 0x55) || (buf[1] != 0xAA) || (buf[2] != 0x00)) && ((buf[0] != 0x55) || (buf[1] != 0xCC) || (buf[2] != 0x00)))
    {   
        ty_fifo_pop(1);
        return;
    } 

    //2.judge if it's a whole frame
    uint16_t buf16 = 0;
    uint16_t total_len = 0;
    buf16 = ((uint16_t)buf[4] << 8) + buf[5];//数据长度
    total_len = buf16 + MIN_PACKET_LEN;//整个数据包长度    
    if(total_len > MAX_PACKET_LEN)//错误数据包
    {
        ty_fifo_pop(3);
        return;
    }  
    if(num < total_len)//数据包不完整
        return;

    //3.judge check sum 
    ty_fifo_read(buf, total_len);//read all frame data
#if LUTEC_DEBUG_UART_ENABLE //int hal_uart_send(u8 *datas, u8 length);
    //buf[5] = 0x01;
    //buf[8] = buf[9];
    //hal_uart_send(&buf[5], buf16+1);
    //app_light_vendor_data_publish(((uint16_t)buf[11]<< 8)+buf[12], &buf[5], buf16);

    hal_uart_send(buf, total_len);
#endif //LUTEC_DEBUG_UART_ENABLE
    uint8_t ck_sum = lutec_check_sum(buf, total_len-1);        
    if(ck_sum == buf[total_len-1])//校验正确
    {
        ty_fifo_pop(total_len);//correct frame,pop this frame length data
        //数据包分类：
        if(buf[1] == 0xAA)//Mesh数据(WiFi透传)
        {
            if(buf[3] == 0x06)//命令字：0x06下行DP数据----上行DP数据由Vendor Model处理
            {
                if((buf[6] > 100) && (buf[6] < 129))//dpID 0x65至0x80 为LUTEC自定义DP
                {
                    if((buf[8] == 0) && (buf[9] > 3) && (buf[9] < 240)) //功能指令长度应大于3Bytes：指向+地址+功能命令
                    {
                        if(buf[10] != 0x01)//不是远程下行
                        {
                            hal_uart_send(buf, total_len);
                            return;
                        }
                        buf16 = ((uint16_t)buf[11] << 8) + buf[12];//地址(目标)  
                        if(lutec_get_own_addr() == buf16)//远程点播
                        {
                            uint8_t ack_l = 0;
                            buf[7] = buf[6];
                            ack_l = lutec_protocol_dp_data(&buf[7]);
                            if(ack_l > 4)
                            {
                                lutec_updata_by_wifi(&buf[7], ack_l);
                            }
                        }
                        else //透传---广播和组播数据会转发回来
                        {                            
                            buf[7] = buf[6];                            
                            buf[6] = 0x01;
                            app_light_vendor_data_publish(buf16, &buf[6], buf[5]);
                        }                        
                    }
                }
                else //tuya定义的DP点暂不处理
                {
                    hal_uart_send(buf, total_len);
                }                
            }
            else //非0x06下行DP数据
            {
                hal_uart_send(buf, total_len);
            }            
        }
        else if(buf[1] == 0xCC)
        {
            lutec_protocol_wifimodul_data(&buf[6], buf16);
        }
        else
        {
            /* code */
        }        
    }
    else
    {//check sum not correct,pop the head length data
        ty_fifo_pop(3);
        return;     
    }
}

/*****************************************************************
*简  介：wifi模块数据解析
*参  数：
*返回值：
*****************************************************************/
void lutec_protocol_wifimodul_data(uint8_t *data_ptr, uint8_t data_len)
{
    switch(data_ptr[0])//dpID
    {
    case 0x6B://107wifi配网
        //execution_wan0x6B(buffer16_v, &uart_ptr->rx_data_buffer[10]);
        break;
    case 0x6C://108重启
        //execution_wan0x6C();
        break;
    case 0x71://113对时
        //execution_wan0x71(buffer16_v, &uart_ptr->rx_data_buffer[10]);
        break;
    case 0x7B://123更新
        //execution_wan0x7B(buffer16_v, &uart_ptr->rx_data_buffer[10]);
        break;
    case 0x7E://126设备识别码
        //execution_wan0x7E();
        break;
    case 0x7F://127wifi状态
        //if(get_cm_reset_flag() == 0xFB)
        //set_cm_reset_flag(0xFC);
        //cm_reset_flag = FALSE;
        //execution_wan0x7F(uart_ptr->rx_data_buffer[10]);
        //write_warning_bit(WIFI_MOUDLE_WARN, Fault_Clearance);
        //wifi_modue_error_counter = 0;//模块故障计数器重新计数
        break;
    case 0x80://128wifi模块信息
        //execution_wan0x80(buffer16_v, &uart_ptr->rx_data_buffer[10]);
        break;
    default:
        break;
    }

}

/*****************************************************************
*简  介：wifi模块数据解析
*参  数：
*返回值：
*****************************************************************/
void lutec_updata_by_wifi(uint8_t *data_ptr, uint8_t data_len)
{
    uint8_t data_buf[255] = {0};
    uint8_t sub_j = 0;

    data_buf[0] = 0x55;
    data_buf[1] = 0xAA;
    data_buf[2] = 0x00;
    data_buf[3] = 0x07;
    data_buf[4] = 0x00;
    data_buf[5] = data_len + 1;
    data_buf[6] = data_ptr[0];  
    data_buf[7] = 0x00;
    for(sub_j = 1; sub_j < data_len; sub_j++) 
        data_buf[sub_j + 7] = data_ptr[sub_j];
    data_buf[sub_j + 8] = lutec_check_sum(data_buf, sub_j + 8);

    hal_uart_send(data_buf, sub_j + 9);
}

/*************************************File end********************************************/
