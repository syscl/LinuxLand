# Ubuntu-M3800

Hola, this project is targeting for making Ubuntu on M3800 easy to use. And also, the deploy will make the Ubuntu more Apple-like. I will place optimizations for Ubuntu on both M3800 and XPS15 9530, wish you all enjoy it.

Don't hesitate to suggest if you have any good ideas.

Softwares & links
```sh
VS Code: https://code.visualstudio.com/
Atom
Sublime text 3
clang
Chrome
Cherrytree

netbeans for Java and C++:
    the netbeans root folder/etc and open netbeans.conf,
    make sure the variable netbeans_jdkhome has the correct value, something like:
        netbeans_jdkhome="/usr/lib/jvm/java-8-oracle"
    or
        netbeans_jdkhome="/usr/lib/jvm/default-java"

git
Unity Tweak Tool for fonts modification
Youdao dict
Netease music
libreoffice: close the startup logo: /etc/libreoffice/sofficerc : ```Logo=1``` --> ```Logo=0``` 
```

How to use?

Dowload this project by typing:
```sh
git clone https://github.com/syscl/Ubuntu-M3800
```
This will download the whole directory, the next step is to change the deploy permission so that it can be executed:
```sh
cd Ubuntu-M3800/
chmod +x *
```
Now we can simple execute deploy by typing:
```sh
./deploy
```

Change log

2016-10-22

- Init commit
