Ubuntu16.04

Install wasm
git clone https://github.com/juj/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest

update profile
echo "source ~/emsdk/emsdk_env.sh --build=Release 1>/dev/null 2>&1" >> ~/.profile

sudo apt install libzmq-dev
npm install zmq

compile fs.c

emcc fs.c -Os -s WASM=1 -o fs.js -s EXPORTED_FUNCTIONS='["_run","_zero_file","_fs_prepare","_print1","_print2","_free"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["stringToUTF8","ccall","cwrap","lengthBytesUTF8"]'

compile zmq_client

g++ zmq_client.cpp -o zmq_client -lzmq -lboost_system -lboost_chrono
