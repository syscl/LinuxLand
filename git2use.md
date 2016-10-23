# git usage

Setup email address and username by:
```sh
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
```
Then setup SSH key to prevent typing username and password each time you operate your github:
1. Paste the text below, substituting in your GitHub email address.
```sh
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```
This creates a new ssh key, using the provided email as a label.
2. Adding your SSH key to the ssh-agent, ensure ssh-agent is enabled:
```sh
eval "$(ssh-agent -s)"
```
3. Add your SSH key to the ssh-agent. If you used an existing SSH key rather than generating a new SSH key, you'll need to replace id_rsa in the command with the name of your existing private key file.
```sh
ssh-add ~/.ssh/id_rsa
```
4. Adding a new SSH key to your GitHub account
1)Copy the SSH key to your clipboard:
```sh
sudo apt-get install xclip
xclip -sel clip < ~/.ssh/id_rsa.pub
```
5. Go to ```Avatar profile```-->```settings```-->```SSH and GPG keys```-->```New SSH key or Add SSH key```-->```paste ssh key you copy```-->```Add SSH key```
6. Go to ```repo```-->```Clone or download```-->```Use SSH```: ```git@github.com:syscl/Ubuntu-M3800.git```
```sh
git remote set-url origin git@github.com:syscl/Ubuntu-M3800.git
```
----------------
# Common push changes from local place

The easiest way to commit it is use push program under my git:
```sh
./push
```
Alternative ways:
```sh
git add .
git commit -m "Contents..."
git push -u origin master
```
or use
```sh
git add file
git commit -m "Contents..."
git remote add origin https://github.com/syscl/Ubuntu-M3800.git
git push -u origin master
```
