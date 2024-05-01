# Fix sof-rt5682 on Fedora and Gnome

This has been tested on Fedora 40 and Ubuntu 24.04 LTS.

> Note on Fedora the result is more reliable, while Ubuntu needs a restart of the `pulseaudio.service`.

This is a bit annoying issue, but let's post the fix first (it is not complete yet, but workaround).

Reference link: https://www.reddit.com/r/chrultrabook/comments/umi82r/comet_lake_audio_sofrt5682_and_deep_sleep/

# Install the following packages
```
pulseaudio pulseaudio-utils pavucontrol
```
on Fedora need to run the following
```
sudo dnf install pulseaudio pulseaudio-utils pavucontrol --allowerasing
```
Add to /etc/modprobe.d/snd.conf
```
options snd-intel-dspcfg dsp_driver=3
```
which means using the new audio driver.

Add to /etc/pulse/client.conf
```
autospawn = yesdaemon-binary = /usr/bin/pulseaudioextra-arguments = --log-target=syslog
```
 Create /etc/pulse/default.pa.d
```
mkdir /etc/pulse/default.pa.d
```
Add the following to /etc/pulse/default.pa.d/chromebook.pa
```
load-module module-oss
load-module module-switch-on-connect
load-module module-alsa-source device="hw:0,1" name="dmic"
set default-source alsa_input.hw_0_0
.ifexists module-udev-detect.so
load-module module-alsa-sink device="hw:0,5"
set-default-sink alsa_output.hw_0_5
set-sink-volume 1 25000
```

> Note `pavucontrol` is needed, otherwise the headphone sound may lose. Keep opening the `pavucontrol` as a workaround until the actual fix/root cause.

On Ubuntu restarting `pulseaudio.service`: `systemctl --user restart pulseaudio.service` to make the sound take effects.

Let's make a script for automated the restart pulseaudio and start pavucontrol hack using systemd:
1. Create the `/etc/init.d/fix-c1030-quirk.sh`:
```
#!/usr/bin/env bash

echo "Restarting pulseaudio.service and start pavucontrol..."

# check /usr/share/applications/pavucontrol.desktop `Exec` section for more information
nohup pavucontrol >/dev/null 2>&1 &

systemctl --user restart pulseaudio.service
```
2. Create the service in `/etc/systemd/system/fix-c1030-quirk.service`
```
[Unit]
Description=Fix HP c1030 quirk on Ubuntu
After=network.target

[Service]
ExecStart=/etc/init.d/fix-c1030-quirk.sh

[Install]
WantedBy=default.target
```
3. Reload systemd dameon and enable, start services
```
systemctl daemon-reload
systemctl enable fix-c1030-quirk.service
systemctl start fix-c1030-quirk.service
```