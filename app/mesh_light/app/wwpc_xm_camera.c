/****************************************************************************************
> File Name: wwpc_xm_camera.h
> Description£º
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#include "wwpc_xm_camera.h"

#include "ty_fifo.h"

/***********************************************************************************************
*?  ????????????
*?  ?? 
*       uint8_t *par   ????????
*       int par_len    ???????
*????
*       ?
***********************************************************************************************/
void lutec_xm_data(void){
#if 0
    static u8 is_factory = 1;
    u8 i,num = ty_fifo_get_size();
    if(num < F_MIN_LEN)return;
    
    //1.judge head
    u8 buf[256];

    ty_fifo_read(buf,F_MIN_LEN);//get head length datas,judge if it's head
    if(((buf[F_HEAD1] != 0x66) || (buf[F_HEAD2] != 0xaa) || (buf[F_HEAD3] != 0x00)) &&//factory 
            ((buf[F_HEAD1] != 0xa5) || (buf[F_HEAD2] != 0x5a) || (buf[F_HEAD3] != 0x00))){//mesh light
        ty_fifo_pop(1);
        return;
    }


    u8 head = buf[F_HEAD1];
    u8 cmd = buf[F_CMD];
    u8 len = 0, total_len = 0;
    if(head == 0xa5){                    //mesh light
        len = buf[UART_F_LEN2];
        total_len = len + UART_F_MIN_LEN;
    }else if(head == 0x66){             //2.judge if it's a whole frame
        len = buf[F_LEN2];
        total_len = len + F_MIN_LEN;

        if(len > F_MAX_LEN){                    //error frame,the max frame data len is pid+version=39
            ty_fifo_pop(3);
            return;
        }
    }
    if(num < total_len)return;

    //3.judge check sum 
    ty_fifo_read(buf,total_len);//read all frame data
    u8 ck_sum = app_uart_check_sum(buf,total_len-1);
        
    if(ck_sum == buf[total_len-1]){
        //LOG-FOR-DEBUG
        PR_DEBUG("%-30s","RECEIVE RAW DATA:");
        for(i=0;i<total_len;i++){
            PR_DEBUG_RAW("%02X ",buf[i]&0xFF); 
        }
        PR_DEBUG_RAW("\n");

        ty_fifo_pop(total_len);//correct frame,pop this frame length data
        if(head == 0x66){
            if(get_if_factory_test_close()){
                return;
            }
            app_factory_test_cmd(cmd,&buf[F_DATA],len);
        }else if(head == 0xa5){
            
            ty_uart_cmd_server.receive_cmd(cmd,buf[0x04],&buf[0x07],len);
        }
    }else{//check sum not correct,pop the head length data
        ty_fifo_pop(3);
        return;     
    }
#endif
}





/*************************************File end********************************************/
