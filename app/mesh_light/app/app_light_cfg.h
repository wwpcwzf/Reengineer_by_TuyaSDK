/*
 * @Author: wls
 * @email: wuls@tuya.com
 * @LastEditors: wls
 * @file name: light_cfg.h
 * @Description: light control support function include file
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2019-04-26 13:55:40
 * @LastEditTime: 2019-10-18 10:53:39
 */

#ifndef __APP_LIHGT_CFG_H__
#define __APP_LIHGT_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * @brief Light frame support function choose
 */
#define LIGHT_CFG_INIT_PARAM_CHECK          0   //if not check param vaild when light init 
#define LIGHT_CFG_PROD_DRIVER_NEED_INIT     0   //if not drive need init in production
#define LIGHT_CFG_PAIRING_BLINK             0   //if blink or breathing(0)when pairing

#define LIGHT_CFG_SUPPORT_RHYTHM            0   //if not support biological rhythm function
#define LIGHT_CFG_3IN1_SAVE                 1   //if not an 3IN1 storage   0:for user  1:for tuya light source and light strip(already releases before 2020/12)

#define LIGHT_CFG_REMOTE_ENABLE             1

#define LIGHT_CFG_UART_ENABLE               1

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* __LIHGT_CFG_H__ */
