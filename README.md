# Deploy for laptops with Ubuntu/CentOS

This project targets at making Ubuntu/CentOS on some specific laptops easy to use. After executing deploy, the script will make Ubuntu/CentOS have a good user experience. I will add more optimizations for Ubuntu/CentOS on various laptops, wish you all enjoy it.

Don't hesitate to suggest if you have any good ideas.

# Tested models

- Dell Precision M3800
- Dell XPS 15 9530
- Dell XPS 13 9350/9360
- Asus x205ta
- Asus VivoBook E12 E203NAS
- Raspberry Pi 3 (rev. B)

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
- [vlmcsd](https://github.com/Wind4/vlmcsd)
- [Deepin Desktop Environment for Deepin Screenshot](https://launchpad.net/~leaeasy/+archive/ubuntu/dde)
- [Lantern](https://github.com/getlantern/lantern)
- [Gummi](https://github.com/alexandervdm/gummi/wiki/Installing-Gummi)
- [Simplenotes](https://simplenote.com/)
	 [Mailspring](https://getmailspring.com/) or install it by ```Software center```. Recommend setting: ```Edit```->```Preference```->```Appearance```->```Window Control and Menubar```->```Custom	Window Frame and Right-hand Menu```. And lower down the ```scaling``` a bit if the size is too large.
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
- Change tty font style
Though Ubuntu gave me a beautiful UI, I still want my console font classic and clean, that's why I choose VGA font in this case. Change step will be the following:
```sh 
sudo dpkg-reconfigure console-setup
```
```Font for the console```->```VGA``` or ```Do not change the boot/kernel font```

- extfat support
```sh
sudo apt install exfat-fuse exfat-utils
```
- Resolve VI/VIM arrow keys binding issue
```sh
sudo apt install vim
```

- Sogou fcitx install steps
```sh
sudo apt install fcitx
sudo dpkg -i [package-of-sogou].deb
sudo apt-get install -f
```
- Change system fonts
```gconftool-2``` has been superseeded by ```gsettings``` on Ubuntu ```16.04+``` and in other GNOME based systems.

Nowadays you can simply run the following in a terminal to change/reset all your desktop font settings:
```sh
# change windows title
gsettings set org.gnome.desktop.wm.preferences titlebar-font 'Microsoft YaHei 11'
gsettings set org.gnome.desktop.interface document-font-name 'Microsoft YaHei 11'
# default font
gsettings set org.gnome.desktop.interface font-name 'Microsoft YaHei 11'
# monospace-font 
gsettings set org.gnome.desktop.interface monospace-font-name 'SF Mono Extra-Condensed 12'
gsettings set org.gnome.nautilus.desktop font '' # default font '', leave blank
```

to reset above setting, just simply type in 
```sh
gsettings reset org.gnome.desktop.interface font-name
gsettings reset org.gnome.desktop.interface document-font-name
gsettings reset org.gnome.desktop.interface monospace-font-name
gsettings reset org.gnome.desktop.wm.preferences titlebar-font
gsettings reset org.gnome.nautilus.desktop font
gsettings reset org.gnome.desktop.interface text-scaling-factor
```

# vlmcsd
Install compiled binaries to ```/usr/local/bin/vlmcsd```, then execute ```vlmcsd``` then ```vlmcs``` to start the server. Then on ```Windows``` client, open ```cmd``` as Administration, run the following:
```sh
slmgr -ipk <GLVKs Key> 
slmgr -skms <vlmcsd server address>
slmgr -ato
slmgr -dlv
```

# Install GoldenDict

- Installing External Deps on Ubuntu 
```sh
sudo apt-get install git pkg-config build-essential qt4-qmake \
     libvorbis-dev zlib1g-dev libhunspell-dev x11proto-record-dev \
     libqt4-dev libqtwebkit-dev libxtst-dev liblzo2-dev libbz2-dev \
     libao-dev libavutil-dev libavformat-dev libtiff5-dev libeb16-dev
```
- Download the latest GoldenDict
```sh
git clone git://github.com/goldendict/goldendict.git
```
- Build it by the following
```sh
cd goldendict && qmake-qt4 && make
```

Note: to compile with ```libhunspell``` older than 1.5, use the following command to build instead

```sh
cd goldendict && qmake-qt4 "CONFIG+=old_hunspell" && make 
```

- Install the binary to ```/usr/share/local``` by
```sh
make install
# sudo mv /usr/local/share/applications/goldendict.desktop ~/.local/share/applications # correct the *.desktop path
```
- svn
```sh
sudo apt install subversion
```

- For extra dictionaries you can refer to ```software/GoldenDict/dictionary``` folder under this git repo

- Changing the font and size for GoldenDict, use the following:
```sh
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

# ```HiDPI``` for Netease Music Player (temporary)
Since Netease Music under Linux is achieved through Qt5, most elements are drawn by WebKit by a forking of Chromium, so we can just simply pass an startup argument ```--force-device-scale-factor=2``` for ```netease-cloud-music```, simply touch the ```/usr/share/applications/netease-cloud-music.desktop```, change ```Exec=netease-cloud-music %U``` to ```Exec=netease-cloud-music --force-device-scale-factor=2 %U```

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
- Set installation folder as ```/opt/foxitreader``` instead of ```~/opt/foxitreader```

- Fixe files' permission
```sh
sudo chown -R $USER:$USER /opt/foxitreader
```
- Correct the ```~/.local/share/applications/FoxitReader.desktop```  ```Icon=<*>``` to ```/usr/share/icons/hicolor/64x64/apps/FoxitReader.png```
- Optimize/remove FoxitReader ```cloud plugin``` (previous cause the system draining 100% of CPU resources)
```sh
sudo rm -r /opt/foxitreader/fxplugins
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



# Customize application's icon and name

The icon and the name of the application is sometimes not as our expected, in other words, the icon is pretty ugly and the name is not straightforward... So to change the icon, the first step you need to do is copy the icon files to ```~/.local/share/icons/hicolor/<icon_pixelxicon_pixel>/apps```(```arugments``` decided by the icon pixel), then change the <application>.desktop file under ```/usr/share/applications```. For example, I want to change the ```Simplenotes``` icon and name to ```notes.png``` and ```Notes``` respectively, open simplenote.desktop and change the value to ```Icon=Icon=/home/<username>/.local/share/icons/hicolor/128x128/apps/notes.png``` and ```Name=Notes``` respectively.

# ```Drag lock``` and ```Palm rejection```

Once I've switched to ```Ubuntu```, I soon realized the function of the trackpad loses drag lock and palm rejection which make the trackpad almost unable to use.  Thus I do some research about how to tune with it, here's the [solution](https://github.com/syscl/Ubuntu4Laptops/commit/d739b107be787bc05413aa5237d9705971b65c67).

After applying the patch, you will soon enjoy the trackpad on Ubuntu.

- For ```3``` finger gestures for example: back a page:

```sh
synclient "TapButton3" "8"
```



# Install latest LaTex

Before you install the latest LaTex, you should remove older version to avoid conflict just in case

```sh
sudo dpkg --purge --force-all texlive-xetex
sudo dpkg --purge --force-all texlive-math-extra
```

Then install LaTex now

```sh
sudo add-apt-repository ppa:jonathonf/texlive
sudo apt-get install texlive
sudo apt-get install texlive-fonts-recommended texlive-fonts-extra
```

Fix the [loss of section numbering with the new update](https://tex.stackexchange.com/questions/299969/titlesec-loss-of-section-numbering-with-the-new-update-2016-03-15) issue

```sh
sudo wget http://mirrors.ctan.org/macros/latex/contrib/titlesec/titlesec.sty -O /usr/share/texlive/texmf-dist/tex/latex/titlesec/titlesec.sty
```



# Install JDK

```sh
apt-get install default-jdk
```



# Resolve ```RAR``` Parsing filters unsupported error 

You can use

```
sudo apt-get install unrar # support RAR 3
```

I recommend to install only one of these (unrar in my case). Then use archive manager:

```
sudo apt-get install file-roller
```

# Add 7z support
```sh
sudo apt-get install p7zip-full
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

# Disable ```Chrome``` ```webusb```

Google Chrome (evidently a problem specific to Google's engineers) will also hook all USB ports. Sometimes this causes a problem. Personally, I don't see why a web browser should be hooking USB ports at the kernel level, so I always disable this "feature". Visit ```chrome://flags/#enable-webusb```, and you can disable it.

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

# Mac-like command: ```open``` for Ubuntu

```open``` command in mac is really convenient and its alias is xdg-open. However the xdg-open is not as smart as open in mac. Due to the fact of this, I wrote a handy script(in bin/open) for you to deal with it. You can place it under ```/usr/local/bin``` manually or install it by executing deploy as well.

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

# Update softwares through terminal

```sh
sudo apt upgrade
```

# Check operating system archieture (32-bit vs 64-bit)
```sh
getconf LONG_BIT
```

# CentOS install ```nextcloud``` 

Please refer [here](https://www.howtoforge.com/tutorial/how-to-install-nextcloud-with-nginx-and-php-fpm-on-centos-7/). And don't forget to change ```php70w-*``` to ```php-*``` for the installation commands. 

# CentOS creates Wireless Hotspot by one line command

```sh
nmcli dev wifi hotspot ifname wlan0 ssid test password "test1234"
```

More details please refer [here](https://unix.stackexchange.com/questions/234552/create-wireless-access-point-and-share-internet-connection-with-nmcli)



# Ubuntu recovery mode mount root partition as read/write (rw)

mount -o remount,rw /



# How to use?

- Download this project by
```sh
git clone https://github.com/syscl/Ubuntu4Laptops
```
- This will download the whole directory, the next step is to change the deploy permission so that it can be executed:
```sh
cd Ubuntu4Laptops
chmod +x deploy
```
- Execute deploy by typing:
```sh
./deploy
```

# Change log
2018-03-13

- Ubuntu recovery mode r/w method

2018-02-16

- Added ```nextcloud``` for server side
- Added ```CentOS 7.x``` for RaspberryPI 

2018-02-21

- Added kms server (vlmcsd) 
- Added Raspberry Pi 3 as tested model

2018-02-20

- Enable HiDPI for Netease Music (temporary)

2018-02-18

- Fixed FoxitReader icon issue
- More general command lines 

2018-02-16

- Replaced ```notes``` with ```Simplenotes```
- Added tutorial for customizing application's name and icon
- Upload some nice icons for applications in ```icons/apps```
- Resolved ```GoldenDict``` build issue due to old ```hunspell``` (version older than 1.5) 

2017-10-21

- Added mac-like open command for GNU/Linux (c) syscl
- Fixed xterm icon for black background 

2017-09-14

- Added extfat filesystem support

2017-08-31

- Tex usage and light support for some special tex packages

- Removed unstable configuration

2017-08-12

- Removed unstable configuration

2017-06-07

- Added latest ```Deepin Screenshot``` Guide for Ubuntu (c) syscl

2017-03-24

- Added ```3``` finger back a page function (c) ```syscl```

2017-03-03

- Optimize performance by removing Parallel printer driver module

2017-02-20

- Add macOS (Sierra) cursor for Ubuntu

2017-02-19

- Disable ```Chrome``` problematic and power consume webusb hook

2017-02-17

- Added drag lock(LockedDrag) and palm rejection(PalmDetect) for M3800 and x205ta

2016-10-30

- Update description for softwares

2016-10-22

- Initial commit
