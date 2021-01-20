# Reengineer_by_TuyaSDK


## 目的：  
&emsp;&emsp;基于涂鸦蓝牙SDK灯DEMO开发LUTEC摄像头灯。  
## 主要功能：  
&emsp;&emsp;1.手机APP通过蓝牙给摄像头灯的摄像头模组配置WiFi。  
&emsp;&emsp;2.支持蓝牙的标准协议、涂鸦协议和LUTEC自定义协议。  
&emsp;&emsp;3.简单网关透传功能（LUTEC自定义协议）  
&emsp;&emsp;&emsp;&emsp;APP-->Internet-->XM-->Sigmesh  
&emsp;&emsp;4.群组联动（LUTEC自定义协议）  
&emsp;&emsp;5.PIR功能  
&emsp;&emsp;&emsp;&emsp;单/双探头，灵敏度可设。  
&emsp;&emsp;6.CW调光  
&emsp;&emsp;7.场景  

## 特别注意：  
&emsp;&emsp;1.摄像头模组重启需要较长的时间---APP是否等待！  
&emsp;&emsp;2.重启按键位于摄像头模组，当摄像头模组重置时，蓝牙也需要重置。  
&emsp;&emsp;3.  

## 实现路径：  
&emsp;&emsp;A、摄像头模组心跳(wifi状态):    
&emsp;&emsp;&emsp;&emsp;app_common.c-->mesh_main_run()-->lutec_main_loop()  
&emsp;&emsp;B、蓝牙配置wifi & LUTEC自定义协议(蓝牙部分)：    
&emsp;&emsp;&emsp;&emsp;app_common.c-->app_tuya_vendor_light_dp_data()-->lutec_protocol_dp_data()    
&emsp;&emsp;C、简单网关(WiFi透传):    
&emsp;&emsp;&emsp;&emsp;收：app_uart.c-->app_uart_run()-->lutec_xm_data()  
&emsp;&emsp;&emsp;&emsp;转发：
&emsp;&emsp;D、调光：    
&emsp;&emsp;&emsp;&emsp;          
&emsp;&emsp;E、PIR功能：    
&emsp;&emsp;&emsp;&emsp;      
&emsp;&emsp;F、场景：    
&emsp;&emsp;&emsp;&emsp;启动：app_light_control.c-->app_light_ctrl_proc()-->lutec_scenes_start()     
&emsp;&emsp;&emsp;&emsp;运行：lutec_main_loop()-->lutec_scenes_runing()     
&emsp;&emsp;G、存储：    
&emsp;&emsp;&emsp;&emsp;存：app_light_cmd.c-->app_light_ctrl_data_auto_save()-->lutec_save_data_setvariable()      
&emsp;&emsp;&emsp;&emsp;取：app_light_cmd.c-->app_light_ctrl_data_auto_read()-->lutec_read_data_setvariable()    

## 数据流(Interface)：
&emsp;&emsp;Bluetooth下行：Mesh-->tuya_mesh_data_recv_callback()-->app_tuya_vendor_set_light_data()-->lutec_protocol_dp_data()  
&emsp;&emsp;Bluetooth上行：lutec_protocol_dp_data()-->app_light_vendor_data_publish()-->lutec_protocol_dp_data()    
&emsp;&emsp;WiFi下行： 
&emsp;&emsp;WiFi上行：








 


















