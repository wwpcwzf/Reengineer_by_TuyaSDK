/*
 * @Author: wls
 * @email: wuls@tuya.com
 * @LastEditors: wls
 * @file name: light_prod.h
 * @Description: light production test include file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2019-04-26 13:55:40
 * @LastEditTime: 2019-05-08 16:17:44
 */

#ifndef __TY_LIHGT_RHYTHM_H__
#define __TY_LIHGT_RHYTHM_H__

#if (LIGHT_CFG_SUPPORT_RHYTHM == 1)


#define RHYTHM_ENABLE

#include "light_types.h"
#include "math.h"
#include "user_flash.h"

//#include "light_set_color.h"
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define DPID_RHYTHM     30
#define RHYTHM_DATA_OFFSET  (PROD_TEST_DATA_OFFSET + sizeof(LIGHT_APP_DATA_FLASH_T) + 1)

#define MAX_NODE_NUM    8

#define BASE_TIMES      1000

#define SHADE_TIMES     15  //min

#define NORMAL_DP_SAVE_TIME 3000


#pragma pack(1)
typedef struct {
    u8     valid;      
    u8     hour;      
    u8     min;        
    u8     h_per[2];   
    u8     s_per;      
    u8     v_per;     
    u8     bright_per;
    u8     temper_per;
}Node_Param_S;

typedef struct {
    u8     version;   
    u8     onoff;     
    u8     mode;     
    u8     wday;     
    u8     node_cnt;  
    Node_Param_S  node[MAX_NODE_NUM]; 
}RHYTHM_PROTL_S;

typedef struct {
    bool 	uflag;
    u8 ucOnlyOneNode;

    USHORT_T start_bright;
    USHORT_T end_bright;
	USHORT_T cur_bright;
    SHORT_T  step_bright;   

    USHORT_T start_temper;
    USHORT_T end_temper;
	USHORT_T cur_temper;
    SHORT_T  step_temper;  

    UINT_T start_time;   //unit：min
    UINT_T end_time;
	UINT_T cur_time;
    UINT_T step_time;
}RHYTHM_CHANGE_S;


typedef struct
{
    u8 dpid;
    WORD_T len;
    u8 data[72+5];
}RHYTHM_POINT_DATA_S;


typedef enum {
    RHYTHM_FULLCHANGE = 0x00,
    RHYTHM_DIRCHANGE = 0x0f,
}RHYTHM_CTRL_WAY_E;


typedef enum {
    RHYTHM_ON = 1,
    RHYTHM_WAIT,
    RHYTHM_OFF,
    RHYTHM_SET,
    RHYTHM_RESERVE
}RHYTHM_CTRL_STA_E;


/**
 * @brief: return rhythm dp data
 * @param dp_data
 * @retval: LIGHT_OK 
 */
OPERATE_LIGHT ty_light_rhythm_data_get(RHYTHM_POINT_DATA_S *dp_data);

/**
 * @brief: rhythm default data set & save into flash
 * @param {none}
 * @attention: 
 * @retval: none
 */
VOID ty_light_rhythm_default_data_set(VOID);

/**
 * @brief: rhythm data analysis process
 * @param dp_buf  dp_len
 * @retval: none
 */
VOID ty_light_rhythm_analysize(u8 *dp_buf, UINT_T dp_len);

/**
 * @brief: rhythm function init
 * @param {none} 
 * @retval: none
 */
OPERATE_LIGHT ty_light_rhythm_init(VOID);

/**
 * @brief: set light rhythm data
 * @param {IN u8 ucMode --> rhythm adjust CW or RGB}
 * @param {IN u16 usBright --> CW mode, brightness param}
 * @param {IN u16 usTemperature --> CW mode, temperature param} 
 * @param {IN COLOR_HSV_T *Color --> RGB mode, HSV param}
 * @attention: when turn off light, mode bright temperature and rgb will not accept!
 * @retval: OPERATE_LIGHT
 */
OPERATE_LIGHT ty_light_rhythm_ctrl_data_set(IN bool bSwitch, IN u8 ucMode, IN u16 usBright, IN u16 usTemperature, IN COLOR_RGB_T *Color);

/**
 * @brief: get rhythm cfg
 * @param {none}
 * @retval: u8
 */
u8 ty_light_rhythm_ctrl_get_rhythm_mode(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

 
#endif  /* __LIHGT_RHYTHM_H__ */

#endif
