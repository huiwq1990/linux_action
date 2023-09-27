
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

sudo apt-get update

sudo dpkg --add-architecture i386
sudo apt-get update -y
sudo apt upgrade -y

# sudo apt-get dist-upgrade

sudo apt-get install -y build-essential bin86 manpages-dev linux-headers-$(uname -r)
sudo apt-get install -y libc6-dev-i386 lib32z1
sudo apt-get install -y libsm6:i386
sudo apt-get install -y libx11-6:i386
sudo apt-get install -y libxpm4:i386

sudo apt-get install -y libncurses5:i386
sudo apt-get install -y libexpat1:i386


sudo apt-get install -y qemu
sudo apt-get install -y qemu-system