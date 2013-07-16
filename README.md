yee_link_light
==============

一个将yeelight接入yeelink平台的小程序for Liunx。   
使用注意：   
1.当然是要确保程序的运行环境能够访问到yeebox盒子。   
2.配置文件yeelight.conf和程序要放在相同路径（任意）。   
3.首次使用切记填写好yeelight.conf配置文件的相关信息,使用到的是yeelink平台的开关。    
4.由于程序写得渣，为了防止程序崩溃啥的，如果需要长期在openwrt上运行，建议在/etc/inittab文件中加上   
::respawn:/root/YeeSer   
其中/root/YeeSer为程序的绝对路径。   
5.demo文件夹下为编译好的适合路由器hg255d在openwrt环境下使用的程序。   
6.代码中使用了来自网友wanli编写的 yeelink API for Linux：http://www.codelifeliwan.com/?p=612   
