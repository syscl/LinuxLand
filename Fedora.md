# A doc about using Fedora and its related optimizations

# Remove `Chromium is managed by your organization`
When installing Chromium from fedora RPM, you will notice the `Chromium is managed by your organization` under the `settings` menu. To address this, just remove the `fedora-chromium-config` by the following command:
```
sudo dnf remove fedora-chromium-config
```

# Enable Fractional Scaling
```
gsettings set org.gnome.mutter experimental-features "['scale-monitor-framebuffer']"
```
One may found this may remove other experimental-features you already have, so the complete command line will get the feature list first via
```
gsettings get org.gnome.mutter experimental-features
```
then insert the `'scale-monitor-framebuffer'` in the list.

# Resolve Chromium blur under fractional scaling under Wayland
In Chromium address bar, type `chrome://flags`, hit enter. Search for `Preferred Ozone platform` and change its value to `Wayland`

# Disable Gnome Overview when login the system
One may find it annoying when login the system, Gnome shows the overview mode. To disable it, ~~just install the [No overview at start-up Extension](https://extensions.gnome.org/extension/4099/no-overview/)~~ just install the [Dash-to-Dock](https://extensions.gnome.org/extension/307/dash-to-dock/), open its setting -> `Appearance` -> turn off `Show overview on startup`.

# Sound card auto switch problem
I'm currently only able to make it work on Fedora and Manjaro. First install the following packages:
```
sudo dnf install pulseaudio pulseaudio-utils pavucontrol --allowerasing
```
Then add the following settings to `/etc/pulse/default.pa`
```
load-module module-oss
load-module module-switch-on-connect
load-module module-alsa-source device=hw:0,1
load-module module-alsa-sink device=hw:0,5
```
Note on Gnome, you need to copy the `c1030/pulse` folder to the `/etc` and overwrite it to make the speaker and headphone work with auto-switch feature. The config is actually copied from the Manjaro KDE 22.04 working with my own modification.


# Flash latest rom for c1030
- Located the UEFI firmware by your device by the [source.sh](https://github.com/MrChromebox/scripts/blob/master/sources.sh), in this case c1030 is device name is `jinlon`, download the firmware by `wget https://mrchromebox.tech/files/firmware/full_rom/coreboot_edk2-jinlon-mrchromebox_20230930.rom`
- Flash the rom via `sudo flashrom -p internal -w <rom_path>`
- Note: Flashing room may throw error that found an `Opaque flash chip` due to active ME. This is caused by the [write protection](https://wiki.mrchromebox.tech/Firmware_Write_Protect). To address it, one can simply flash the rom with the following command:
```bash
sudo flashrom -p internal -w <rom_path> --ifd -i bios --noverify-all
```

# Install cloudpinyin on Fedora KDE
Please refer to this [link](https://www.youtube.com/watch?v=Z7EO00F5H6s) for more detail. Basically:
```
sudo dnf install fcitx5-chinese-addons
```
- Logout
- Right click the fcitx input icon > Add `Pinyin` from right > hit `Configure` > `Enable Cloudpinyin` > select your prefer backend


# Perform update to Fedora release
Check with this: https://docs.fedoraproject.org/en-US/quick-docs/upgrading-fedora-offline/

On UEFI system, don't need to update grub2-install, use https://fedoraproject.org/wiki/GRUB_2#Instructions_for_UEFI-based_systems to update UEFI.
