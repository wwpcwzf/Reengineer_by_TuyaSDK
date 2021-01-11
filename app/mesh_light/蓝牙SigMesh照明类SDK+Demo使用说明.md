|版本|主要变更|时间|
|:--:|--|:--:|
|V1.0|首版|2020/12/10|

# 注意事项
## 控制命令
    a)不许改变命令原有含义
    b)不许私自增加命令,如需增加,需与涂鸦协商报备

# 框架介绍

# DP点介绍
## mesh标准命令
    云端查看还是自定义命令,app和网关会将自定义命令转换为mesh标准命令
    mesh标准命令使用查看<Mesh Model Specification>

|涂鸦定义|mesh定义|名称|
|:--:|:--:|:--:|
|1|Generic OnOff|开关|
|3|Light Lightness Actual|亮度值|
|4|Light CTL Temperature|冷暖值|
|5|Light HSL|彩光|

## 涂鸦定义命令
    1～30 为基础功能通用 DP，适用于可以复用到其他大部分品类的基础功能DP，通用DPID不可以重复；
    31～50 为新功能通用 DP ，适用于可以复用到其他大部分品类的新功能DP，通用DPID不可以重复；
    50～100为品类特有功能 DP ，适用于通用功能DP无法满足需求的情况下，各品类自主定义的品类特有的DP功能；
    101～200为自定义 DP ，适用于自定义方案，客户新增自定义功能；
    201～250 为系统 DP，适用于电工、传感等其他产品线可复用的DP能力。

|涂鸦定义DP|名称|含义|
|:--:|:--:|--|
|1|开关||
|2|模式|用于切换灯的工作模式:白光/彩光/场景/音乐律动等|
|3|亮度值|白光模式的亮度|
|4|冷暖值|白光模式的色温|
|5|彩光|彩光模式HSV模型|
|6|场景|1.涂鸦自定义场景<br>2.可增加最多至8个场景<br>3.每个场景至多8个单元<br>4.模式:静态,渐变,跳变|
|7|倒计时|1.仅支持本地倒计时开关<br>2.断上电或APP操作开关后即失效|
|8|音乐律动|APP依据音乐将HSV发送给设备端执行|
|33|断电记忆|1.开启和关闭断电记忆<br>2.开启后可选择以下三种模式<br>0x00 初始默认值<br>0x01 恢复记忆值<br>0x02 用户定制(HSVBT)|
|34|通电勿扰|1.开启和关闭通电勿扰<br>2.开启后,在关灯5s后,首次上电不会亮灯,5s内再次上电才会亮灯<br>3.用于有经常断电风险的地区|

## 遥控器命令
|涂鸦命令|涂鸦名称|含义|
|:--:|:--:|--|
|0x81|订阅遥控器|1.将设备添加入遥控器的群组<br>2.订阅完成后,遥控器可以控制该灯|
|0x83|亮度|遥控器控制灯的亮度|
|0x87|喜好收藏|1.喜好收藏：收到该命令时设备将当前的状态记录下来，形成一个喜好组并收藏<br>2.喜好执行：收到该命令时设备取出之前收藏的喜好组，并将设备状态切换为收藏的状态|

# 文件使用介绍
|文件名|文件介绍|使用注意事项|
|:--:|:--:|--|
||||

# 重点函数介绍
|文件名|函数名|函数作用|备注|
|:--:|:--:|--|--|
|app_common.c|void mesh_app_init(void)|用于应用层逻辑的初始化||
|app_common.c|void mesh_main_run(void)|用于应用层逻辑的周期性执行||
|app_common.c|void mesh_factory_reset(void)|设备被重置前会调用该函数，用于应用层在设备重置时清空一些应用层级别的 flash 数据||
|app_common.c|	void app_tuya_mdev_test(uint8_t is_Authorized, uint8_t rssi)|烧录授权时的产测回调函数，一般不要改，不要动||
|app_common.c|	void mesh_state_callback(mesh_state_t stat)|各种mesh状态发生变化时，会调用该函数，通知给应用层（看 mesh_state_t 可知道有哪些信息会上报）||
|app_common.c|void tuya_mesh_data_recv_callback(uint16_t src_addr, uint16_t dst_addr, uint32_t opcode, uint8_t *data, uint16_t data_len, uint8_t ttl)|手机 -> 设备的数据回调函数（非常重要）<br>src_addr[in]：数据源地址<br>dst_addr[in]：数据目的地址<br>opcode[in]：命令字<br>data[in]：数据指针<br>data_len[in]：数据长度<br>ttl[in]：数据剩余转发次数||
|app_common.c|void mesh_oem_config_init(void)|读取flash/json配置文件||
|app_light_control.c|OPERATE_LIGHT app_light_ctrl_proc(void)|灯控制函数||
|app_light_control.c|void app_light_ctrl_loop(void)|在void mesh_main_run(void)中运行，定时调度灯控任务||
|app_light_control.c|OPERATE_LIGHT app_light_real_time_ctrl_proc(void)|实时控灯，用于音乐律动||
|app_light_prompt.c|void app_light_ctrl_prompt_start(void)|配网时指示灯开启||
|app_light_prompt.c|void app_light_ctrl_prompt_stop(void)|配网时指示灯关闭||
|app_uart.c|void app_uart_init(void)|除了串口初始化，还有 FIFO 初始化、存储初始化、产测初始化、与mcu通信初始化||
|app_uart.c|void app_uart_run(void)|是一个 loop 函数，不断执行从串口读取数据，放入 fifo 中|此外还有两个 loop 函数在这个总的 loop 中执行：<br>app_factory_test_run();<br>uart_server_run();//解析FIFO中的数据，并调用相应的处理函数|
|app_uart.c|static void app_uart_server_run(void)|按照串口协议解析 FIFO 中的串口数据，获取有效的数据帧，根据数据帧类别，分别送到：<br>产测数据处理接口app_factory_test_cmd(cmd,&buf[F_DATA],len)<br>与MCU通信的串口对接数据处理接口ty_uart_cmd_server.receive_cmd(u8 cmd, u8 fur, u8 *para, u8 len)|HEAD中是A5 5A表示是 MCU发来的数据；是66 AA表示是产测上位机发来的数据。|
|app_uart.c|int app_mesh_uart_write(u8 fur, u8 *params, u8 len)|将mesh网络中灯的命令/信息发送给MCU|是否发送取决于<br>ty_uart_cmd_server_get_txtomcu_flag()<br>MCU发送命令给BT设置<br>ty_uart_cmd_server_set_txtomcu_flag(bool flag)|
|app_uart.c|void app_mesh_uart_upload(u8 *params, u8 len, u8 is_group)|MCU透传DP数据||
|app_uart.c|void app_mesh_uart_read(u8 fur, u8 *params, u8 len)|MCU读取灯功能信息、场景ID、完整场景、倒计时、mesh状态||
|app_uart.c|void app_mesh_uart_ctl(u8 fur, u8 *params, u8 len)|MCU控制灯功能、场景ID、完整场景、倒计时，BT重置||
|tuya_sigmesh_hal.c|void tuya_mesh_node_init(node_info_t *node_info)|mesh 节点初始化，相关能力的配置，node_info[in]：节点能力设置|设备初始化流程，必须调用|
|tuya_sigmesh_hal.c|void tuya_mesh_data_send(uint16_t src_addr, uint16_t dst_addr, uint32_t opcode, uint8_t *data, uint16_t data_len, uint16_t appkey_idx, uint8_t is_rsp)|mesh 数据发送 API<br>src_addr[in]：数据源地址<br>dst_addr[in]：数据目的地址<br>opcode[in]：命令字<br>data[in]：数据指针<br>data_len[in]：数据长度<br>appkey_idx[in]：使用的app_key<br>is_rsp[in]：是否status回复||
|tuya_sigmesh_hal.c|void tuya_primary_ele_addr_set(uint16_t addr, int save)|设置设备的 unicast addr<br>addr[in]：设备地址<br>save[in]：是否flash记忆||
|tuya_sigmesh_hal.c|uint16_t get_primary_ele_addr(void)|获取设备的 unicast addr||
|tuya_sigmesh_hal.c|void tuya_mesh_devkey_set(uint8_t *key)|主动更新设备的devkey||
|tuya_sigmesh_hal.c|void tuya_mesh_network_reset_with_restore(uint16_t restore_time_s)|将设备移除网络并恢复到配网状态，且配置超时时间，超时后恢复到移除前的网络||
|tuya_sigmesh_hal.c|void tuya_mesh_rf_power_set(TUYA_RF_Power level)|设置发射功率||
|tuya_sigmesh_hal.c|void tuya_mesh_uuid_set(uint8_t *uuid)|uuid 更新接口||
|tuya_sigmesh_hal.c|void tuya_gatt_adv_beacon_enable(uint8_t enable)|广播 beacon 使能||
|tuya_sigmesh_hal.c|uint8_t get_if_prov_success(void)|获取设备配网状态||
|fast_provision_model.c|int mesh_reset_network(u8 provision_enable, u16 recover_time_s)|将设备移除网络并恢复到配网状态||
|tuya_node_init.c|void tuya_pid_set(uint8_t *pid)|PID 更新接口，不调用则默认用授权的PID|8字节长度的PID字符串|
|tuya_node_init.c|void app_tuya_mesh_category_set(uint16_t mesh_category)|mesh 设备能力值配置||
|hal_hw_timer.c|OPERATE_LIGHT ty_light_basis_hw_timer_start(IN u32 uiCycleUs, IN void* pCallback)|硬件定时任务，用于灯光渐变任务||
|hal_hw_timer.c|OPERATE_LIGHT ty_light_basis_hw_timer_stop(void)|关闭硬件定时任务，用于灯光渐变任务||
|ty_light_basis_sw_timer.c|OPERATE_LIGHT ty_light_basis_sw_timer_start(IN u8 ucTimerID, IN u32 uiCycleMs, IN void* pCallback);|软件定时任务，用于灯光控制任务||
|ty_light_basis_sw_timer.c|OPERATE_LIGHT ty_light_basis_sw_timer_stop(IN u8 ucTimerID);|关闭软件定时任务，用于灯光控制任务||
|ty_light_basis_sw_timer.c|void ty_light_basis_sw_timer_handler(void);|处理定时任务||
|ty_light_driver_set.c|OPERATE_LIGHT ty_light_driver_set_init(IN DRIVER_CONFIG_T *pLightConfig);|灯驱动初始化，有三种模式:<br>PwmInit<br>Sm2135Init<br>tSm16726bInit||
|ty_light_gradual.c|void ty_light_gradual_hw_timer_handler(void);|灯光渐变定时任务||
|ty_light_remote.c|void ty_light_remote_dp_data(u8 * par, int par_len);|遥控器DP点控制处理||
|ty_light_scene.c|void ty_light_scene_cmd_sync(u8 uint_num)|场景同步||
|ty_light_scene.c|void ty_light_scene_ctrl_change_start(IN u32 uiChangeTimeMs)|定时时间后开始场景改变||
|ty_light_scene.c|OPERATE_LIGHT ty_light_scene_ctrl_change(OUT bool *pCycleEnable, OUT u32 *pCycleTimeMs)|将场景控制信息转变为RGBCW所需的值||

# json使用介绍
json介绍
|类别|json名|名称|客户需改动|含义|
|:--:|:--:|:--:|:--:|--|
|json head|name|固件标识名|是|1.首先在涂鸦平台创建固件标识名<br>2.上传的固件名称与涂鸦平台一致|
|json head|description|配置功能|可|仅用于描述该固件|
|json head|version|固件版本|是|形式x.x|
|json head|ic|芯片型号|否|tlsr825x|
|json head|hardware|硬件模块|否|TYBT3L|
|json head|log|打印调试信息|可|1.调试是可以为1,将log信息输出<br>2.成品固件必须设置为0|
|json head|oem|固件形式|否|建议为1|
|json head|json_config|json可配|否|必须为0|
|json head|kind|设备能力|否|默认即可|
|json head|pid|pid名称|是|建议填写固件key名称|
|json head|vendorid|品类信息|是|1.一路灯:1011<br>2.两路灯:1012<br>3.三路灯:1013<br>4.四路灯:1014<br>5.五路灯:1015|
||Jsonver|json配置版本|否|默认即可|
||category|设备能力|是|与kind保持一致|
||module|模块选型|是|1,BT8C<br>2.非BT8C模块填BT3L|
||cmod|灯类选型|是|1.一路灯:c<br>2.两路灯:cw<br>3.三路灯:rgb<br>4.四路灯:rgbc<br>5.五路灯:rgbcw|
||dmod|驱动选型|是|0:PWM驱动<br>1:SM16726B<br>2:SM2135E|
||cwtype|白光调节驱动方式|是|0:CW - 冷光/暖光<br>1:CCT - 亮度/色温|
||onoffmode|开关渐变|是|0:开关时有渐变<br>1:开关时无渐变|
||pmemory|断电记忆|是|0:无断电记忆<br>1:有断电记忆|
||defcolor|配网成功后颜色|是|彩光可选:r/g/b<br>白光可选:c|
||defbright|配网成功后亮度|是|范围：10~100|
||deftemp|配网成功后色温|是|defcolor为c时有效<br>范围：0~100|
||cwmaxp|冷暖混光最大功率|是|默认为100<br>范围：100~200，间距：10|
||brightmin|白光亮度最小值|是|范围：1~100，间距：1|
||brightmax|白光亮度最大值|是|范围：1~100，间距：1|
||colormin|彩光亮度最小值|是|范围：1~100，间距：1|
||colormax|彩光亮度最大值|是|范围：1~100，间距：1|
||wfcfg|首次配网触发方式|是||
||rstmode|触发配网方式|否|默认为0|
||rstnum|通断电复位次数|是|范围：3~10，间距：1|
||rstcor|配网时提醒颜色|是|彩光可选:r/g/b<br>白光可选:c|
||rstbr|配网时提醒亮度|是|范围：10~100|
||rsttemp|配网时提醒色温|是|rstcor为c时有效<br>范围：0~100|
||pairt|配网提醒的时间|是|范围：6~600<br>注:呼吸提醒时,时间建议为6,呼吸期间会影响GATT配网|
||notdisturb|勿扰模式|是|0:关闭<br>1:开启|
|PWM|pmwhz|PWM 频率|是|范围：500~20000；间距：100|
|PWM|r_pin/g_pin/<br>b_pin/c_pin/<br>w_pin|rgbcw引脚|是|填写0~14,引脚对应关系如下<br>0:GPIO_PB1<br>1:GPIO_PB7<br>2:GPIO_PB5<br>3:GPIO_PB4<br>4:GPIO_PA0<br>6:GPIO_PC0<br>7:GPIO_PC2<br>8:GPIO_PC3<br>9:GPIO_PD2<br>10:GPIO_PD7<br>11:GPIO_PC4<br>12:GPIO_PB0<br>13:GPIO_PC5<br>14:GPIO_PC1|
|PWM|r_lv/g_lv/<br>b_lv/c_lv/<br>w_lv|有效电平|是|默认为1<br>所有引脚必须保持一致<br>1:高电平点亮<br>0:低电平点亮|
|IIC芯片驱动|iicr/iicg/iicb<br>/iicc/iicw|rgbcw通道|是|配置为01234|
|IIC芯片驱动|iicscl|I2C SCL 管脚号|是|IIC驱动必填|
|IIC芯片驱动|iicsda|I2C DATA 管脚号|是|IIC驱动必填|
|IIC芯片驱动|ctrl_pin|控制引脚|是|SM16726B必填|
|IIC芯片驱动|ctrl_lv|电平控制配置|是|SM16726B必填<br>1:高电平有效<br>0:低电平有效|
|IIC芯片驱动|campere|彩光模式单路最大电流|是|sm2135E驱动必填<br>范围：10~45，间距：5，默认值：20|
|IIC芯片驱动|wampere|白光模式单路最大电流|是|sm2135E驱动必填<br>范围：10~80，间距：5，默认值：30|
||crc|校验|否|无需改动,不校验|

# 调试技巧
## 环境搭建(以泰凌为例)
### IDE安装
Telink官方论坛主页：http://wiki.telink-semi.cn/wiki/IDE-and-Tools/IDE-for-TLSR8-Chips/ -> Telink IDE（集成开发环境）-> 按指导进行安装

将 doc\tools\jq-win64.exe 放入 C:\TelinkSDK\bin\

将下面路径加入系统环境变量中：

C:\TelinkSDK\opt\Vim\vim73\;	
C:\TelinkSDK\opt\tc32\bin\;	
C:\TelinkSDK\bin\;	
C:\TelinkSDK\opt\tc32\tools\;

### 烧写调试助手安装
Telink官方论坛主页：http://wiki.telink-semi.cn/wiki/IDE-and-Tools/Burning-and-Debugging-Tools-for-all-Series/ -> Burning and Debugging Tools (BDT) -> 下载解压即可

### git安装
从 https://git-scm.com/download/win 下载 git-for-win 并安装（不熟悉的人建议全部采用默认安装,如果电脑上已经有git-bash之类的可以运行sh脚本的软件可以不用安装）

## 上手
### build
利用 app/mesh_common/_build 中的 run.sh 脚本，可以实现编译、烧录：（如无 _build 文件，则在common/tools 中运行（修改相应文件名称） bash cmake.sh mesh_light tlsr825x_smesh light_profile 生成 _build 文件）

```
bash run.sh build/flash [app_config.json]
```

该脚本会将 [app_config.json] 转变为 _build/base_oem_config.h, 其中有大量的宏定义，用于让同一个应用代码，能生成不同的应用程序（如：只需要改动生成固件的名字、版本号、PID等信息时，不需要改动代码，只需要改动该 json 配置文件）。

凡是能通过修改 [app_config.json] 能满足客户需求，尽量不要修改APP代码，这样产出的固件风险性小；凡是不能通过修改 [app_config.json]满足客户需求的，建议采用复制一个相似的 app_name 进行改动开发。一般情况不建议产生大量做简单修改不同的 app，而推荐考虑加强 [app_config.json] 能力。
```
  $ cd app/mesh_common/_build

  $ bash run.sh build 5_bt3l-cfg_V3.1.json 
```
### flash
1)将烧写器的SWM引脚与开发板的SWS引脚相连，烧写器通过 USB 连接到电脑上，开发板单独供电（保持共地）；

2）打开 Telink 烧写调试助手 (BTD)，选择 8258 芯片，点击 SWS 初始配置烧写器（让烧写器可以烧录 8258 型号芯片，往往只需要 SWS 一次即可）：

3）在 Git Bash 中输入：tcdb.exe rst看到下面的结果，表明待烧写板子已经成功连接到烧写板子上：
```
  $ tcdb.exe rst
    Slave MCU Reset
```

上面准备工作做好后，可以直接利用 run.sh 将 bin 文件烧录到开发板：
```
$ bash run.sh flash 5_bt3l-cfg_V3.1.json 
```
## 申请 PID 和授权码
授权码找对应的产品经理，所有设备必须授权才能配网使用。

申请 PID ：

1)登录涂鸦智能平台（https://iot.tuya.com/）创建产品；

2)例如选择光源、蓝牙 Mesh(SIG) 、彩灯五路 (RGBCW)_SIG ，输入产品名称，创建产品；

3)添加功能，确定，APP面板配置，选择模板；

4)硬件调试，选择相应开发模组

5)云端配置

注：需将流程走到 云端配置 这步，PID 的功能才完全实现，否则将出现一些小问题。

## json 位置放置固件 key或者产品 PID
区别：放置固件 key 可以对应多个 PID，对应有多种产品；放置产品 PID 只能对应一种产品。