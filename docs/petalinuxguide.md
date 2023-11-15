# PYNQ-Z2 Linux Installation Guide

#### How to install PetaLinux

1. **Download PetaLinux:**
   - Visit the following link to download the PetaLinux installer:
     [PetaLinux Download](https://www.xilinx.com/member/forms/download/xef.html?filename=petalinux-v2023.1-05012318-installer.run)

2. **Installation Steps:**

First of all, make sure you have the latest version of the OS.

```bash
  sudo apt update
```
After:
 ```bash
  sudo apt upgrade
```
- Then, after downloading, move the `.run` file to the desired installation folder.
- Open your terminal and navigate to the installation folder.
- Run the installer using the following command:
```bash
  bash petalinux-v2023.1-05012318-installer.run
```

- If an Error comes out saying you are missing some dependencies, run the following command:
```bash
  sudo apt install gawk zlib1g-dev net-tools xterm autoconf libtool texinfo gcc-multilib 
```
Maybe they aren't all the packages and dependencies missing. 

You can go at that [link](https://support.xilinx.com/s/article/73296?language=en_US ). By scrolling down, you can see a script called "plnx-evn-setup.sh". Download that script and run it. It should install **all** the packages needed. If is that not the case, check the error messages and search on google how to download that specific library by terminal. You will easily find a command to do it.

- Follow the on-screen prompts to accept the license agreements and complete the installation.

- Run the settings.sh script `source ./settings.sh` (ignore the warning)


#### Create the project
1. Go to your terminal and change directory to where you would like to create your new PetaLinux project directory 
2. Run:

```bash
petalinux-create -t project --template zynq --name aes-petalinux
```

Here '-t' is equivalent to '--type'. You can see that there is a new folder created and you can enter inside it.

```bash
cd aes-petalinux
```

#### Configure using XSA file

You have previously created a XSA file as output of VIVADO that describes you hardware platform, which includes the instantiation of the ARM® Cortex™-A9 and the Crypto-core. You will need this file now for configure petalinux build and tell to petalinux what devices are available for it and it will create a Device Tree based on this hw definition file.

Write this command into the project directory

```bash
petalinux-config --get-hw-description <PATH-TO-XSA DIRECTORY>
```

This will open the first configuration screen of the petalinux tool. In this you can navigate and check what is inside, but there is no need to change anything here.

You can exit by pressing double time the <ESC>. Save it.
This can needs some time.

#### Configure the Kernel

Now we will configure the kernel. Hit the following command inside the project directory

```bash
petalinux-config -c kernel
```
This will need some time. After that, a similar window to the previous one should open. As before, there are many options, you can browser it for checking if you have to change something. Also here, there is no need to change anything for the purpose of this Lab.

#### Configure U-boot

Another configuration command we have to run

```bash
petalinux-config -c u-boot
```
In the configuration window, you have to enable the boot options --> boot media --> "Support for booting from QSPI flash" and "Support for booting from SD/EMMC"

Save and exit.

Now there will be another configuration command needed, the one for the RootFS. But first, in order to compile it correctly for this lab, you want to create an application and a module.

#### Creating and Compiling the driver
The main goal of this LAB is to write a crypto-core driver in C language. Now, you can do it from scratch and try to cross-compile this driver for the system that you are building. This is not easy. Fortunately, Petalinux comes to help us. Indeed, in order to cross-compile the driver for the cripto-core easily, we will use the petalinux's recipes and buildtools. The skeleton of the driver that will contain your custom code can be created by terminal with this command.

```bash
petalinux-create -t modules --name aes-core-driver --enable
```
You can check that a new file it is created. The file is in

```bash
$(PETAPROJECT)/project-spec/meta-user/recipes-modules/aes-core-driver/files/aes-core-driver.c
```
There you can customize the init, write, read, open, close functions to your needs.

Once you are done you can build it with petalinux (cross-compile it)

```bash
petalinux-build -c aes-core-driver
```

Thanks to that command and to nexts that we will see, the driver will be already mounted on the device (i.e. the *.ko file).

#### Creating and Compiling the test driver

You can also create an application that tests your driver using the petalinux tools and avoiding also here to crosscompile it by yourself. 

```bash
petalinux-create -t apps --template c --name aes-core-test --enable
```

The new file created is in

```bash
$(PETAPROJECT)/project-spec/meta-user/recipes-apps/aes-core-test/files/aes-core-test.c
```
There you can customize the C file to your testing needs. 
Once you are done you can build it with petalinux

```bash
petalinux-build -c aes-core-test
```
#### Build the images

If everything works, you can build the images by giving as input the hw_platform you have created before

```bash
petalinux-package --boot --fsbl $(PETAPROJECT)/images/linux/zynq_fsbl.elf --fpga $(VIVADO-HW-PATH)/hw_platform_300923/hw_platform/hw_platform.runs/impl_1/hw_platform_wrapper.bit --uboot --force
```
#### Configure the Rootfs
The final configuration command will be.

```bash
petalinux-config -c rootfs
```
Here you can add your custom applications by going to user packages -> aes-core-driver and enable it

Same for the test.

Save and exit.

#### Build the project

Finally, you can build everything

```bash
petalinux-build
```
This will need time to complete.

## Booting from SD

First, you have to format and partition the SD card. You can do it by using the following guide:

https://docs.xilinx.com/r/en-US/ug1144-petalinux-tools-reference-guide/Partitioning-and-Formatting-an-SD-Card

Once you have done it, you will have two partitions:
1. BOOT
2. RootFS

You have already mounted the devices in you pc. If you don't know where the mount is located, you can do right-click on the GUI folder and hit "Open in the terminal". From there you can check the location of your two partitions.

1. Copy the following files from <PETAPROJECT>/images/linux in /BOOT/
   1. BOOT.BIN
   2. image.ub
   3. boot.scr
2. Exctract the rootfs.tar.gz folder into the RootFS folder

```bash
cd $(YourMountedLocation)/RootFS/

tar -xzvf $(PETAPROJECT)/images/linux/rootfs.tar.gz
```

You can eject the SD and put into the board, you're ready to go!
