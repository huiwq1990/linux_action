MODULE=tmain
make >> /dev/null
sudo dmesg -c >> /dev/null

sudo insmod ${MODULE}.ko

sudo rmmod ${MODULE}

make clean >> /dev/null

dmesg