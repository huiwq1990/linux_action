
## 虚拟机

```shell

启动虚拟机，然后执行`sh init.sh`，将操作系统源码挂载到虚拟机里。

```

sudo免密

```shell
sudo chmod +w /etc/sudoers

# 追加/etc/sudoers

echo "hg ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

```

## 环境准备

### 安装软件

```shell

sh install.sh

cd gcc-3.4 & ./inst.sh amd64

#因为oslab在共享目录下，这个文件名不区分大小写
cp -r /hostshare/oslab /root/oslab

```

## 开启调试

```shell

-fda Image：代表你把 Image 執行目錄下  
-hda hdc-0.11.img：代表你把 HD img，是一个模拟硬盘的文件，可以在赵博士所提供的`linux-0.11-devel-040809.zip`找到
-m：设定模拟的内存大小，本地设定为 16MB 
-s : 服务器开启1234端口
-S: 开始执行就挂住

```


开启新窗口

gdb tools/system

https://www.jianshu.com/p/ab4fa7f12f06