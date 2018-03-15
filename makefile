CC=emcc
CFLAGS= -s EXPORTED_FUNCTIONS='["_run","_zero_file","_fs_prepare","_print1","_print2","_free"]'
CFLAGS+= -s EXTRA_EXPORTED_RUNTIME_METHODS='["stringToUTF8","ccall","cwrap","lengthBytesUTF8"]'
CFLAGS+= -s WASM=1 -Os

default: fs 

fs: fs.c
	$(CC) $(CFLAGS)  fs.c  
