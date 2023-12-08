# !/bin/bash
arm-linux-gnueabihf-gcc test.s -o test -static
qemu-arm ./test
