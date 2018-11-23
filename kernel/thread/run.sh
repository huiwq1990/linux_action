MODULE=thread_create
make

sudo insmod ${MODULE}.ko

sudo dmesg -c >> /dev/null

sudo rmmod ${MODULE}

make clean

dmesg