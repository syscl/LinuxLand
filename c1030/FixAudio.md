# Fix sof-rt5682 (hp c1030) on Fedora and Gnome

If you are using KDE(manjaro, fedora), you just need to change the audio configure profile to `pro audio`, then the sound is out automatically. (note you need to manually choose the output, e.g. hw:0:1 is jack, hw:0:5 is speaker).

On Ubuntu, you need to install pipewire and pavucontrol to select the `pro audio`:
1. Install pipewire, pavucontrol and disbale pulseaudio service, enable pipewire service:
```
sudo apt install  install pipewire-audio-client-libraries libspa-0.2-bluetooth libspa-0.2-jack wireplumber pipewire-media-session- pavucontrol
systemctl --user --now disable pulseaudio.service
systemctl --user --now mask pulseaudio.service
systemctl --user --now enable pipewire pipewire-pulse
```
> NOTE: there's a '-' in the end of the command indicates to remove the package. The command will also install the required pipewire-pulse automatically. wireplumber is more advanced than simple media-session.
2. PulseAudio Volume Control > Configuration > Profile > Pro Audio.
3. You can verify if the sound service is on pipewire via `pactl info|grep 'Server Name'`



> Note below has been deprecated, since pulseaudio is so unreliable and cannot even detect the hdmi output properly.
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
load-module module-alsa-source device="hw:0,1" name="dmic"
set default-source alsa_input.hw_0_0
.ifexists module-udev-detect.so
load-module module-alsa-sink device="hw:0,5"
set-default-sink alsa_output.hw_0_5
set-sink-volume 1 25000
```

- Headphone will lose sound when idle, to fix it comment out/remove the `load-module module-suspend-on-idle`.

- On ubuntu install a restart pulseaudio.service script on login using `/etc/profile.d/`. Since `profile.d/*.sh` is executed by `/etc/profile`, we need to create a shell script that will invoke another script. Just cp `fix-c1030-quirk.sh` and `fix-c1030-quirk.py` to the `/etc/profile.d`.
