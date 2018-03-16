#! /bin/bash
path='/mnt/nbd/';
dd if=/dev/urandom of=${path}zf_1k.bin bs=1000 count=1;
dd if=/dev/urandom of=${path}zf_10k.bin bs=1000 count=10;
dd if=/dev/urandom of=${path}zf_100k.bin bs=1000 count=100;
dd if=/dev/urandom of=${path}zf_1m.bin bs=10000 count=100;
dd if=/dev/urandom of=${path}zf_10m.bin bs=10000 count=1000;
dd if=/dev/urandom of=${path}zf_100m.bin bs=10000 count=10000;
