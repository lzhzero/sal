fio --ioengine=libaio --direct=1 --name=test --filename=/mnt/mem/test --bs=128k --iodepth=64 --size=10G --readwrite=rw 
