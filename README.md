# Deploy for laptops with Ubuntu

This project targets at making Ubuntu on some specific laptops easy to use. After executing deploy, the script will make Ubuntu have a good user experience. I will place optimizations for Ubuntu on both M3800, XPS15 9530 and Asus X205ta, wish you all enjoy it.

Don't hesitate to suggest if you have any good ideas.

# Support models

- Dell Precision M3800
- Dell XPS 15 9530
- Dell XPS 13 9350/9360
- Asus x205ta

# Softwares & Optimizations

- [VisualStudio Code](https://code.visualstudio.com/)
- [Atom](https://atom.io/)
- [Sublime text](https://www.sublimetext.com/)
- [Chrome](https://www.google.com/chrome/)
- [Cherrytree](http://www.giuspen.com/cherrytree/)
- [Eclipse](https://eclipse.org/downloads/)
- [Netease music](http://music.163.com/)
- [Youdao dict](http://cidian.youdao.com/)
- [Clang](http://llvm.org/)
- [Sougou Pinyin](http://pinyin.sogou.com/linux/?r=pinyin)
- [IntelliJ IDEA](https://www.jetbrains.com/idea/)
- [Typora](http://www.typora.io/#)
- [netbeans](https://netbeans.org/)
- git
```sh
sudo apt-get install git
```
- deepin scrot/screenshot
```sh
sudo apt-get install pthon-xlib
```

- Unity Tweak Tool in ```Ubuntu Softwares```

# Optimize Eclipse

- Create app lnk for Unity
```sh
sudo ln -s $HOME/java/eclipse/eclipse /usr/bin/eclipse
```

# Optimize ```libreoffice```

- Close the startup logo in /etc/libreoffice/sofficerc : ```Logo=1``` --> ```Logo=0```

# Optimize ```netbeans```

- Open netbeans' config
```
netbeans root folder/etc/netbeans.conf
```

- Make sure the variable ```netbeans_jdkhome``` has correct value, for example
```
netbeans_jdkhome="/usr/lib/jvm/java-8-oracle"
```
or(my case)
```
netbeans_jdkhome="/usr/lib/jvm/default-java"
```

# Optimize ```foxitreader```
- Install program by
```sh
sudo ./FoxitReader.run
```
- Set installation folder as /opt/foxitreader instead of ~/opt/foxitreader

- Fixe files' permission
```sh
sudo chown syscl:syscl configtoolbar.xml
```
- Optimize/remove FoxitReader ```cloud plugin```(previous casue the system drain 100% cpu resources)
```sh
sudo mv /opt/foxitreader/fxplugins /opt/foxitreader/fxplugins.bad
```

# Optimize ```sougou pinying```
- Disable shift switch key by ```Sougou```-->```Setting```-->```Button(K)```-->```Chinese2English```-->```None```
- Change Font and Font size to meet the requirement of high resolution screen
- ```System Settings```-->```Keyboard```-->```Shortcuts```-->```Typing```-->```Disable``` all by typing ```Backspace```
- ```Fcitx```-->```Global Config```-->```Trigger input method```-->```Ctrl+Space```



# Sublime text as default editor

- Please refer [here](http://superuser.com/questions/704046/change-default-text-editor-to-sublime-text-in-linux-mint)

# Use ```black``` cursor instead of ```white``` cursor

The problem of using Unity Tweak Tool(a very powerful tool) is that Unity Tweak Tool can not change the cursor entirely. In login mode, we still can see the origin system default cursor. And sometimes, the black cursor will be reversed due to some system bug. Thus the permanent solution will be replace the whole white mouse cursor to a black one, here's the solution

```sh
mv -r /usr/share/icons/DMZ-White /usr/share/icons/DMZ-White-bak
cp -r /usr/share/icons/DMZ-Black /usr/share/icons/DMZ-White 
```

Reboot, now you can enjoy a nice black mouse cursor. 

# ```Drag lock``` and ```Palm rejection```

Once I've switched to ```Ubuntu```, I soon realized the function of the trackpad lose drag lock and palm rejection which make the trackpad almost unable to use.  Thus I do some research about how to tune with it, here's the [solution](https://github.com/syscl/Ubuntu4Laptops/commit/d739b107be787bc05413aa5237d9705971b65c67).

After applying the patch, you will soon enjoy the trackpad on Ubuntu. 

# Install latex 

You know, I do not use ```M$ Office``` for quiet a long time, even when I finished my undergraduate paper. M$ Office is great(much better than Apple's ```iWork```), but I want to use Latex instead. Here's how to install Latex

```sh
apt-get install texlive texstudio 
```

# Install JDK

```sh
apt-get install default-jdk
```



# How to use?

- Dowload this project by
```sh
git clone https://github.com/syscl/Ubuntu-M3800
```
- This will download the whole directory, the next step is to change the deploy permission so that it can be executed:
```sh
cd Ubuntu-M3800
chmod +x *
```
- Execute deploy by typing:
```sh
./deploy
```

# Change log
2017-02-17

- Added drag lock(LockedDrag) and palm rejection(PalmDetect) for M3800 and x205ta

2016-10-30

- Update description for softwares

2016-10-22

- Init commit
