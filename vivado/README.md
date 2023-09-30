# CONNECT THE BOARD IN LINUX

-From VIVADO open Flow -> Hardware manager -> Autoconnect (You should be able to see the board connected)


-Install the cable drivers for vitis -> 

```bash
./${vivado_install_dir}/data/xicom/cable_drivers/lin64/install_script/install_drivers/install_drivers
```

-If while trying to write on the FPGA you get the map error download the patch at this link: https://support.xilinx.com/s/article/000034848?language=en_US

Inside the downloaded dir there is a README file that explains how to install it.

-After building the project in Vitis, go in Launch Target Connection and you should see the board connected in the Local server

-Finally, in order to check the result, in the Vitis serial terminal click on + and add the USB port at which the board is connected in order to have the serial connection. 





