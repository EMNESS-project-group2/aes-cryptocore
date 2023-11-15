# Introduction

European Master Network on Embedded System Security (EMNESS) project is an ERASMUS+ Cooperation partnership initiative with the goal to structure an innovative academic curriculum on Reliability and Hardware Security.

The main goal is to prepare an OPEN-ACCESS lab experience to teach the topic covered by the project to students of the master in Computer or Electronic engineering

In detail, this repository is the development of a Linux/FreeRTOS device driver for a crypto core in a PYNQ-Xilinx Board. In this README file there will be explained the LAB experience.

#### Copyright
Licensed under CC-BY-4.0

## Requirements

In order to do the lab it is necessary to have the following software installed:
- Vivado
- Vitis
- FPGA XILINX PYNQ-Z2
- petalinux

It's supposed to be executed on a linux machine.

## Laboratory activities

The steps that you will follow are:

1. Create the HW platform in Vivado that will contain the instance of the processor and the crypto-core, with an AXI interface
2. Test the HW platform with a bare-metal test on Vitis
3. Export the hw platform file
4. Build an Embedded linux system
5. Put the Embedded Linux system on the FPGA
6. Write a driver for the cryptocore
7. Write a test for the driver on the linux system


# 1. Create the HW platform in Vivado


## Download the core

Download the requested core from http://opencores.org <br>
It's mandatory to be registered with a student account in order to be able to download it. The confirmation of the registration could take some days. 

The core will be in VHDL or Verilog format. Both the HDL formats will work correctly with the following parts of the task.

## Vivado

### Project and IP creation

We will use vivado to create the IP, including the core we need. <br>

Create a Vivado Project.

Create new Project -> RTL project<br>
Then we choose the board, which is the Pynq-Z2.<br>
**NOTE:** the board package needs to be included during the installation process of Vivado <br>
Then, clicking on `Finish`, the project is created.

From the `Tools` menu, click on `Create and package new IP`, then `Create AXI4 Peripheral`<br>
Pay attention to set `light` as interface type. <br>
In this phase is important to specify the total number of registers needed in the IP (considering they have 32 bit, so signals with higher parallelism will take more than one register).<br>
Each register will create an address (made by an offset with respect to a common base address) and each of these will be used only for an input or an output. The same address can't be used for more than one signal.<br>

### Core instantiation in the interface

After having created the IP, click on the `Edit IP` choice. <br>
Then from the `Sources` panel click on the `+` and add the HDL files for the core. <br>
The core will be instantiated using these files as a component. <br>

For interfacing properly the core through the AXI4 interface, it has to be instantiated and the ports have to be connected to the signals of the AXI4 that can be used as input/output. It can be done by writing HDL code into the verilog file of the IP (the file which name terminates with `...SOO_AXI.vhd/.v`)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/media/Screenshot%20from%202023-10-11%2018-32-43.png)

After having made the proper connections, click on `Open elaborated design`. This option will automatically allocate our core inside the interface in the way defined in the IP. 

Now the schematics of the elaborated design are available.

It's important to verify from the schematics that all the connections have correctly been implemented, especially where there is a parallelism higher than 32 bits and so the data has to be managed using registers in parallel.


![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/media/Screenshot%20from%202023-09-29%2018-48-22.png)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/media/Screenshot%20from%202023-09-30%2015-58-35.png)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/media/Screenshot%20from%202023-09-30%2016-50-48.png)

### Review, package, block design, wrapper

At this point, if everything corresponds to what is expected, click on the `Package IP - <name>` panel, and proceed clicking on `File Groups` -> `Merge changes from File Groups Wizard`.

Now click on `Review and Package` -> `Re-Package IP`

After having confirmed to close the project by clicking on `Yes`, next step is to create the block design <br>
On the left menu: `Create block design`, the specify a name and click `OK`. <br>
Now add the board processing system by clicking on the `+` symbol in the `Diagram` panel, and then selecting the board. <br>
Click on `Run Block Automation`, then confirm with `OK`.<br>
Then add the custom IP made in the previous steps by clicking again on the `+` symbol, then `Run Connection Automation` and `OK` in the window that will appear. <br>
Now validateby clicking on the blue check mark `✓` in `Diagram` panel, click `OK`.

Now it's time to create the wrapper that will be exported: <br>
right click on the core name under the `Design Sources` section -> `Create HDL Wrapper` -> `Let Vivado manage wrapper and auto-update`. <br>

Now the wrapper should appear in the Design Sources in the `Sources` panel.

Then on the left menu: `Generate Bitstream`, and `OK` in "Launch Runs" window.

Now `File` > `Export` > `Export Hardware` <br>
In the window "Export Hardware Platform" : <br>
`Include bitstream`, give the file name for the XSA and a path where to be exported. <br>
`Finish`.

# 2. Test the HW platform with a bare-metal test on Vitis

Open Vitis <br>
`Create Application Project` -> `Next` -> `Create a new platform from hardware (XSA)` <br>
Here click on `Browse...` and select the wrapper file (.xsa) . Verify the platform name and proceed with `Next`. <br>
Select the `ps7_cortexa9_0`, then `Next`. <br>
In "select a domain" click on `Create new`, and in "Operating System" option select `standalone` <br>
`Next` -> select `HelloWorld` -> `Finish` <br>

Now the project is ready for adding some user code <br>

On the left menu, in `src`, then `helloworld.c`, read the code generated by Vitis. <br>
On the left menu, in `hw`, `drivers`, `<your ip name>`, `src` open the `<your ip name>.h` file and verify the generation of the correct offset constants for the address management. By scrolling down in the code, there are the methods for writing registers and reading registers, that can be used for our purposes. <br>

Be sure to have included libraries: 
```
#include "platform.h"
#include "xil_io.h"
#include "<your ip name>.h""
#include "xparameters.h"
```
<br>

Now we can use the `_mWriteReg` and `_mReadReg` methods to properly write and read data to/from the core. <br>

<br>

Once finished, we can click on the `build` icon (the one with the hammer on it, on the top bar)


# 3. Embedded Linux Installation Guide

## How to install PetaLinux

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


## Create the project
1. Go to your terminal and change directory to where you would like to create your new PetaLinux project directory 
2. Run:

```bash
petalinux-create -t project --template zynq --name aes-petalinux
```

Here '-t' is equivalent to '--type'. You can see that there is a new folder created and you can enter inside it.

```bash
cd aes-petalinux
```

## Configure using XSA file

You have previously created a XSA file as output of VIVADO that describes you hardware platform, which includes the instantiation of the ARM® Cortex™-A9 and the Crypto-core. You will need this file now for configure petalinux build and tell to petalinux what devices are available for it and it will create a Device Tree based on this hw definition file.

Write this command into the project directory

```bash
petalinux-config --get-hw-description <PATH-TO-XSA DIRECTORY>
```

This will open the first configuration screen of the petalinux tool. In this you can navigate and check what is inside, but there is no need to change anything here.

You can exit by pressing double time the <ESC>. Save it.
This can needs some time.

## Configure the Kernel

Now we will configure the kernel. Hit the following command inside the project directory

```bash
petalinux-config -c kernel
```
This will need some time. After that, a similar window to the previous one should open. As before, there are many options, you can browser it for checking if you have to change something. Also here, there is no need to change anything for the purpose of this Lab.

## Configure U-boot

Another configuration command we have to run

```bash
petalinux-config -c u-boot
```
In the configuration window, you have to enable the boot options --> boot media --> "Support for booting from QSPI flash" and "Support for booting from SD/EMMC"

Save and exit.

Now there will be another configuration command needed, the one for the RootFS. But first, in order to compile it correctly for this lab, you want to create an application and a module.

## Creating and Compiling the driver
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

## Creating and Compiling the test driver

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
## Build the images

If everything works, you can build the images by giving as input the hw_platform you have created before

```bash
petalinux-package --boot --fsbl $(PETAPROJECT)/images/linux/zynq_fsbl.elf --fpga $(VIVADO-HW-PATH)/hw_platform_300923/hw_platform/hw_platform.runs/impl_1/hw_platform_wrapper.bit --uboot --force
```
## Configure the Rootfs
The final configuration command will be.

```bash
petalinux-config -c rootfs
```
Here you can add your custom applications by going to user packages -> aes-core-driver and enable it

Same for the test.

Save and exit.

## Build the project

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



