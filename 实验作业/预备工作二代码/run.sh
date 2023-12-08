# !/bin/bash
arm-linux-gnueabihf-gcc -o test.s -S -O0 test.c -fno-asynchronous-unwind-tables
arm-linux-gnueabihf-gcc test.s -o test -static
