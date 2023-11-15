## CONNECT THE BOARD IN LINUX

#### Board package on Vivado

In order to work on the Pynq-Z2, download from there the board files:

https://www.tulembedded.com/FPGA/ProductsPYNQ-Z2.html#:~:text=Z2%20Board%20File


1. unzip the downloaded file
2. copy the folder insider $Vivado_path/data/xhub/boards/XilinxBoardStore/boards/Xilinx/
3. Restart Vivado


-From VIVADO open Flow -> Hardware manager -> Autoconnect (You should be able to see the board connected)

#### Install the Xilinx Cable Drivers

For installing the cable drivers in order to connect the board to the computer on a linux distribution, you will need vivado. Run the following command

```bash
./${VIVADO_DIR}/data/xicom/cable_drivers/lin64/install_script/install_drivers/install_drivers
```

**Notes for TroubleShooting**
- If while trying to write on the FPGA you get the map error download the patch at this [link](https://support.xilinx.com/s/article/000034848?language=en_US). Inside the downloaded dir there is a README file that explains how to install it.
- After building the project in Vitis, go in Launch Target Connection and you should see the board connected in the Local server
- Finally, in order to check the result, in the Vitis serial terminal click on + and add the USB port at which the board is connected in order to have the serial connection. 

## Console Set-Up with Putty

You can access serially the FPGA by using Putty.
```bash
sudo apt install putty
```

If you run
```bash
ls /dev/ttyUSB*
```

If the FPGA is plugged, you will notice a couple of device attached, usually ttyUSB0 and ttyUSB1. Usually, ttyUSB0 is the one related to the JTAG connection for programming and debugging and ttyUSB1 is the one related to the USB to UART converter.


You can use any program to monitor the console. With Putty you can run it with sudo and put
115200 as Baud Rate and the /dev/ttyUSB1 as serial port.

Now you can see what's happening in your linux system and also interface with it.

## Login with petalinux 2022.2 or above

Login with "petalinux" and change the password.

## Ethernet connection

If you are connected to your laptop through an ethernet connection, you can setup a TCP/IP connection.

On your laptop, add a subnet. For example

```bash
sudo ip addr add 192.168.3.1/24 dev eth0

sudo ip link set dev eth0 up
```

The Device can change of course. Usually is eth* or enps*

You can see if is working with

```bash
ip addr
```

You should be able to see your new IP.

On the FPGA, accessing through Serial port you can do the same things you did on your laptop but by using a different subnet

```bash
sudo ip addr add 192.168.3.3/24 dev eth0
```

After configuring both your computer and the FPGA, you should be able to ping between them as mentioned in the previous response:

- From your computer, you can ping the FPGA using its configured IP address (e.g., ping 192.168.3.3).
- From the FPGA, you can ping your computer using its configured IP address (e.g., ping 192.168.3.1).

If everything works you can also access the system through ssh.


