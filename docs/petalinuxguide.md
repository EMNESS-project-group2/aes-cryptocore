# PYNQ-Z2 Linux Installation Guide: NOT SURE OF THE LAST SECTION

## Installing PetaLinux

1. **Download PetaLinux:**
   - Visit the following link to download the PetaLinux installer:
     [PetaLinux Download](https://www.xilinx.com/member/forms/download/xef.html?filename=petalinux-v2023.1-05012318-installer.run)

2. **Installation Steps:**
   - After downloading, move the `.run` file to the desired installation folder.

   - Open your terminal and navigate to the installation folder.

   - Run the installer using the following command:
     ```bash
     bash petalinux-v2023.1-05012318-installer.run
     ```
   - Follow the on-screen prompts to accept the license agreements and complete the installation.

   - Run the settings.sh script `source ./settings.sh` (ignore the warning)

## Generating BSP Files and Linux Kernel

Since our board vendor does not provide BSP files, you can use PetaLinux to generate them and configure your Linux system. After generating the BSP files, you have two options:

1. **Using a Precompiled Image (Easier):**
   - Visit the [PYNQ-Z2 board manufacturer's website](http://www.pynq.io/board.html).
   - Download the precompiled Linux image provided by the manufacturer.
   - Use PetaLinux to generate the remaining boot files (BOOT.BIN, image.ub) specific to the hardware configuration (you will need to obtain this configurations from the manufacturer cloning the following git repository: (https://github.com/xilinx/pynq).

2. **Creating a PetaLinux Project from Scratch (Full Control):**
   -  Create a PetaLinux project from scratch to build the entire Linux system, including the kernel, device tree, and root filesystem, customized for our hardware. This approach provides full control and customization but requires more setup and configuration compared to using a precompiled image.


Since its an specification of the project, we  will try creating the project from scratch: CONTINUE
1) petalinux-create -t project -n myproject --template zynq
2) 