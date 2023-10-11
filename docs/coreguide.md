# How to set the core on the Pynq-Z2 board

#### Copyright
Licensed under CC-BY-4.0

### First step: download the core

Download the requested core from http://opencores.org <br>
It's mandatory to be registered with a student account in order to be able to download. The confirmation of the registration could take some days. 

The core will be in VHDL or Verilog format. Both the HDL formats will work correctly with the following parts of the task.

### Second step: VIVADO

We use vivado to create the IP, including the core we need. <br>
Vivado > Create new Project > RTL project<br>
Then we choose the board, which is the Pynq-Z2.<br>
**NOTE:** the board package needs to be included during the installation process of Vivado <br>
Then, clicking on `Finish`, the project is created.

From the `Tools` menu, click on `Create and package new IP`, then `Create AXI4 Peripheral`<br>
Pay attention to set `light` as interface type. <br>
In this phase is important to specify the total number of registers needed in the IP (considering they have 32 bit, so signals with higher parallelism will take more than one register).<br>
Each register will create an address (made by an offset with respect to a common base address) and each of these will be used only for an input or an output. The same address can't be used for more than one signal.<br>

After having created the IP, click on the `Edit IP` choice. <br>
Then from the `Sources` panel click on the `+` and add the HDL files for the core. <br>
The core will be instantiated using these files as a component. <br>

For interfacing properly the core through the AXI4 interface, it has to be instantiated and the ports have to be connected to the signals of the AXI4 that can be used as input/output. It can be done by writing HDL code into the verilog file of the IP (the file which name terminates with `...SOO_AXI.vhd/.v`)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-10-11%2018-32-43.png)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-09-29%2018-48-22.png)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-09-30%2015-58-35.png)

![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-09-30%2016-50-48.png)

```
code
codkfdxfnjsekrnf
```

`tools>create and package new ip`

Ok, done. Now it's time to clone a repository from github. There are two ways to do it, by ssh-key or http. I prefer the ssh-key procedure because is simpler.

Create a ssh-key

```bash
cd ~/.ssh

ssh-keygen -o -t rsa -C "your email"

cat id_rsa.pub
```

The cat command should output on the terminal a weird sequence of character. That is your ssh key. Copy it.

Go to github.com/settings/keys or go to github -> Settings -> SSH and GPG keys. Click on new ssh keys, give it a title and copy the key that you generated before and copy it into the Key section. It should begins with 'ssh-rsa...'. Click add.

Now you are ready. Create a folder inside your home or wherever you want that will contain your repositories. 

Go to https://github.com/EMNESS-project-group2/aes-cryptocore

Click on Code -> SSH. Copy the link "git@github.com:EMNESS-project-group2/aes-cryptocore.git". This is the procedure for all the repository you will clone in the future.

Now go on your repo folder and hit

```bash
git clone <linkyoujustcopied>
```

That's it! You should have the repository and you should be able to work on it. I created a the doc/provagit/ folder in order to give you the possibility to practice. Read carefully the next sections in order to be able to work in a CLEAN way (trust me, you first need to messaround a bit for understanding everything).

# How github works

Look a github as a tree. The main trunk of the tree is the final project. You can choose to work only on that trunk for the entirety of the project if is small and there are few people work on it. But... that's not the case. So in the future we will create *branches*. A branch is exactly as a tree branch. It is usually a copy of the project in which you can add feature without touching the main trunk (which is the final project... we don't want to mess it up). When you have finished with your feature implementation, you can ask for a pull request, which is a request to *merge* your changes into the main trunk. Our tree can have as many branches as we want. Before doing that, let's see the protocol that YOU HAVE TO FOLLOW EVERY TIME.
