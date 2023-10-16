# How to set the core on the Pynq-Z2 board

#### Copyright
Licensed under CC-BY-4.0

## First step: download the core

Download the requested core from http://opencores.org <br>
It's mandatory to be registered with a student account in order to be able to download. The confirmation of the registration could take some days. 

The core will be in VHDL or Verilog format. Both the HDL formats will work correctly with the following parts of the task.

## Second step: VIVADO

### Project and IP creation

We use vivado to create the IP, including the core we need. <br>
Vivado > Create new Project > RTL project<br>
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

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-10-11%2018-32-43.png)

After having made the proper connections, click on `Open elaborated design`. This option will automatically allocate our core inside the interface in the way defined in the IP. 

Now the schematics of the elaborated design are available.

It's important to verify from the schematics that all the connections have correctly been implemented, especially where there is a parallelism higher than 32 bits and so the data has to be managed using registers in parallel.


![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-09-29%2018-48-22.png)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-09-30%2015-58-35.png)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-09-30%2016-50-48.png)

At this point, if everything corresponds to what is expected, click on the `Package IP - <name>` panel, and proceed clicking on `File Groups` -> `Merge changes from File Groups Wizard`.

Now click on `Review and Package` -> `Re-Package IP`

After having confirmed to close the project by clicking on `Yes`, next step is to create the block design <br>
On the left menu: `Create block design`, the specify a name and click `OK`. <br>
Now add the IP by clicking on the `+` symbol in the `Diagram` panel, and then selecting the board. <br>
Click on `Run Block Automation`, then confirm with `OK`.<br>

```
code
codkfdxfnjsekrnf
```

