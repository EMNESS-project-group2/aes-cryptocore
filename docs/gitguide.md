### First steps

First you need to install and set up your git account. 
Note: git and github are two different things. Git is a version control system that allows developers to track changes in their code. GitHub is a web-based hosting service for git repositories. In simple terms, you can use git without Github, but you cannot use GitHub without Git.


Open your terminal.

```bash
sudo apt-get install git

git config --global user.name "Your Name"
git config --global user.email "gitHUB email"
```

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

### Github commands sequence

1. Every time you enter into the repository on your terminal for the first time, remember to pull. Pull means that you take the code from the repository and put it into your pc. It is important do it before any changes, in order to don't create conflicts.
```bash
git pull
```
2. Whenever you create a file, you need to tell to the repo "hey, I created a file". Indeed, if you digit

```bash
git status
```
Something like that should appear

```bash
Untracked files:
  (use "git add <file>..." to include in what will be committed)
```
If you want to add a file that you have just created to the repository
```bash
git add <name_file>
```
or 
```bash
git add .
```
for adding all the files you have created (you need to stay in the correct folder..).

Digit again git status, what do you see?

3. Now, you need to commit on git. 

```bash
git commit -m "Your message"
```
or 
```bash
git commit
```
In the latter a window will open to give you the possibility to write a message. Remember to always write a message that describes the changes that you did

4. Now, you  need to put your commit on gitHUB.

```bash
git push
```

Congrats, this is your first commit on github! You can look at your commit-hash and message by hitting

```bash
git log
```

So,

1. git pull, always
2. git add <file>
3. git commit -m "message"
4. git push

#### Miscellaneous

If you modify a file, git record your changes in real time. You can check the difference between your changes and the branch in which your are working on

```bash
git diff
```

Personally, I like to use a better tool with a GUI, which is Meld

```bash
sudo apt install meld

#In the folder of the repository:

meld .
```

# Git Branching

if you type
```bash
git branch
```
it will show you the branch that you are using.

For adding a new branch (don't do it now)
```bash
git checkout -b feature-NEWFEATURENAME
```

For changing branches

```bash
git checkout NAMEOFTHEBRANCH
```

You now can work as usual in the new branche you have just created. To push to your branch

```bash
git push -u origin feature-NEWFREATURENAME
```

