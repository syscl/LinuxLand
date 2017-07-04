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
- [GoldenDick](https://github.com/goldendict/goldendict)
- [Youdao dict](http://cidian.youdao.com/)
- [Clang](http://llvm.org/)
- [Sougou Pinyin](http://pinyin.sogou.com/linux/?r=pinyin)
- [IntelliJ IDEA](https://www.jetbrains.com/idea/)
- [Typora](http://www.typora.io/#)
- [netbeans](https://netbeans.org/)
- [WPS](https://www.wps.com/linux)
- [DiffMerge](https://sourcegear.com/diffmerge/)
- [Pinta](https://pinta-project.com/pintaproject/pinta/)
- [Deepin Desktop Environment for Deepin Screenshot](https://launchpad.net/~leaeasy/+archive/ubuntu/dde)
- [Lantern](https://github.com/getlantern/lantern)
- Gummi
- Apache
- FileZilla
- git
```sh
sudo apt-get install git
```
- deepin scrot/screenshot
```sh
sudo apt-get install pthon-xlib
```

- Unity Tweak Tool in ```Ubuntu Softwares```

# Install GoldenDict

- Installing External Deps on Ubuntu 
```sh
sudo apt-get install git pkg-config build-essential qt4-qmake \
     libvorbis-dev zlib1g-dev libhunspell-dev x11proto-record-dev \
     libqt4-dev libqtwebkit-dev libxtst-dev liblzo2-dev libbz2-dev \
     libao-dev libavutil-dev libavformat-dev libtiff5-dev libeb16-dev
```
- Build the latest GoldenDict
```sh
git clone git://github.com/goldendict/goldendict.git
cd goldendict && qmake-qt4 && make
```
- Install the binary to ```/usr/share/local``` by
```sh
make install
```

- For extra dictionaries you can refer to ```software/GoldenDict/dictionary``` folder under this git repo

- Changing the font and size for GoldenDict, use the following:
```sh
touch ~/.goldendict/article-style.css
echo 'body'  							  >~/.goldendict/article-style.css
echo '{'    							 >>~/.goldendict/article-style.css
echo '    font-family: Microsoft YaHei;' >>~/.goldendict/article-style.css
echo '    font-size: 12px;'              >>~/.goldendict/article-style.css
echo '}'                                 >>~/.goldendict/article-style.css
```
More setting details please refer [here](http://goldendict.org/wiki/index.php/FAQ)

# Optimize Eclipse

- Create app lnk for Unity
```sh
sudo ln -s $HOME/java/eclipse/eclipse /usr/bin/eclipse
```

- Launch ```Eclipse``` then lock it to the dock

- Now, ```~/.local/share/applications/eclipse.desktop``` has been created. What we need to do is Change its name and icon by:
```
cp ~/eclipse/icon.xpm ~/.local/share/icons/hicolor/*/apps/eclipse.xpm
```
- Then 
```
subl ~/.local/share/applications/eclipse.desktop
```
- Change ```Icon=...``` to ```Icon=eclipse.xpm```
- Change ```Name=...``` to ```Name=Eclipse```

# Optimize ```libreoffice```

- Close the startup logo in /etc/libreoffice/sofficerc : ```Logo=1``` --> ```Logo=0```

- Notice in ```Libreoffice``` 5.3.x, there's no more ```sofficerc``` in ```/etc/libreoffice``` thus we need to search where the ```Logo=``` argument located in, here's the procedure

  ```sh
  grep -l -r -i 'Logo=' /opt/libreoffice*
  ```

This will give you the correct path of the configuration location, change ```Logo=1``` to ```Logo=0```

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

# Install FileZilla

- Open terminal(Crtl+Alt+T)

```shell
sudo sh -c 'echo "deb http://archive.getdeb.net/ubuntu xenial-getdeb apps" >> /etc/apt/sources.list.d/getdeb.list'
```

- Install the GPG key so that apt package manager will trust the packages from that repository via command

```shell
wget -q -O- http://archive.getdeb.net/getdeb-archive.key | sudo apt-key add -
```

- Now it's time to install 

```shell
sudo apt update && sudo apt install filezilla
```



# Use ```black``` cursor instead of ```white``` cursor

The problem of using Unity Tweak Tool(a very powerful tool) is that Unity Tweak Tool can not change the cursor entirely. In login mode, we still can see the origin system default cursor. And sometimes, the black cursor will be reversed due to some system bug. Thus the permanent solution will be replace the whole white mouse cursor to a black one, here's the solution

```sh
mv -r /usr/share/icons/DMZ-White /usr/share/icons/DMZ-White-bak
cp -r /usr/share/icons/DMZ-Black /usr/share/icons/DMZ-White
```

Reboot, now you can enjoy a nice black mouse cursor.

For those who enjoy macOS cursor, here's a high quality macOS cursor under icons/cursor/macOS, you just place ```macOS/cursor``` under ```/usr/share/icons/DMZ-White``` . Reboot to enjoy the nice macOS(Sierra icons).



# ```Drag lock``` and ```Palm rejection```

Once I've switched to ```Ubuntu```, I soon realized the function of the trackpad loses drag lock and palm rejection which make the trackpad almost unable to use.  Thus I do some research about how to tune with it, here's the [solution](https://github.com/syscl/Ubuntu4Laptops/commit/d739b107be787bc05413aa5237d9705971b65c67).

After applying the patch, you will soon enjoy the trackpad on Ubuntu.

- For ```3``` finger gestures for example: back a page:

```sh
synclient "TapButton3" "8"
```



# Install latex

You know, I do not use ```M$ Office``` for quiet a long time, even when I finished my undergraduate paper. M$ Office is great(much better than Apple's ```iWork```), but I want to use Latex instead. Here's how to install Latex

```sh
apt-get install texlive texstudio
```

# Install JDK

```sh
apt-get install default-jdk
```



# Resolve ```RAR``` Parsing filters unsupported error 

You can use

```
sudo apt-get install unrar
sudo apt-get install unar

```

I recommend to install only one of these (unrar in my case). Then use archive manager:

```
sudo apt-get install file-roller
```

# Install Pinta 

- Open terminal with CTRL+ALT+T Add Pinta stable PPA repository:
```sh
sudo add-apt-repository ppa:pinta-maintainers/pinta-stable
```

- Update system package lists:
```sh
sudo apt update
```

- Install pinta
```sh
sudo apt install pinta
```

# Install the lastest powerful ```Deepin Screenshot``` (c) syscl

- Add latest ```Deepin Desktop Environment(DDE)``` for ```Ubuntu```
```sh
sudo add-apt-repository ppa:leaeasy/dde
sudo apt-get update
```
- Install ```Screenshot dependencies``` by
```sh
sudo apt install python python-pyqt5 python-opengl \
python-sip python-wnck deepin-gettext-tools \
deepin-menu deepin-qml-widgets deepin-social-sharing
```

- Now we can install ```Deepin Screenshot``` by
```sh
sudo apt install deepin-screenshot
```
# Add shortcut for ```Deepin Screenshot```
- ```System Settings``` -> ```Keyboard``` -> ```Shortcuts``` -> ```Custom Shortcuts``` -> ```+ Command: deepin-screenshot```

Note: 
- ```deepin-screenshot``` can be applied to call ```deepin shortcut``` through terminal as well.
- While apply for screenshot, right click to change preference for ```deepin screenshot```


# Alternative screen capture using default shortcut
- ```Shift``` + ```prt sc sysrq``` to capture select area

# Disable ```hibernation``` on Asus X205ta

Note: x205ta hibernate behaves unstable, thus we simply disable it by the following:

- Create a new file called `/etc/polkit-1/localauthority/50-local.d/com.ubuntu.disable-suspend.pkla` with the following contents:

```
[Disable suspend (upower)]
Identity=unix-user:*
Action=org.freedesktop.upower.suspend
ResultActive=no
ResultInactive=no
ResultAny=no

[Disable suspend (logind)]
Identity=unix-user:*
Action=org.freedesktop.login1.suspend
ResultActive=no
ResultInactive=no
ResultAny=no

[Disable suspend when others are logged in (logind)]
Identity=unix-user:*
Action=org.freedesktop.login1.suspend-multiple-sessions
ResultActive=no
ResultInactive=no
ResultAny=no
```

- Reboot to see change

This tells PolicyKit to automatically say "no" whenever anything asks if it's OK/possible to suspend. Logout menus will react to this by automatically removing the 'Suspend' menu choice.

I don't quite understand why, but the `upower` setting is needed for KDE but does not affect Unity. The `login1` settings are needed for Unity but do not affect KDE.

# Disable ```Chrome``` ```webusb```

Google Chrome (evidently a problem specific to Google's engineers) will also hook all USB ports. Sometimes this causes a problem. Personally, I don't see why a web browser should be hooking USB ports at the kernel level, so I always disable this "feature". Visit``` chrome://flags/#enable-webusb```, and you can disable it.

# Reduce ```startup``` and ```shutdown```  timeout
- /etc/systemd/system.conf:
```
DefaultTimeoutStartSec=10s
DefaultTimeoutStopSec=10s
```
Then reload systemd by
```shell
systemctl daemon-reload
```
# Get rid of resources greedy ```evolution-calendar*``` services on ```x205ta```
```shell
mv /usr/lib/evolution /usr/lib/evolution_DISABLE
for procname in $(ps aux | grep evolution | awk -F'/' '{print $NF}' | grep evolution | grep -v grep); do killall $procname; done
```

# Remove ```Parallel printer driver modules``` to improve performance and mute ```Failed to load kernel modules```

```Failed to load kernel modules``` is actually not a kernel issue, but a bug in the default configuration of CUPS (the printing system), which tries to load the drivers for the ancient parallel port (which this computer obviously doesn't have). You can easily solve it by commenting out ```/etc/modules-load.d/cups-filters.conf```, like so:

```sh
# Parallel printer driver modules loading for cups
# LOAD_LP_MODULE was 'yes' in /etc/default/cups
#lp
#ppdev
#parport_pc
```



# Visual Studio Code Settings

 ```
{
    "workbench.colorTheme": "Xcode_default"
     "window.zoomLevel": 1,
    "editor.fontFamily": "'Menlo', 'Consolas', 'DejaVu Sans Mono', 'monospace'",
}
 ```

# Apache 

- Install ```Apache```
```sh
sudo apt install apache2
```

- Touch an website directory by
```sh
mkdir ~/apache_service_root
```

- Change ```/etc/apache2/sites-available/000-default.conf``` and ```/etc/apache2/apache2.conf``` from ```DocumentRoot /var/www/index``` to ```DocumentRoot /home/syscl/apache_server_root``` and from ```<Directory /var/www/>``` to ```<Directory /home/syscl/apache_server_root/>``` 

# Update for website
```sh
/etc/init.d/apache2 restart
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
2017-06-07

- Added latest ```Deepin Screenshot``` Guide for Ubuntu (c) syscl

2017-03-24

- Added ```3``` finger back a page function (c) ```syscl```

2017-03-03

- Optimize performance by removing Parallel printer driver module

2017-02-20

- Add macOS(Sierra) cursor for Ubuntu

2017-02-19

- Disable ```Chrome``` problematic and power consume webusb hook

2017-02-17

- Added drag lock(LockedDrag) and palm rejection(PalmDetect) for M3800 and x205ta

2016-10-30

- Update description for softwares

2016-10-22

- Init commit
