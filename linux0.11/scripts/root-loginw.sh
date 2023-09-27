#!/bin/bash

 #set root password
 # https://blog.csdn.net/hexf9632/article/details/110688396
echo -e "root123\nroot123" | passwd root
 
#modify conf
sudo sed -i 's/^#PermitRootLogin.*/PermitRootLogin yes/' /etc/ssh/sshd_config

#restart server
sudo systemctl restart ssh