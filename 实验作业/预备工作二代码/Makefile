.PHONY:test,clean
test:
	arm-linux-gnueabihf-gcc test.s -o test.out
	qemu-arm ./test.out
clean:
	rm -rf test.out
