VER_FILE=version.in
echo -n " .equ BUILD_VERSION, " > $VER_FILE
echo 0x3739 >> $VER_FILE
 
CONFIG_FILE=base_oem_config.h
echo "//-------------------------------------------"> $CONFIG_FILE
echo "//common define">> $CONFIG_FILE
echo "//-------------------------------------------">> $CONFIG_FILE
echo "#define     FW_VERSION                \"9.7\"" >> $CONFIG_FILE
echo "#define     FW_VERSION_HEX            0x3739" >> $CONFIG_FILE
echo "#define     BUILD_TIME                \"2021-01-12-20:03:47\"" >> $CONFIG_FILE
echo "#define     BUILD_FIRMNAME            \"oem_tlsr8250_lightcfg_pwm_ty\"" >> $CONFIG_FILE
echo "#define     MESH_PID                  \"keyd9k4q\"" >> $CONFIG_FILE
echo "#define     CONFIG_LOG_ON             0" >> $CONFIG_FILE
echo "#define     CONFIG_OEM_ON             1" >> $CONFIG_FILE
echo "#define     JSON_CONFIG_ON            1" >> $CONFIG_FILE
echo "#define     LOCAL_CONTROL_ON          0" >> $CONFIG_FILE
echo "#define     KIND_ID                   0x1015" >> $CONFIG_FILE
echo "#define     POWER_RESET_CNT           0" >> $CONFIG_FILE
echo "#define     POWER_RESET_TIME          5" >> $CONFIG_FILE
echo "#define     POWER_RESET_RECOVER_TIME  600" >> $CONFIG_FILE
echo "#define     TY_BT_MODULE              TYBT3L" >> $CONFIG_FILE
echo "            #define     TYBT3L        0" >> $CONFIG_FILE
echo "            #define     TYBT8C        1" >> $CONFIG_FILE
echo "#define     IC_TLSR825x" >> $CONFIG_FILE
echo "" >> $CONFIG_FILE
echo "//-------------------------------------------">> $CONFIG_FILE
echo "//module light define">> $CONFIG_FILE
echo "//-------------------------------------------">> $CONFIG_FILE
echo "#define DEFAULT_CONFIG \"{Jsonver:1.1.8,category:1015,module:BT3L,cmod:rgbcw,dmod:0,cwtype:0,\
onoffmode:0,pmemory:1,defcolor:c,defbright:100,deftemp:100,\
cwmaxp:100,brightmin:10,brightmax:100,colormin:10,colormax:100,\
wfcfg:spcl_auto,rstmode:0,rstnum:3,remdmode:null,rstcor:c,rstbr:50,\
rsttemp:100,pwmhz:1000,pairt:6,notdisturb:0,prodagain:0,cagt:20,\
wt:20,rgbt:10,colorpfun:0,colormaxp:200,r_pin:3,r_lv:1,g_pin:8,\
g_lv:1,b_pin:9,b_lv:1,c_pin:2,c_lv:1,w_pin:7,w_lv:1,\
iicr:0,iicg:1,iicb:2,iicc:3,iicw:4,iicscl:0,iicsda:13,\
ctrl_pin:12,ctrl_lv:1,campere:20,wampere:30,wr:100,wg:70,wb:75,\
gr:80,gg:60,gb:60,crc:111,}\" ">> $CONFIG_FILE
echo "" >> $CONFIG_FILE
grep -n "DEFAULT_CONFIG" $CONFIG_FILE | cut -f1 -d: | xargs -I {} sed -i "{}s:,*\:null,:,:g" $CONFIG_FILE
