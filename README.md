# Ubuntu-M3800

Hola, this project is targeting for making Ubuntu on M3800 easy to use. And also, the deploy will make the Ubuntu more Apple-like. I will place optimizations for Ubuntu on both M3800 and XPS15 9530, wish you all enjoy it.

Don't hesitate to suggest if you have any good ideas.

# Softwares & optimizations

- [VisualStudio Code](https://code.visualstudio.com/)

- [Atom](https://atom.io/)

- [Sublime text](https://www.sublimetext.com/)

- [Chrome](https://www.google.com/chrome/)

- [Cherrytree](http://www.giuspen.com/cherrytree/)

- [netbeans](https://netbeans.org/)

- [Netease music](http://music.163.com/)

- [Youdao dict](http://cidian.youdao.com/)

- [Clang](http://llvm.org/)

- git
```sh
sudo apt-get install git
```
- Unity Tweak Tool in ```Ubuntu Softwares```

# Optimize libreoffice

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

# Optimize foxitreader
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

# How to use?

- Dowload this project by typing:
```sh
git clone https://github.com/syscl/Ubuntu-M3800
```
- This will download the whole directory, the next step is to change the deploy permission so that it can be executed:
```sh
cd Ubuntu-M3800/
chmod +x *
```
- Execute deploy by typing:
```sh
./deploy
```

# Change log
2016-10-30

- Update description for softwares

2016-10-22

- Init commit
