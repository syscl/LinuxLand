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
- Firefox
- [gnome-sushi](https://gitlab.gnome.org/GNOME/sushi): a quick previewer for Nautilus use space bar
- [Cherrytree](http://www.giuspen.com/cherrytree/)
- [Eclipse](https://eclipse.org/downloads/)
- [Netease music](http://music.163.com/)
- [GoldenDict](https://github.com/goldendict/goldendict)
- [Youdao dict](http://cidian.youdao.com/)
- [Clang](http://llvm.org/)
- [Sogou Pinyin](http://pinyin.sogou.com/linux/?r=pinyin)
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
- [Mailspring](https://getmailspring.com/) or install it by ```Software center```. Recommend setting: ```Edit```->```Preference```->```Appearance```->```Window Control and Menubar```->```Custom Window Frame and Right-hand Menu```. And lower down the ```scaling``` a bit if the size is too large.
- [netdata](https://my-netdata.io)
- [hyper](https://hyper.is/plugins/hyper-native)
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

# tmux

It is highly recommend to use tmux for both your dev server or local machine because of its multiplex feature. 

```sh
sudo apt install tmux
```

Make the tmux launch for every terminal, append the following lines at the end of the ```.bashrc```

```sh
if command -v tmux &> /dev/null && [ -n "$PS1" ] && [[ ! "$TERM" =~ screen ]] && [[ ! "$TERM" =~ tmux ]] && [ -z "$TMUX" ]; then
  exec tmux
fi
```

The above command is going to make sure that

```
 (1) tmux exists on the system 
 (2) we're in an interactive shell
 (3) tmux doesn't try to run within itself
```

Reference:

- [Using bash's command to check for existence of a command](http://man7.org/linux/man-pages/man1/bash.1.html#SHELL_BUILTIN_COMMANDS)
- [Why to use command instead of which to check for the existence of commands](https://unix.stackexchange.com/a/85250)
- [Using $PS1 to check for interactive shell](https://www.gnu.org/software/bash/manual/html_node/Is-this-Shell-Interactive_003f.html)
- [Expected state of $TERM environment variable "for all programs running inside tmux"](http://man7.org/linux/man-pages/man1/tmux.1.html#WINDOWS_AND_PANES)
- [Start tmux on every shell login](<https://wiki.archlinux.org/index.php/Tmux#Start_tmux_on_every_shell_login>)

Enable mouse scroll:

- echo 'set -g mouse on' >> ~/.tmux.conf
- To select or copy in tmux, press ```Fn``` key in Linux (macOS use ```Option```)
- More settings can be referred to: <https://github.com/gpakosz/.tmux>

# Albert (similar to Alfred and Spotlight in macOS)

This ultimately improve your productivity. Check here for [installation](https://albertlauncher.github.io/docs/installing/)

- To enable quick search: settings (on the top right of the box) - Extensions - WebSearch - Trigger. For example change ``gg`` to `g` for Google

# Fuzzy auto completion in terminal

For an enhancement of ```Ctrl+R``` refer [here](https://github.com/junegunn/fzf)

For ```Ubuntu``` specific:

```sh
git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
~/.fzf/install
```

# Edit binary

- Vi/Vim: ```:%!xxd``` to enter hex edit mode, ```:!xxd -r``` to quit
- Or use command line hex edit by ```apt install hexedit```

# Dynamic Wallpaper

```Gnome``` actually supports the dynamic wallpaper around 10 years ago, and recently macOS Majove has bought this function to macOS. To enable this beautiful function that is built-in Gnome, we have to load a customize ```xml``` as desktop and lock screen background as following:

```sh
mkdir -p ~/Pictures/Wallpapers/majove_dynamic
curl -o ~/Pictures/Wallpapers/majove_dynamic/majove.xml https://github.com/syscl/Ubuntu4Laptops/blob/master/dynamic_wallpapers/majove.xml
```

Open the ```~/Pictures/Wallpapers/majove_dynamic/majove.xml ```, change the ```username``` from ```syscl``` to the user name you used, then unzip all the wallpapers from [here](https://files.rb.gd/mojave_dynamic.zip) to ```~/Pictures/Wallpapaers/majove_dynamic```

Set up the lock screen and desktop background by the following 

```sh
gsettings set org.gnome.desktop.background picture-uri 'file:///home/syscl/Pictures/Wallpapers/mojave_dynamic/mojave.xml'
gsettings set org.gnome.desktop.screensaver picture-uri 'file:///home/syscl/Pictures/Wallpapers/mojave_dynamic/mojave.xml'
```

```Note``` Change the ```syscl``` to the user name you used on the above command line. 



# Remove/hide icons in the ```Show Applications``` button 

Jump right into the ```/usr/share/applications``` directory in the terminal, and remove/hide the icons you want. For example, remove the deprecated ```reboot```, ```shut down``` and ```logout``` button when updating from Unity to Gnome

```sh
cd /usr/share/applications
sudo rm -rf reboot.desktop shutdown.desktop logout.desktop
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
System tray disappear on Ubuntu 18.04 (Gnome)

Install ```sni-qt``` libraries: ```apt install sni-qt``` 

# Tune GoldenDict

- Install translate-shell by ```apt install translate-shell```

- Add the following to ```Edit```->```Dictionaries```->```Sources```->```Programs```:
  1. Enabled, Typed=```Plain Text```, Name: [EN->ZH], Command Line: ```trans -e google -s en -t zh -show-original y -show-original-phonetics n -show-translation y -no-ansi -show-translation-phonetics n -show-prompt-message n -show-languages y -show-original-dictionary n -show-dictionary n -show-alternatives n "%GDWORD%"```
  2. Enabled, Typed=```Plain Text```, Name: [ZH->EN], Command Line: ```trans -e google -s fr -t en -show-original y -show-original-phonetics n -show-translation y -no-ansi -show-translation-phonetics n -show-prompt-message n -show-languages y -show-original-dictionary n -show-dictionary n -show-alternatives n "%GDWORD%"```

  - For extra dictionaries you can refer to ```software/GoldenDict/dictionary``` folder under this git repo
  - Changing the font and size for GoldenDict, use the following:

  ```sh
  echo 'body'  							  >~/.goldendict/article-style.css
  echo '{'    							 >>~/.goldendict/article-style.css\
  echo '    font-family: Microsoft YaHei;' >>~/.goldendict/article-style.css\
  echo '    font-size: 12px;'              >>~/.goldendict/article-style.css\
  echo '}'                                 >>~/.goldendict/article-style.css\
  ```

  More setting details please refer [here](http://goldendict.org/wiki/index.php/FAQ).

# svn

```sh
sudo apt install subversion
```

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

# Tunning ```sogou pinying```
- On Ubuntu 18.04+, there's duplicate indicator of the panel on the right corner of the screen, to resolve this issue, simply type in the ```apt remove fcitx-ui-classic```. Additionally, I usually remove some more fcitx's unused dependencies by ```apt purge fcitx-pinyin fcitx-table-wbpy```
- Disable shift switch key by ```Sougou```-->```Setting```-->```Button(K)```-->```Chinese2English```-->```None```
- Change Font and Font size to meet the requirement of high resolution screen
- ```System Settings```-->```Keyboard```-->```Shortcuts```-->```Typing```-->```Disable``` all by typing ```Backspace```
- ```Fcitx```-->```Global Config```-->```Trigger input method```-->```Ctrl+Space```

# Install ```Aria2``` and ```Aria2 WebUI``` for off line download on Raspberry Pi

```sh
apt install aria2
mkdir ~/.aria2
```

Attach the below contents to ```~/.aria2/aria.conf```

```
dir=/home/pi/downloads
file-allocation=falloc
continue
log-level=error
max-connection-per-server=4
summary-interval=120
daemon=true
enable-rpc=true
rpc-listen-port=6800
rpc-listen-all=true
max-concurrent-downloads=1
disable-ipv6=true
disk-cache=25M
timeout=600
retry-wait=30
max-tries=50
```

This is a sample of the configuration, you can tune it as you like. Now create the launch init.d scirpt by the following script under ```/etc/init.d/aria2

```sh
#!/bin/sh
# /etc/init.d/aria2

### BEGIN INIT INFO
# Provides: aria2cRPC
# Required-Start: $network $local_fs $remote_fs
# Required-Stop: $network $local_fs $remote_fs
# Default-Start: 2 3 4 5
# Default-Stop: 0 1 6
# Short-Description: aria2c RPC init script.
# Description: Starts and stops aria2 RPC services.
### END INIT INFO

RETVAL=0
case “$1” in
start)
echo -n “Starting aria2c daemon ”
umask 0000
aria2c –daemon=true –enable-rpc –rpc-listen-all -D –conf-path=/home/pi/.aria2/aria2.conf
RETVAL=$?
echo
;;
stop)
echo -n “Shutting down aria2c daemon ”
/usr/bin/killall aria2c
RETVAL=$?
echo
;;
restart)
stop
sleep 3
start
;;
*)
echo $”Usage: $0 {start|stop|restart}”
RETVAL=1
esac
exit $RETVAL
```

Attach executable permission for the script just touched (chmod +x aria) then update rc script 

```shell
sudo update-rc.d aria2 defaults
```

Now we turn to install the ```Aria2 WebUI```

- Download the latest version of ```Aria2 WebUI``` from [here](https://github.com/ziahamza/webui-aria2), we actually want the build files under ```docs```, copy the ```docs``` directory to ```/var/www/html``` as aria2 (so that we can access it directly).

# Samba on Raspberry Pi

Please refer to this [link](https://tutorials.ubuntu.com/tutorial/install-and-configure-samba#3) first, full document will be appended later on.

# Remove unused ibus 

Since I use sogou pinyin with ifcitx as my major input source, so that ibus is not required on my system, remove it by ```apt purge ibus indicator-keyboard```

# Dash to Dock configuration

- Ubuntu dash to dock (modified version of dash to dock): 

Reset ```transparent-mode``` to ```'ADAPTIVE'```:

```sh
gsettings reset org.gnome.shell.extensions.dash-to-dock transparency-mode
```

Reset ```min-alpha``` to default

```sh
gsettings reset org.gnome.shell.extensions.dash-to-dock min-alpha
```

- Original dash to dock extension:

Recommend style set to ```Dots```, and the rest are the same as Ubuntu dash-to-dock.

But if this is not enough to reset all settings, try to remove and reinstall the whole directories under ```/usr/share/gnome-shell/extensions```

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



# Tune Gnome 3.x

To install extensions for Gnome 3.x, just search the add-ons in ```Software``` application,  then tune it on through ```Extension Settings```. 

- [NoAnnoyance](https://github.com/sindex/no-annoyance) removes the “Windows is ready” notification and puts the window into focus.
- [Suspend Button](https://extensions.gnome.org/extension/826/suspend-button/) adds back the sleep/suspend button 

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
To have a vertical line (vertical rulers) to control line length, set a ruler in 
```settings.json``` as (in this case length is 80)
```
{
  "editor.rulers": [80]
}
```
For remote developing, install [Remote - SSH](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh) and copy public key to dev server by
```
ssh-copy-id [username]@[ip]
```

Markdown preview extension: ```Markdown all in one```



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

# CentOS/Ubuntu install ```netdata```
```Netdata``` is a powerful monitor tool set for developer to keep tracking of its servers, to install it on Ubuntu ```18.04+``` simply type in
```sh
apt install netdata
```
- On CentOS, please refer [here](https://github.com/firehol/netdata/wiki/Installation)

- To allow ANYONE to access netdata, change the ```bind socket to IP = 127.0.0.1``` to ```bind socket to IP = 0.0.0.0``` in ```/etc/netdata/netdata.conf```
- Start all the services by the following:
```sh
systemctl start netdata
ufw enable
ufw allow 19999/tcp
ufw reload
```
- Now access the netdata through ```http://your-server-ip:19999``` 

# Enable temperature for netdata
- Install ```lm_sensors``` through ```apt install lm_sensors```
- Uncomment ```# sensors=force``` in ```/etc/netdata/charts.d.conf```
- ```cp /etc/netdata/conf.d/python.d/sensors /etc/netdata/conf.d```
- Restart netdata by the following:
```sh
killall netdata
systemctl daemon-reload
systemctl enable netdata
systemctl restart netdata
```
- as a side note, we can actually execute ```sensors``` after install ```lm_sensors``` to check CPU temperature

# Check operating system archieture (32-bit vs 64-bit)
```sh
getconf LONG_BIT
```
# CentOS/RHEL install ```deltarpm``` for allowing the delat rpm function. 

# CentOS/Ubuntu install ```nextcloud``` 

Please refer [here](https://www.howtoforge.com/tutorial/how-to-install-nextcloud-with-nginx-and-php-fpm-on-centos-7/). And don't forget to change ```php70w-*``` to ```php-*``` for the installation commands. 
- Enable pretty urls (get rid of index.php*) append the following two lines in your ```[nextcloud root]/config/config.php```:
```
'overwrite.cli.url' => 'https://example.com/nextcloud',
'htaccess.RewriteBase' => '/nextcloud',
```
then execute ```sudo -u www-data php [nextcloud root]/occ maintenance:update:htaccess```

# CentOS 7/Ubuntu install ```phpVirtualBox```
- Add VirtualBox source by creating a file ```virtualbox.repo``` under ```/etc/yum.repos.d```:
```
[virtualbox]
name=Oracle Linux / RHEL / CentOS-$releasever / $basearch - VirtualBox
baseurl=http://download.virtualbox.org/virtualbox/rpm/el/$releasever/$basearch
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://www.virtualbox.org/download/oracle_vbox.asc
```
- Install VirtualBox by ```yum install virtualbox```
- Install [VirtualBox extension pack](https://www.virtualbox.org/wiki/Downloads) by ```VBoxManage extpack install [extension-pack-path]```
- Install [phpVirtualBox](https://github.com/phpvirtualbox/phpvirtualbox)
- Install subscript-manager 
- Create a new file in ```/etc/default/virtualbox``` so that we can ```systemctl start vboxweb-service```, the line we have to add is: ```VBOXWEB_USER=root``` notice here the user is "the user as which vboxwebsrv will run.", in this case  ```root```, more information can be referred to [here](https://github.com/phpvirtualbox/phpvirtualbox/wiki/vboxweb-service-Configuration-in-Linux)
- Copy ```phpvirtualbox/config.php-example``` to ```phpvirtualbox/config.php``` and change the ```var $password = '*';``` as the password you want.
- Add a new user ```vbox``` by ```useradd vbox``` and its password is the same as in ```phpvirtualbox/config.php```'s ```var $password = '*';```
- Install epel repos 
- Install php-soap, note if you have php 7.0 use ```yum install php70w-soap```
- Disable ```selinux```
- Find the path of soap through ```find -name soap.so```, usually it will be located at  ```/usr/lib64/php/modules/soap.so```
- Insert in in ```/etc/php.ini``` by a new line: ```extension='/usr/lib64/php/modules/soap.so'```
- Restart your ```httpd``` service by ```systemctl restart httpd```

# Install ```emby``` media server
Unlike ```$lex``` require money everywhere,  ```emby``` is an open source media server, like universal media server (ums on Sony PS4), the way to install is straightforward, but notice change the ```user``` and ```group``` as ```emby:emby``` for the folders you want to attach as libraries otherwise permission errors will occurs. 

# CentOS/RHEL turn off beep/bell terminal sound
- Remove ```pcspkr``` kernel module
```sh
rmmod -v pcspkr
```
- Blacklist ```pcspkr``` in ```/etc/modprobe.d/blacklist``` by adding the following line:
```sh
blacklist pcspkr
```

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
2019-5-11

- Fixed path splited due to blank space
- Added hexedit cli

2019-5-07

- hyper web shell for et/mosh

2019-5-05

- env to find python interpreter 
- shlex to analyze command lexically in case to prevent security hole

2019-5-03

- tmux with set up guide line

2019-03-26

- update cli for easy updating apt-based system

2018-11-4

- ssh to guest virtual machine, along with ```vm_init``` to start virtual machine in background

2018-11-3

- O(1) is_remote_proto() using frozenset instead of previous list traversing O(n) of ```open```

2018-11-2

- Revised the open command using python2/3
- Revised battery information script using python2/3

2018-10-15

- Settings for Dash to Dock

2018-10-13

- Resolved GoldenDict on Ubuntu 18.04 system tray by installing sni-qt libraries 

2018-10-08

- Dynamic wallpapers configuration for Gnome 
- Method to remove/hide icons in the ```Show Applications``` button
- Suspend button for Gnome 3.x
- Revert commit command

2018-09-19

- Aria2 install guide on Raspberry Pi
- Aria2-WebUI install guide on Raspberry Pi
- Samba service attached on Raspberry Pi

2018-09-15

- Resolve duplicate indicators of fcitx and sogou on Ubuntu 18.04
- Remove unused ibus and indicator-keyboard 

2018-07-23

- Virtualbox and phpVirtualbox for CentOS 7/Ubuntu with php7
- Nextcloud for Ubuntu with pretty urls rewrite 
- Netdata for ```Ubuntu 18.04+``` and ```CentOS 6.5+```
- Enable temperature sensors for netdata and ```sensors``` command tip 
- Attach netdata and emby in apps list

2018-04-30

- Fixed '..' issue and simplified block logic for 'open' program

2018-03-19

- Corrected ```GoldenDict``` typo credit @Penuchot

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
