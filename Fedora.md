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
One may find it annoying when login the system, Gnome shows the overview mode. To disable it, just install the [No overview at start-up Extension](https://extensions.gnome.org/extension/4099/no-overview/).

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
