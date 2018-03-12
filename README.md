Ubuntu16.04

Install wasm
git clone https://github.com/juj/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest

update profile
source ./emsdk_env.sh --build=Release 1>/dev/null 2>&1

sudo apt install libzmq-dev



