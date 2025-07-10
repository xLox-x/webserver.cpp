wget http://home.tiscali.cz/~cz210552/distfiles/webbench-1.5.tar.gz
tar -zxvf webbench-1.5.tar.gz
cd webbench-1.5
sudo apt-get install -y libtirpc-dev
sudo ln -s /usr/include/tirpc/rpc/types.h /usr/include/rpc
sudo ln -s /usr/include/tirpc/netconfig.h /usr/include
sudo apt-get install universal-ctags
make
webbench -c 100 -t 30 http://127.0.0.1:1234/
