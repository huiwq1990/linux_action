
sudo mkdir -p /hostshare
sudo mount -t 9p -o trans=virtio share /hostshare -oversion=9p2000.L
