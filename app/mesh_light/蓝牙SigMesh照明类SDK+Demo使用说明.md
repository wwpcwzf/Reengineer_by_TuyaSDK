|�汾|��Ҫ���|ʱ��|
|:--:|--|:--:|
|V1.0|�װ�|2020/12/10|

# ע������
## ��������
    a)����ı�����ԭ�к���
    b)����˽����������,��������,����ͿѻЭ�̱���

# ��ܽ���

# DP�����
## mesh��׼����
    �ƶ˲鿴�����Զ�������,app�����ػὫ�Զ�������ת��Ϊmesh��׼����
    mesh��׼����ʹ�ò鿴<Mesh Model Specification>

|Ϳѻ����|mesh����|����|
|:--:|:--:|:--:|
|1|Generic OnOff|����|
|3|Light Lightness Actual|����ֵ|
|4|Light CTL Temperature|��ůֵ|
|5|Light HSL|�ʹ�|

## Ϳѻ��������
    1��30 Ϊ��������ͨ�� DP�������ڿ��Ը��õ������󲿷�Ʒ��Ļ�������DP��ͨ��DPID�������ظ���
    31��50 Ϊ�¹���ͨ�� DP �������ڿ��Ը��õ������󲿷�Ʒ����¹���DP��ͨ��DPID�������ظ���
    50��100ΪƷ�����й��� DP ��������ͨ�ù���DP�޷��������������£���Ʒ�����������Ʒ�����е�DP���ܣ�
    101��200Ϊ�Զ��� DP ���������Զ��巽�����ͻ������Զ��幦�ܣ�
    201��250 Ϊϵͳ DP�������ڵ繤�����е�������Ʒ�߿ɸ��õ�DP������

|Ϳѻ����DP|����|����|
|:--:|:--:|--|
|1|����||
|2|ģʽ|�����л��ƵĹ���ģʽ:�׹�/�ʹ�/����/�����ɶ���|
|3|����ֵ|�׹�ģʽ������|
|4|��ůֵ|�׹�ģʽ��ɫ��|
|5|�ʹ�|�ʹ�ģʽHSVģ��|
|6|����|1.Ϳѻ�Զ��峡��<br>2.�����������8������<br>3.ÿ����������8����Ԫ<br>4.ģʽ:��̬,����,����|
|7|����ʱ|1.��֧�ֱ��ص���ʱ����<br>2.���ϵ��APP�������غ�ʧЧ|
|8|�����ɶ�|APP�������ֽ�HSV���͸��豸��ִ��|
|33|�ϵ����|1.�����͹رնϵ����<br>2.�������ѡ����������ģʽ<br>0x00 ��ʼĬ��ֵ<br>0x01 �ָ�����ֵ<br>0x02 �û�����(HSVBT)|
|34|ͨ������|1.�����͹ر�ͨ������<br>2.������,�ڹص�5s��,�״��ϵ粻������,5s���ٴ��ϵ�Ż�����<br>3.�����о����ϵ���յĵ���|

## ң��������
|Ϳѻ����|Ϳѻ����|����|
|:--:|:--:|--|
|0x81|����ң����|1.���豸�����ң������Ⱥ��<br>2.������ɺ�,ң�������Կ��Ƹõ�|
|0x83|����|ң�������ƵƵ�����|
|0x87|ϲ���ղ�|1.ϲ���ղأ��յ�������ʱ�豸����ǰ��״̬��¼�������γ�һ��ϲ���鲢�ղ�<br>2.ϲ��ִ�У��յ�������ʱ�豸ȡ��֮ǰ�ղص�ϲ���飬�����豸״̬�л�Ϊ�ղص�״̬|

# �ļ�ʹ�ý���
|�ļ���|�ļ�����|ʹ��ע������|
|:--:|:--:|--|
||||

# �ص㺯������
|�ļ���|������|��������|��ע|
|:--:|:--:|--|--|
|app_common.c|void mesh_app_init(void)|����Ӧ�ò��߼��ĳ�ʼ��||
|app_common.c|void mesh_main_run(void)|����Ӧ�ò��߼���������ִ��||
|app_common.c|void mesh_factory_reset(void)|�豸������ǰ����øú���������Ӧ�ò����豸����ʱ���һЩӦ�ò㼶��� flash ����||
|app_common.c|	void app_tuya_mdev_test(uint8_t is_Authorized, uint8_t rssi)|��¼��Ȩʱ�Ĳ���ص�������һ�㲻Ҫ�ģ���Ҫ��||
|app_common.c|	void mesh_state_callback(mesh_state_t stat)|����mesh״̬�����仯ʱ������øú�����֪ͨ��Ӧ�ò㣨�� mesh_state_t ��֪������Щ��Ϣ���ϱ���||
|app_common.c|void tuya_mesh_data_recv_callback(uint16_t src_addr, uint16_t dst_addr, uint32_t opcode, uint8_t *data, uint16_t data_len, uint8_t ttl)|�ֻ� -> �豸�����ݻص��������ǳ���Ҫ��<br>src_addr[in]������Դ��ַ<br>dst_addr[in]������Ŀ�ĵ�ַ<br>opcode[in]��������<br>data[in]������ָ��<br>data_len[in]�����ݳ���<br>ttl[in]������ʣ��ת������||
|app_common.c|void mesh_oem_config_init(void)|��ȡflash/json�����ļ�||
|app_light_control.c|OPERATE_LIGHT app_light_ctrl_proc(void)|�ƿ��ƺ���||
|app_light_control.c|void app_light_ctrl_loop(void)|��void mesh_main_run(void)�����У���ʱ���ȵƿ�����||
|app_light_control.c|OPERATE_LIGHT app_light_real_time_ctrl_proc(void)|ʵʱ�صƣ����������ɶ�||
|app_light_prompt.c|void app_light_ctrl_prompt_start(void)|����ʱָʾ�ƿ���||
|app_light_prompt.c|void app_light_ctrl_prompt_stop(void)|����ʱָʾ�ƹر�||
|app_uart.c|void app_uart_init(void)|���˴��ڳ�ʼ�������� FIFO ��ʼ�����洢��ʼ���������ʼ������mcuͨ�ų�ʼ��||
|app_uart.c|void app_uart_run(void)|��һ�� loop ����������ִ�дӴ��ڶ�ȡ���ݣ����� fifo ��|���⻹������ loop ����������ܵ� loop ��ִ�У�<br>app_factory_test_run();<br>uart_server_run();//����FIFO�е����ݣ���������Ӧ�Ĵ�����|
|app_uart.c|static void app_uart_server_run(void)|���մ���Э����� FIFO �еĴ������ݣ���ȡ��Ч������֡����������֡��𣬷ֱ��͵���<br>�������ݴ���ӿ�app_factory_test_cmd(cmd,&buf[F_DATA],len)<br>��MCUͨ�ŵĴ��ڶԽ����ݴ���ӿ�ty_uart_cmd_server.receive_cmd(u8 cmd, u8 fur, u8 *para, u8 len)|HEAD����A5 5A��ʾ�� MCU���������ݣ���66 AA��ʾ�ǲ�����λ�����������ݡ�|
|app_uart.c|int app_mesh_uart_write(u8 fur, u8 *params, u8 len)|��mesh�����еƵ�����/��Ϣ���͸�MCU|�Ƿ���ȡ����<br>ty_uart_cmd_server_get_txtomcu_flag()<br>MCU���������BT����<br>ty_uart_cmd_server_set_txtomcu_flag(bool flag)|
|app_uart.c|void app_mesh_uart_upload(u8 *params, u8 len, u8 is_group)|MCU͸��DP����||
|app_uart.c|void app_mesh_uart_read(u8 fur, u8 *params, u8 len)|MCU��ȡ�ƹ�����Ϣ������ID����������������ʱ��mesh״̬||
|app_uart.c|void app_mesh_uart_ctl(u8 fur, u8 *params, u8 len)|MCU���Ƶƹ��ܡ�����ID����������������ʱ��BT����||
|tuya_sigmesh_hal.c|void tuya_mesh_node_init(node_info_t *node_info)|mesh �ڵ��ʼ����������������ã�node_info[in]���ڵ���������|�豸��ʼ�����̣��������|
|tuya_sigmesh_hal.c|void tuya_mesh_data_send(uint16_t src_addr, uint16_t dst_addr, uint32_t opcode, uint8_t *data, uint16_t data_len, uint16_t appkey_idx, uint8_t is_rsp)|mesh ���ݷ��� API<br>src_addr[in]������Դ��ַ<br>dst_addr[in]������Ŀ�ĵ�ַ<br>opcode[in]��������<br>data[in]������ָ��<br>data_len[in]�����ݳ���<br>appkey_idx[in]��ʹ�õ�app_key<br>is_rsp[in]���Ƿ�status�ظ�||
|tuya_sigmesh_hal.c|void tuya_primary_ele_addr_set(uint16_t addr, int save)|�����豸�� unicast addr<br>addr[in]���豸��ַ<br>save[in]���Ƿ�flash����||
|tuya_sigmesh_hal.c|uint16_t get_primary_ele_addr(void)|��ȡ�豸�� unicast addr||
|tuya_sigmesh_hal.c|void tuya_mesh_devkey_set(uint8_t *key)|���������豸��devkey||
|tuya_sigmesh_hal.c|void tuya_mesh_network_reset_with_restore(uint16_t restore_time_s)|���豸�Ƴ����粢�ָ�������״̬�������ó�ʱʱ�䣬��ʱ��ָ����Ƴ�ǰ������||
|tuya_sigmesh_hal.c|void tuya_mesh_rf_power_set(TUYA_RF_Power level)|���÷��书��||
|tuya_sigmesh_hal.c|void tuya_mesh_uuid_set(uint8_t *uuid)|uuid ���½ӿ�||
|tuya_sigmesh_hal.c|void tuya_gatt_adv_beacon_enable(uint8_t enable)|�㲥 beacon ʹ��||
|tuya_sigmesh_hal.c|uint8_t get_if_prov_success(void)|��ȡ�豸����״̬||
|fast_provision_model.c|int mesh_reset_network(u8 provision_enable, u16 recover_time_s)|���豸�Ƴ����粢�ָ�������״̬||
|tuya_node_init.c|void tuya_pid_set(uint8_t *pid)|PID ���½ӿڣ���������Ĭ������Ȩ��PID|8�ֽڳ��ȵ�PID�ַ���|
|tuya_node_init.c|void app_tuya_mesh_category_set(uint16_t mesh_category)|mesh �豸����ֵ����||
|hal_hw_timer.c|OPERATE_LIGHT ty_light_basis_hw_timer_start(IN u32 uiCycleUs, IN void* pCallback)|Ӳ����ʱ�������ڵƹ⽥������||
|hal_hw_timer.c|OPERATE_LIGHT ty_light_basis_hw_timer_stop(void)|�ر�Ӳ����ʱ�������ڵƹ⽥������||
|ty_light_basis_sw_timer.c|OPERATE_LIGHT ty_light_basis_sw_timer_start(IN u8 ucTimerID, IN u32 uiCycleMs, IN void* pCallback);|�����ʱ�������ڵƹ��������||
|ty_light_basis_sw_timer.c|OPERATE_LIGHT ty_light_basis_sw_timer_stop(IN u8 ucTimerID);|�ر������ʱ�������ڵƹ��������||
|ty_light_basis_sw_timer.c|void ty_light_basis_sw_timer_handler(void);|����ʱ����||
|ty_light_driver_set.c|OPERATE_LIGHT ty_light_driver_set_init(IN DRIVER_CONFIG_T *pLightConfig);|��������ʼ����������ģʽ:<br>PwmInit<br>Sm2135Init<br>tSm16726bInit||
|ty_light_gradual.c|void ty_light_gradual_hw_timer_handler(void);|�ƹ⽥�䶨ʱ����||
|ty_light_remote.c|void ty_light_remote_dp_data(u8 * par, int par_len);|ң����DP����ƴ���||
|ty_light_scene.c|void ty_light_scene_cmd_sync(u8 uint_num)|����ͬ��||
|ty_light_scene.c|void ty_light_scene_ctrl_change_start(IN u32 uiChangeTimeMs)|��ʱʱ���ʼ�����ı�||
|ty_light_scene.c|OPERATE_LIGHT ty_light_scene_ctrl_change(OUT bool *pCycleEnable, OUT u32 *pCycleTimeMs)|������������Ϣת��ΪRGBCW�����ֵ||

# jsonʹ�ý���
json����
|���|json��|����|�ͻ���Ķ�|����|
|:--:|:--:|:--:|:--:|--|
|json head|name|�̼���ʶ��|��|1.������Ϳѻƽ̨�����̼���ʶ��<br>2.�ϴ��Ĺ̼�������Ϳѻƽ̨һ��|
|json head|description|���ù���|��|�����������ù̼�|
|json head|version|�̼��汾|��|��ʽx.x|
|json head|ic|оƬ�ͺ�|��|tlsr825x|
|json head|hardware|Ӳ��ģ��|��|TYBT3L|
|json head|log|��ӡ������Ϣ|��|1.�����ǿ���Ϊ1,��log��Ϣ���<br>2.��Ʒ�̼���������Ϊ0|
|json head|oem|�̼���ʽ|��|����Ϊ1|
|json head|json_config|json����|��|����Ϊ0|
|json head|kind|�豸����|��|Ĭ�ϼ���|
|json head|pid|pid����|��|������д�̼�key����|
|json head|vendorid|Ʒ����Ϣ|��|1.һ·��:1011<br>2.��·��:1012<br>3.��·��:1013<br>4.��·��:1014<br>5.��·��:1015|
||Jsonver|json���ð汾|��|Ĭ�ϼ���|
||category|�豸����|��|��kind����һ��|
||module|ģ��ѡ��|��|1,BT8C<br>2.��BT8Cģ����BT3L|
||cmod|����ѡ��|��|1.һ·��:c<br>2.��·��:cw<br>3.��·��:rgb<br>4.��·��:rgbc<br>5.��·��:rgbcw|
||dmod|����ѡ��|��|0:PWM����<br>1:SM16726B<br>2:SM2135E|
||cwtype|�׹����������ʽ|��|0:CW - ���/ů��<br>1:CCT - ����/ɫ��|
||onoffmode|���ؽ���|��|0:����ʱ�н���<br>1:����ʱ�޽���|
||pmemory|�ϵ����|��|0:�޶ϵ����<br>1:�жϵ����|
||defcolor|�����ɹ�����ɫ|��|�ʹ��ѡ:r/g/b<br>�׹��ѡ:c|
||defbright|�����ɹ�������|��|��Χ��10~100|
||deftemp|�����ɹ���ɫ��|��|defcolorΪcʱ��Ч<br>��Χ��0~100|
||cwmaxp|��ů��������|��|Ĭ��Ϊ100<br>��Χ��100~200����ࣺ10|
||brightmin|�׹�������Сֵ|��|��Χ��1~100����ࣺ1|
||brightmax|�׹��������ֵ|��|��Χ��1~100����ࣺ1|
||colormin|�ʹ�������Сֵ|��|��Χ��1~100����ࣺ1|
||colormax|�ʹ��������ֵ|��|��Χ��1~100����ࣺ1|
||wfcfg|�״�����������ʽ|��||
||rstmode|����������ʽ|��|Ĭ��Ϊ0|
||rstnum|ͨ�ϵ縴λ����|��|��Χ��3~10����ࣺ1|
||rstcor|����ʱ������ɫ|��|�ʹ��ѡ:r/g/b<br>�׹��ѡ:c|
||rstbr|����ʱ��������|��|��Χ��10~100|
||rsttemp|����ʱ����ɫ��|��|rstcorΪcʱ��Ч<br>��Χ��0~100|
||pairt|�������ѵ�ʱ��|��|��Χ��6~600<br>ע:��������ʱ,ʱ�佨��Ϊ6,�����ڼ��Ӱ��GATT����|
||notdisturb|����ģʽ|��|0:�ر�<br>1:����|
|PWM|pmwhz|PWM Ƶ��|��|��Χ��500~20000����ࣺ100|
|PWM|r_pin/g_pin/<br>b_pin/c_pin/<br>w_pin|rgbcw����|��|��д0~14,���Ŷ�Ӧ��ϵ����<br>0:GPIO_PB1<br>1:GPIO_PB7<br>2:GPIO_PB5<br>3:GPIO_PB4<br>4:GPIO_PA0<br>6:GPIO_PC0<br>7:GPIO_PC2<br>8:GPIO_PC3<br>9:GPIO_PD2<br>10:GPIO_PD7<br>11:GPIO_PC4<br>12:GPIO_PB0<br>13:GPIO_PC5<br>14:GPIO_PC1|
|PWM|r_lv/g_lv/<br>b_lv/c_lv/<br>w_lv|��Ч��ƽ|��|Ĭ��Ϊ1<br>�������ű��뱣��һ��<br>1:�ߵ�ƽ����<br>0:�͵�ƽ����|
|IICоƬ����|iicr/iicg/iicb<br>/iicc/iicw|rgbcwͨ��|��|����Ϊ01234|
|IICоƬ����|iicscl|I2C SCL �ܽź�|��|IIC��������|
|IICоƬ����|iicsda|I2C DATA �ܽź�|��|IIC��������|
|IICоƬ����|ctrl_pin|��������|��|SM16726B����|
|IICоƬ����|ctrl_lv|��ƽ��������|��|SM16726B����<br>1:�ߵ�ƽ��Ч<br>0:�͵�ƽ��Ч|
|IICоƬ����|campere|�ʹ�ģʽ��·������|��|sm2135E��������<br>��Χ��10~45����ࣺ5��Ĭ��ֵ��20|
|IICоƬ����|wampere|�׹�ģʽ��·������|��|sm2135E��������<br>��Χ��10~80����ࣺ5��Ĭ��ֵ��30|
||crc|У��|��|����Ķ�,��У��|

# ���Լ���
## �����(��̩��Ϊ��)
### IDE��װ
Telink�ٷ���̳��ҳ��http://wiki.telink-semi.cn/wiki/IDE-and-Tools/IDE-for-TLSR8-Chips/ -> Telink IDE�����ɿ���������-> ��ָ�����а�װ

�� doc\tools\jq-win64.exe ���� C:\TelinkSDK\bin\

������·������ϵͳ���������У�

C:\TelinkSDK\opt\Vim\vim73\;	
C:\TelinkSDK\opt\tc32\bin\;	
C:\TelinkSDK\bin\;	
C:\TelinkSDK\opt\tc32\tools\;

### ��д�������ְ�װ
Telink�ٷ���̳��ҳ��http://wiki.telink-semi.cn/wiki/IDE-and-Tools/Burning-and-Debugging-Tools-for-all-Series/ -> Burning and Debugging Tools (BDT) -> ���ؽ�ѹ����

### git��װ
�� https://git-scm.com/download/win ���� git-for-win ����װ������Ϥ���˽���ȫ������Ĭ�ϰ�װ,����������Ѿ���git-bash֮��Ŀ�������sh�ű���������Բ��ð�װ��

## ����
### build
���� app/mesh_common/_build �е� run.sh �ű�������ʵ�ֱ��롢��¼�������� _build �ļ�������common/tools �����У��޸���Ӧ�ļ����ƣ� bash cmake.sh mesh_light tlsr825x_smesh light_profile ���� _build �ļ���

```
bash run.sh build/flash [app_config.json]
```

�ýű��Ὣ [app_config.json] ת��Ϊ _build/base_oem_config.h, �����д����ĺ궨�壬������ͬһ��Ӧ�ô��룬�����ɲ�ͬ��Ӧ�ó����磺ֻ��Ҫ�Ķ����ɹ̼������֡��汾�š�PID����Ϣʱ������Ҫ�Ķ����룬ֻ��Ҫ�Ķ��� json �����ļ�����

������ͨ���޸� [app_config.json] ������ͻ����󣬾�����Ҫ�޸�APP���룬���������Ĺ̼�������С�����ǲ���ͨ���޸� [app_config.json]����ͻ�����ģ�������ø���һ�����Ƶ� app_name ���иĶ�������һ�����������������������޸Ĳ�ͬ�� app�����Ƽ����Ǽ�ǿ [app_config.json] ������
```
  $ cd app/mesh_common/_build

  $ bash run.sh build 5_bt3l-cfg_V3.1.json 
```
### flash
1)����д����SWM�����뿪�����SWS������������д��ͨ�� USB ���ӵ������ϣ������嵥�����磨���ֹ��أ���

2���� Telink ��д�������� (BTD)��ѡ�� 8258 оƬ����� SWS ��ʼ������д��������д��������¼ 8258 �ͺ�оƬ������ֻ��Ҫ SWS һ�μ��ɣ���

3���� Git Bash �����룺tcdb.exe rst��������Ľ������������д�����Ѿ��ɹ����ӵ���д�����ϣ�
```
  $ tcdb.exe rst
    Slave MCU Reset
```

����׼���������ú󣬿���ֱ������ run.sh �� bin �ļ���¼�������壺
```
$ bash run.sh flash 5_bt3l-cfg_V3.1.json 
```
## ���� PID ����Ȩ��
��Ȩ���Ҷ�Ӧ�Ĳ�Ʒ���������豸������Ȩ��������ʹ�á�

���� PID ��

1)��¼Ϳѻ����ƽ̨��https://iot.tuya.com/��������Ʒ��

2)����ѡ���Դ������ Mesh(SIG) ���ʵ���· (RGBCW)_SIG �������Ʒ���ƣ�������Ʒ��

3)��ӹ��ܣ�ȷ����APP������ã�ѡ��ģ�壻

4)Ӳ�����ԣ�ѡ����Ӧ����ģ��

5)�ƶ�����

ע���轫�����ߵ� �ƶ����� �ⲽ��PID �Ĺ��ܲ���ȫʵ�֣����򽫳���һЩС���⡣

## json λ�÷��ù̼� key���߲�Ʒ PID
���𣺷��ù̼� key ���Զ�Ӧ��� PID����Ӧ�ж��ֲ�Ʒ�����ò�Ʒ PID ֻ�ܶ�Ӧһ�ֲ�Ʒ��