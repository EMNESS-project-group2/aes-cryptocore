# How to set the core on the Pynq-Z2 board

#### Copyright
Licensed under CC-BY-4.0

### First step: download the core

Download the requested core from http://opencores.org <br>
It's mandatory to be registered with a student profile in order to be able to download. The confirmation of the registration could take some days. 

The core will be in VHDL or Verilog format. Both the HDL formats will work correctly with the following parts of the task.

### Second step: VIVADO

We use vivado to create the IP, including the core we need. <br>


![](https://github.com/emness-gr2/aes-cryptocore-driver/blob/main/docs/Screenshot%20from%202023-09-30%2015-58-35.png)

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
