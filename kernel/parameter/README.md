
make

 modinfo ./parameter.ko


sudo insmod parameter.ko testpar=10

dmesg

sudo rmmod helloworld
