pip3 install --user --editable .
pip2 install --user --editable .

mkdir build
cd build
cmake ..
make -j2
sudo make install
