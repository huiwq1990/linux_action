
ip addr

echo "注：如何退出QEMU，同时按住ctrl+a，然后全部松开，再按x"

qemu-system-i386 -m 16M -boot a -fda Image -hda hdc-0.11.img 

#-s -S