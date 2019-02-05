#!/bin/bash
apt-get update
apt-get upgrade -y
apt-get dist-upgrade -y
### Create 4 GB of Swap ###
dd if=/dev/zero of=/mnt/myswap.swap bs=1M count=4000
mkswap /mnt/myswap.swap
chmod 0600 /mnt/myswap.swap
swapon /mnt/myswap.swap
### Install Depends ###
apt-get install nano htop git -y
apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils software-properties-common libgmp3-dev -y
apt-get install libboost-all-dev -y
add-apt-repository ppa:bitcoin/bitcoin -y
apt-get update
apt-get install libzmq3-dev -y
apt-get install libminiupnpc-dev -y
apt-get install libdb4.8-dev libdb4.8++-dev -y
### Prepare Source ###
mkdir /root/vividsource
git clone https://github.com/vividplatform/vividcoin /root/vividsource
chmod -R 777 /root/vividsource
cd /root/vividsource
chmod 777 autogen.sh
./autogen.sh
./configure
chmod +x share/genbuild.sh
make
### Prepare Binaries ###
mkdir /root/vivid
mkdir $HOME/.vivid
cp /root/vividsource/src/vividd /root/vivid
cp /root/vividsource/src/vivid-cli /root/vivid
ln -s /root/vivid/vivid-cli /usr/local/bin/vivid-cli
ln -s /root/vivid/vividd /usr/local/bin/vividd
chmod -R 777 /root/vivid
chmod -R 777 $HOME/.vivid
apt-get install pwgen -y
EXIP=`wget -qO- ipinfo.io/ip`
PASS=`pwgen -1 20 -n`
printf "rpcuser=userasdasd\nrpcpassword=$PASS\nrpcport=38000\ndaemon=1\nlisten=1\nserver=1\nmaxconnections=256\nrpcallowip=127.0.0.1\nexternalip=$EXIP:38079\n" > $HOME/.vivid/vivid.conf
printf "\n#--- Seed Nodes ---\naddnode=144.202.17.231:38079\naddnode=144.202.65.82:38079\naddnode=95.179.140.221:38079\naddnode=45.76.54.229:38079\n" >> /$HOME/.vivid/vivid.conf
