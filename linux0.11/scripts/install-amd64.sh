
# 适用于yuan-xy的Linux代码，用高版本的gcc编译

sudo cp /etc/apt/sources.list /etc/apt/sources.list.backup

sudo cat<<EOF > /etc/apt/sources.list 
# 默认注释了源码仓库，如有需要可自行取消注释
deb https://mirrors.ustc.edu.cn/ubuntu/ jammy main restricted universe multiverse
# deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy main restricted universe multiverse

deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-security main restricted universe multiverse
# deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-security main restricted universe multiverse

deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse
# deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-updates main restricted universe multiverse

deb https://mirrors.ustc.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
# deb-src https://mirrors.ustc.edu.cn/ubuntu/ jammy-backports main restricted universe multiverse
EOF

sudo apt-get update -y

sudo apt-get install -y build-essential bin86 manpages-dev linux-headers-$(uname -r)
sudo apt-get install -y qemu
sudo apt-get install -y qemu-system
sudo apt-get install -y openssh-server
 