# !/bin/bash
cp test.s t.s
arm-linux-gnueabihf-gcc test.s -o test -static
qemu-arm ./test
