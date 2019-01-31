
make

sudo insmod tmain.ko

sudo dmesg -c >> /dev/null

sudo rmmod tmain

make clean

dmesg