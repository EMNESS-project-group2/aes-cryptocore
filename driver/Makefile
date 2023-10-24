#Decide which is the ouput of the compiling process. Is like the -o of gcc. This instruction is the name of one output of the compiler process
#

#CC=/usr/bin/arm-linux-gnueabihf-gcc
obj-m+=driver.o

#Sections of compiling. With that you are compiling with the libraries present into the file system
all:
	make -C  /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
