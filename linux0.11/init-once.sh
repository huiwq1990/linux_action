

# 设置hg用户，具有sudo不输入密码
sudo chmod +w /etc/sudoers

echo "hg ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

