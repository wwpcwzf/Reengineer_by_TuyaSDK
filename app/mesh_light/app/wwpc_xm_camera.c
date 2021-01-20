/****************************************************************************************
> File Name: wwpc_xm_camera.h
> Description��
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#include "wwpc_xm_camera.h"

#include "app_common.h"

#define MAX_PACKET_LEN                    255    //���ݰ���󳤶�
#define MIN_PACKET_LEN                    7      //���ݰ���С����


static uint8_t buf[256] = {0};

/*****************************************************************
*��  �飺wifiģ��ͨѶ����
*��  ����
*����ֵ��
*****************************************************************/
void lutec_wifimodule_thread(void)
{


}


/*****************************************************************
*��  �飺wifiģ�����ݽ���
*��  ����
*����ֵ��
*****************************************************************/
void lutec_wifimodule_data(void)
{
    uint8_t num = ty_fifo_get_size();
    //0���Ƿ��յ�����
    if(num < MIN_PACKET_LEN)//û�����������ݰ�
        return;
    
    //1.judge head
    ty_fifo_read(buf,MIN_PACKET_LEN);//get head length datas,judge if it's head 
    //0x55AA00:Mesh����(WiFi͸��)��0x55CC00:WiFiģ������------------�������ݰ���ʱ������
    if(((buf[0] != 0x55) || (buf[1] != 0xAA) || (buf[2] != 0x00)) && ((buf[0] != 0x55) || (buf[1] != 0xCC) || (buf[2] != 0x00)))
    {   
        ty_fifo_pop(1);
        return;
    } 

    //2.judge if it's a whole frame
    uint16_t buf16 = 0;
    uint16_t total_len = 0;
    buf16 = ((uint16_t)buf[4] << 8) + buf[5];//���ݳ���
    total_len = buf16 + MIN_PACKET_LEN;//�������ݰ�����    
    if(total_len > MAX_PACKET_LEN)//�������ݰ�
    {
        ty_fifo_pop(3);
        return;
    }  
    if(num < total_len)//���ݰ�������
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
    if(ck_sum == buf[total_len-1])//У����ȷ
    {
        ty_fifo_pop(total_len);//correct frame,pop this frame length data
        //���ݰ����ࣺ
        if(buf[1] == 0xAA)//Mesh����(WiFi͸��)
        {
            if(buf[3] == 0x06)//�����֣�0x06����DP����----����DP������Vendor Model����
            {
                if((buf[6] > 100) && (buf[6] < 129))//dpID 0x65��0x80 ΪLUTEC�Զ���DP
                {
                    if((buf[8] == 0) && (buf[9] > 3) && (buf[9] < 240)) //����ָ���Ӧ����3Bytes��ָ��+��ַ+��������
                    {
                        if(buf[10] != 0x01)//����Զ������
                        {
                            hal_uart_send(buf, total_len);
                            return;
                        }
                        buf16 = ((uint16_t)buf[11] << 8) + buf[12];//��ַ(Ŀ��)  
                        if(lutec_get_own_addr() == buf16)//Զ�̵㲥
                        {
                            uint8_t ack_l = 0;
                            buf[7] = buf[6];
                            ack_l = lutec_protocol_dp_data(&buf[7]);
                            if(ack_l > 4)
                            {
                                lutec_updata_by_wifi(&buf[7], ack_l);
                            }
                        }
                        else //͸��---�㲥���鲥���ݻ�ת������
                        {                            
                            buf[7] = buf[6];                            
                            buf[6] = 0x01;
                            app_light_vendor_data_publish(buf16, &buf[6], buf[5]);
                        }                        
                    }
                }
                else //tuya�����DP���ݲ�����
                {
                    hal_uart_send(buf, total_len);
                }                
            }
            else //��0x06����DP����
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
*��  �飺wifiģ�����ݽ���
*��  ����
*����ֵ��
*****************************************************************/
void lutec_protocol_wifimodul_data(uint8_t *data_ptr, uint8_t data_len)
{
    switch(data_ptr[0])//dpID
    {
    case 0x6B://107wifi����
        //execution_wan0x6B(buffer16_v, &uart_ptr->rx_data_buffer[10]);
        break;
    case 0x6C://108����
        //execution_wan0x6C();
        break;
    case 0x71://113��ʱ
        //execution_wan0x71(buffer16_v, &uart_ptr->rx_data_buffer[10]);
        break;
    case 0x7B://123����
        //execution_wan0x7B(buffer16_v, &uart_ptr->rx_data_buffer[10]);
        break;
    case 0x7E://126�豸ʶ����
        //execution_wan0x7E();
        break;
    case 0x7F://127wifi״̬
        //if(get_cm_reset_flag() == 0xFB)
        //set_cm_reset_flag(0xFC);
        //cm_reset_flag = FALSE;
        //execution_wan0x7F(uart_ptr->rx_data_buffer[10]);
        //write_warning_bit(WIFI_MOUDLE_WARN, Fault_Clearance);
        //wifi_modue_error_counter = 0;//ģ����ϼ��������¼���
        break;
    case 0x80://128wifiģ����Ϣ
        //execution_wan0x80(buffer16_v, &uart_ptr->rx_data_buffer[10]);
        break;
    default:
        break;
    }

}

/*****************************************************************
*��  �飺wifiģ�����ݽ���
*��  ����
*����ֵ��
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
