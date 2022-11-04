# Linux

[TOC]





## 1.文件权限

第一列	d: 文件夹	-：文件		l：链接









### 运行级别：

* 0 - 关机级别（切忌默认运行级别设置为0）
* 1 - 单用户级别
* 2 - 多用户级别 （不带NFS，NetWork File System）
* 3 - 完全多用户模式
* 4 - 未被使用
* 5 - 完整图形化界面模式 
* 6 - 重启级别

```
init 0   关机
init 3	切换到不带桌面的模式
init 6 	重启
init 5	切换到图形界面
（只有超级管理员才有权限）

开机设置命令行模式 
/etc/inittab initdefault中的值设为3
```



## 2.用户与用户组管理

/etc/passwd	存储用户关键信息

/etc/group		存储用户组关键信息

/etc/shadow	 存储用户密码信息



（一）添加用户  #useradd 选项 用户名

* -g	指定用户的用户组主组，id或组名
* -G	指定用户的用户组附加组，id或组名
* -u     uid，自定义用户id
* -c     添加注释



passwd文件解释：

![image-20220525154514676](https://xiehangblog.oss-cn-beijing.aliyuncs.com/pic/202205251545773.png)





（二）修改用户  #usermod 选项 用户名

* -g	指定用户的用户组主组，id或组名
* -G	指定用户的用户组附加组，id或组名
* -u     uid，自定义用户id
* -l      修改用户名

​	

（三）设置密码 #passwd 用户名



（四）删除用户 #userdel 选项 用户名

* -r：删除同时删除其家目录

已经登录的用户，需要kill全部进程后删掉



用户组  

 （一）添加 	#groupadd 选项 用户名组

* -g 	自定义用户组id

（二）编辑  #groupmod 选项 用户组名

* -g 	自定义用户组id
* -n     设置新的用户组名称

（三）删除	#groupdel 用户组名











## 3.常用命令

* ls

​		蓝色： 文件夹 	白色：文件	绿色：权限为拥有所有权限

* pwd (print working directory)
* cd       ~切换到家目录
* mkdir 
* touch 文件路径
* cp（copy） 被复制路径  目的路径

​			可以重命名

​			复制文件夹时，需要加选项 -r 把文件夹里的全部复制

* mv   
* rm   

​			-f：	（force）：删除时不用确认，强制删除

​			-r：	删除目录，递归删除

​			删除指定文件，用通配符* 匹配，如linux*表示以linux开头的文件名

* vim

​			退出：  ：q（wq保存并退出）

* 输出重定向

  ```
  >   覆盖输出，覆盖原先内容
  >>	追加输出，末尾添加
  ```

  正常语法 >  保存文件路径（可以不存在）

* cat

​		直接打开文件查看

​		合并文件    `#cat 带合并文件1 文件2 > 合并文件目的地址`

* df

​		查看磁盘空间

​		`#df -h`  以较高可读性显示

* free

​		查看内存使用情况

​		-m 按照MB来看  -g 以GB为单位查看

​		swap：用于临时内存，系统真实内存不够可以使用磁盘空间充当临时内存

* head

​		查看文件前n行，默认十行

​		`#head -n path`

* tail 

​		查看文件后n行，默认十行，用法同上

​		tail -F  查看一个文件的动态变化，用于查看系统日志

* less

​		查看文件，以较少内容输出 ，按辅助键查看更多

* wc

    统计文件内容信息，包括行数，单词数，字节数

    `#wc -lwc path`     -l  lines(常用)    -w words	-c bytes

    

* date

​		操作时间和日期

​		date +%F 	等价于  date “+%Y+%m+%d”

​		date “+%F %T”    输出全部信息    等价于  date “+%Y+%m+%d+%H：%M:%S”

​		往前推一天    `#date -d "-1 day" "+%Y+%m+%d+%H：%M:%S"`

​		%F :完整年月日		%T：完整时分秒

* cal

​		日历

​		cal -1   本月

​		cal -3	上月+本月+下月

​       cal -y	指定



* clear +L
* 
* 管道

​		用于过滤，“特殊”，“扩展处理”

​		`#ls |grep y`  查询包含y的文件名称

```
//统计某文件夹下文件总个数
#ls -al / | wc -l
```



* hostname

​		-f : 输出当前主机名的FQDN（全限定义名）



* id

​		查看用户的基本信息

* whoami

​		显示当前登录用户名

* ps -ef

​		查看服务器的进程信息

​		-e ： 列出全部的进程

​		-f: 	显示全部的列

​		UID：该进程的用户id

​		**PID：进程id**

​		**PPID：该进程的父级id,没有则说明进程无用**

​		**C:CPU的占用率**

​		STIME：进程的启动时间（Start）

​		TIME：进程的执行时间

​		TTY：终端设备，若显示？则表示该进程不是由终端设备发起

​		CMD:该进程的名称或者对应的路径

```
//查看火狐进程
#ps -ef |grep firefox
```



* top

​		查看服务器的进程占的资源

​		进入命令 #top  （动态显示）   q退出

​		PR：进程优先级，越大越好

​		VIRT：虚拟内存		RES:常驻内存		SHR:共享内存

​		S: 进程状态 sleeping   R:running

​		TIME+：执行时间

​		COMMAND： 进程的名称或命令

​		

​		可以使用快捷键M，按照内存排序   	P：按照CPU排序



* du -sh  path

​		查看目录的真实大小 

​		-s ：summaries 显示汇总的大小

​		-h：以较高可读性显示



* find path 选项  选项的值

​		查找文件

​		-name：按照文档名称搜索

​		-type：按照文档类型搜索		-：文件 （f替换）  d：文件夹

```
搜索ETC目录下所有conf后缀文件并查看个数
#find /etc -name *.conf |wc -l

搜索etc下面所有的文件
#find /etc -type f
```



* service  服务名   start/stop/restart

​		用于控制软件的服务启动、停止，重启

​		

* kill 进程PID

​		杀死进程

​		killall 进程名称



* ifconfig

​		操作网卡

​		

* reboot

​		重启

​		-w: 模拟重启，但是不重启 。用于写重启的日志



* uptime

​		输出计算机的持续在线时间



* uname -a

​		获取全部操作系统相关信息

​	

* netstat 

​		查看网络的连接状态

​		-t:	只列出tcp协议的连接

​		-n:	利于观看

​		-l：只显示状态列中为LISTEN（监听）的连接

​		-p：显示对应的连接的进程PID和名称





删除光标之前的命令：ctrl+u     光标之后的：ctrl+k



## 4.vim 

​	命令模式：默认打开模式，不能直接编辑，可以使用快捷键

​	编辑模式：编辑内容

​	末行模式：末行输入命令对文件进行操作



打开方式：

1.  vim 文件路径
2. vim +数字  文件路径     //打开指定文件，并且移动到指定行
3. vim +/关键词  文件路径   //高亮显示关键词
4. vim   path1  path2  ….      



### 1.命令模式

**光标移动：**

* 移动到行首	shift+6	（^）
* 到行尾      shift+4       ($)
* 首行       gg
* 末行      G
* 翻屏      向上：ctrl+b/pgup   (back)     向下：ctrl+f/pgdn  (forward\)
* 移动到指定行   数字 G
* 向上或向下移动多少行     数字 光标上/下



**复制：**

* 复制光标所在行   yy

​		粘贴：p	（paste）

* 向下复制指定行：  数字  yy  （包含当前行）
* 可视化复制    ctrl+v



**剪切与删除：**

* 所在行   dd		
* 向下   数字 dd
* 删除当前行但是光标不上移   D



**撤销恢复：**

​	撤销：u或者u   （undo）

​	恢复：ctrl+r，取消撤销



### 2.末行模式

* 保存 ：w [path]

* 退出：q

* 强制：q！    强制退出，不做保存

* 调用外部命令：！命令

*  搜索：/关键词		N  上一个      n 下一个	（next）

* 取消高亮：nohl    （no high light）
* 替换： s/搜索的关键词/ 新的内容    替换光标所在行第一处符合条件的额内容

​				    s/搜索的关键词/ 新的内容/g   所在行全部符合内容			（global）

​				    % s/搜索的关键词/ 新的内容/g   所有的

* 显示行号：set nu           （number）           取消：set nonu
* 打开多个文件

​		：files  显示文件

​		%a：正在打开的文件（active）

​		#：上一个打开的文件

​		切换： open filename   或者 ：bn（上一个   back next）    bp（下一个 back previous）





### 3.编辑模式

​	进入： i  （光标所在前插入  insert）   a（光标所在后插入 after）



### 4.扩展

​	代码着色：syntax on/off

​	vim中的计算器：进入编辑模式，ctrl+R，然后“=”，输入需要计算的内容，回车

​	别名机制：映射文件 ./bashrc

​				alias  cls=“clear”





## 5.网络

重启网卡服务 #service network restart 

/etc/init.d 	有很多服务的快捷方式

软链接	#ln -s  

关闭某个网卡： #ifdown 网卡名

开启某个网卡： #ifup 网卡名



* ping  主机地址（ip地址，主机名 域名等）

  检测当前主机与目标主机之间的连通性

  ```
  ping www.baidu.com
  ```

  

* netstat   -tnlp

​		查看网络连接信息

​		-t:tcp协议		

​		-n：字母转换为数字

​		-l：列出状态为监听

​		-p：显示进程的相关信息



* traceroute	查找当前主机与目标主机所有的网关（路由器）

​		

* sftp

* 

  

  

  

   

## 6.Shell

#!/bin/bash

输出echo

指令赋值给变量末尾加反引号`







# 其他

* 设置主机名	#hostname

​		-f：全限定域名

​	设置临时主机名	hostname 名字

​	永久设置	/etc/sysconfig/network	修改hostname

​	设置FQDN：hosts文件位置	/etc/hosts



* chkconfig

​		- -list	开机启动服务查询  3，5开机不启动 （数字表示启动级别）

​		- -del	服务名			删除服务

​		- -add	服务名

​		- -level  连在一起的级别	on/level	修改设置某个服务的级别	

​		chkconfig –level 35 httpd on



* ntp服务

​		用于对计算机的时间同步管理操作

​		一次性同步：#ntpdate	时间服务器域名（百度搜）

​		自动同步：nptd服务

​			先启动 #service nptd start

​			设置开机启动	#chkconfig –level 35 ntpd on

​		

* 防火墙服务
* rpm管理

​		查询	#rpm -qa|grep 关键词

​		-q：query 查询

​		-a：all

​		

​		卸载：#rpm -e 名称

​			如果有依赖关系	#rpm -e 软件包名 –nodeps		（忽略依赖）

​			

​		安装：#rpm  -ivh  软件包完整名称

​			先获取安装包（官网）

​			-i: install

​			-v：显示进度条

​			-h：以“#” 形式显示进度条

​			

* cron/crontab	计划任务

​		#crontab	

​		**-l：list	指定用户的计划任务列表**

​		**-e：edit** 		分 时 日 月 周 需要执行的命令

```
每天0时0分reboot
0 0 * * * reboot

*	所有
-	区间
/	每多少个 每十分钟 */10
,	多个取值
```

​		-u：user  指定用户

​		-r: remove 

![image-20220530173239174](https://xiehangblog.oss-cn-beijing.aliyuncs.com/pic/202205301732257.png)

![image-20220530173501413](https://xiehangblog.oss-cn-beijing.aliyuncs.com/pic/202205301735462.png)

* 
