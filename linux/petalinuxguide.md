# PYNQ-Z2 Linux Installation Guide: NOT SURE OF THE LAST SECTIONfd

## Installing PetaLinux

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

- If an Error comes out saying you are missing some packages, run the following command:
```bash
  sudo apt install gawk zlib1g-dev net-tools xterm autoconf libtool texinfo gcc-multilib 
```
Maybe they aren't all the packages missing. If is that the case, check the error messages and search on google how to download that specific library by terminal. You will easily find a command to do it

- Follow the on-screen prompts to accept the license agreements and complete the installation.

- Run the settings.sh script `source ./settings.sh` (ignore the warning)

## Generating BSP Files and Linux Kernel

BSP (Board Support Package) files are essential configurations and software components that enable an operating system, such as Linux, to run on a specific hardware platform, like the PYNQ-Z2 SoC. These files include device drivers, hardware initialization code, and settings specific to the target board.
Since our board vendor does not provide BSP files, you can use PetaLinux to generate them and configure your Linux system. After generating the BSP files, you have two options:

1. **Using a Precompiled Image (Easier):**
   - Visit the [PYNQ-Z2 board manufacturer's website](http://www.pynq.io/board.html).
   - Download the precompiled Linux image provided by the manufacturer.
   - Put the image inside the SD card

2. **Creating a PetaLinux Project from Scratch (Full Control):**
   -  Create a PetaLinux project from scratch to build the entire Linux system, including the kernel, device tree, and root filesystem, customized for our hardware. This approach provides full control and customization but requires more setup and configuration compared to using a precompiled image.


Since its an specification of the project, we  will create the project from scratch. We found the git repository of Xilinx which has all the needed files and scripts to generate the required BSP which we will then be used on PetaLinux.
**Creating BSP and creating the PetaLinux project**
1. Clone the pynq project repo to your PC:
   ```bash
     git clone git@github.com:Xilinx/PYNQ.git
2. Launch the vivado script for env variables

   ```bash
   source ${Vivado_installation_directory}/settings.sh
   ```
3. Go to the `base` directory:
   ```bash
   cd PYNQ/boards/Pynq-Z2/base/
   ```
4. Open the `base.tcl` script and change `scripts_vivado_version` variable to your Vivado version, for us it was 2022.2
5. Run `make` and wait until you get the message "build finished succesfully", go grab a coffee in the meanwhile, it takes some time.



We have to write here how we created the BSP using petaLinux

After, creating a new project from a BSP is the simplest way to get started with PetaLinux, since it provides you with an already functioning and bootable Linux image that you start playing with.
1. Go to your terminal and change directory to where you would like to create your new PetaLinux project directory and enter the following command.
2. Run:

```bash
petalinux-create -t project -s <bsp_path> --name 
OperatingSystemProject
```

Here '-t' is equivalent to '--type' and '-s' is for source (has to be followed by the absolute path to the BSP we just created in the previous step). (i.e home/ric/PYNQ-Z2/pynq_z2.bsp).

1. Move to the newly created directory:
```bash
cd OperatingSystemProject
```

1. This step is very straight forward from an end user's perspective, but will require you to accept a bit of 'magic' in the background if you are not intimately familiar with the process of compiling a Linux image from scratch. After this step, you will have a kernel, file system, first stage and second stage boot loaders, and device tree compiled and ready to be deployed to your PYNQ-Z2.

```bash
petalinux-config --get-hw-description <PATH-TO-XSA DIRECTORY>
```
The petalinux-config --get-hw-description command allows you to initialize or update a PetaLinux project with hardware-specific information from the specified Vivado hardware project.

TCL, make, tcpdamp,gcc runtime, buildesential, petalinux packages groups (check link), ssh, vitis accelereation essentials, empy root pswd,  (STEP5)

STEP6: RUN COMMAND
STEP7: USB SUPPORT AS TUTORIAL
STEP8: build
 
....
...
..
tutte cose
...
...


 ```bash
 petalinux-build
 ```

 ## Creating and Compiling the driver

 ```bash
 petalinux-create -t modules --name aes-core-driver --enable
 ```

 You can edit the file

 ```bash
 $(PETAPROJECT)/project-spec/meta-user/recipes-modules/aes-core-driver/files/aes-core-driver.c
 ```

 Once you are done you can build it with petalinux

 ```bash
 petalinux-build -c aes-core-driver
 ```

 If everything works, you can build the images by giving as input the hw_platform you have created before

 ```bash
 petalinux-package --boot --fsbl $(PETAPROJECT)/images/linux/zynq_fsbl.elf --fpga $(VIVADO-HW-PATH)/hw_platform_300923/hw_platform/hw_platform.runs/impl_1/hw_platform_wrapper.bit --uboot --force
 ```

 Check if the driver is present in the rootfs

 ```bash
 petalinux-config -c rootfs

 # Go to user packages -> aes-core-driver and enable it
 ```

Finally

```bash
petalinux-build
```

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


