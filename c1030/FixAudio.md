# Fix sof-rt5682 on Fedora and Gnome

This has been tested on Fedora 40 and Ubuntu 24.04 LTS.

> Note on Fedora the result is more reliable, while Ubuntu needs a restart of the `pulseaudio.service`.

This is a bit annoying issue, but let's post the fix first (it is not complete yet, but workaround).

Reference link: https://www.reddit.com/r/chrultrabook/comments/umi82r/comet_lake_audio_sofrt5682_and_deep_sleep/

# Install the following packages
```
pulseaudio pulseaudio-utils
```
on Fedora need to run the following
```
sudo dnf install pulseaudio pulseaudio-utils --allowerasing
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

- Headphone will lose sound on idle, to fix it comment out/remove the `load-module module-suspend-on-idle`. 

- On ubuntu install a restart pulseaudio.service script on login using `/etc/profile.d/`. Since `profile.d/*.sh` is executed by `/etc/profile`, we need to create a shell script that will invoke another script. Just cp `fix-c1030-quirk.sh` and `fix-c1030-quirk.py` to the `/etc/profile.d`. 