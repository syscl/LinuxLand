# Fix sof-rt5682 (hp c1030) on Fedora Gnome

## New method to work on both Gnome and KDE
I found KDE super unstable, even though I want to give it a try, even a Fedora 42 KDE to 43 update will break the entire system (cannot boot). Not only boot problem, but also, some of the UI for example settings, sometimes just show nothing, very flaky even it is already plasma 6.4. So I decide to figure out why audio is working on KDE but not Gnome. Basically, KDE and Gnome should share the same audio stack, so it is very likely the configuration cause the problem. I took a dump of the audio from KDE and Gnome:
1. High-level audio info
```
inxi -Axx
```
2. PCI audio devices + kernel driver:
```
lspci -nnk | grep -A3 -i audio
```
3. PipeWire / WirePlumber status (user session)
```
systemctl --user status pipewire pipewire-pulse wireplumber
```
4. What PipeWire sees (cards/sinks):
```
wpctl status
```
5. PulseAudio-compat view (for profiles)
```
pactl list cards short
pactl list cards
```
Now I have both working logs and none working logs, so I did a compare by
```
diff -ru kde-soundcard-proaudio-on gnome-soundcard
```
this tells the difference between the two soundcards logs in two folders, here's the output:
```
diff -ru kde-soundcard-proaudio-on/inxi.log gnome-soundcard/inxi.log
--- kde-soundcard-proaudio-on/inxi.log	2025-11-08 12:49:37
+++ gnome-soundcard/inxi.log	2025-11-08 12:41:22
@@ -1,7 +1,7 @@
 Audio:
   Device-1: Intel Comet Lake PCH-LP cAVS driver: sof-audio-pci-intel-cnl
     bus-ID: 00:1f.3 chip-ID: 8086:02c8
-  API: ALSA v: k6.17.1-300.fc43.x86_64 status: kernel-api
-  Server-1: PipeWire v: 1.4.8 status: active with: 1: pipewire-pulse
+  API: ALSA v: k6.17.7-300.fc43.x86_64 status: kernel-api
+  Server-1: PipeWire v: 1.4.9 status: active with: 1: pipewire-pulse
     status: active 2: wireplumber status: active 3: pipewire-alsa type: plugin
     4: pw-jack type: plugin
Only in gnome-soundcard: pact_card_short.log
diff -ru kde-soundcard-proaudio-on/pactl.log gnome-soundcard/pactl.log
--- kde-soundcard-proaudio-on/pactl.log	2025-11-08 12:50:22
+++ gnome-soundcard/pactl.log	2025-11-08 12:43:05
@@ -1,4 +1,4 @@
-Card #51
+Card #50
 	Name: alsa_card.pci-0000_00_1f.3-platform-cml_rt5682_def
 	Driver: alsa
 	Owner Module: n/a
@@ -21,7 +21,7 @@
 		device.icon_name = "audio-card-analog-pci"
 		device.name = "alsa_card.pci-0000_00_1f.3-platform-cml_rt5682_def"
 		device.nick = "sof-rt5682"
-		device.plugged.usec = "15955197"
+		device.plugged.usec = "12428990"
 		device.product.id = "0x02c8"
 		device.product.name = "Comet Lake PCH-LP cAVS"
 		device.subsystem = "sound"
@@ -31,9 +31,9 @@
 		media.class = "Audio/Device"
 		spa.object.id = "2"
 		factory.id = "15"
-		client.id = "49"
-		object.id = "51"
-		object.serial = "51"
+		client.id = "45"
+		object.id = "50"
+		object.serial = "50"
 		object.path = "alsa:acp:sofrt5682"
 		alsa.card = "0"
 		alsa.card_name = "sof-rt5682"
@@ -49,7 +49,7 @@
 		output:stereo-fallback: Stereo Output (sinks: 1, sources: 0, priority: 5100, available: no)
 		input:stereo-fallback: Stereo Input (sinks: 0, sources: 1, priority: 51, available: no)
 		pro-audio: Pro Audio (sinks: 5, sources: 3, priority: 1, available: yes)
-	Active Profile: pro-audio
+	Active Profile: off
 	Ports:
 		analog-input-headset-mic: Headset Microphone (type: Headset, priority: 8800, latency offset: 0 usec, availability group: Legacy 1, not available)
 			Properties:
Only in kde-soundcard-proaudio-on: pactl_short.log
diff -ru kde-soundcard-proaudio-on/pipewire_status.log gnome-soundcard/pipewire_status.log
--- kde-soundcard-proaudio-on/pipewire_status.log	2025-11-08 12:50:08
+++ gnome-soundcard/pipewire_status.log	2025-11-08 12:42:25
@@ -4,48 +4,52 @@
              └─00-uresourced.conf
              /usr/lib/systemd/user/service.d
              └─10-timeout-abort.conf
-     Active: active (running) since Sat 2025-11-08 20:44:09 UTC; 5min ago
- Invocation: b6ea5961d8d14374b2fa1a3d9c624bbb
+     Active: active (running) since Sat 2025-11-08 12:39:46 PST; 2min 39s ago
+ Invocation: 34cf6acaabf541b092561fe3db68fbc1
 TriggeredBy: ● pipewire.socket
-   Main PID: 2276 (pipewire)
-      Tasks: 3 (limit: 18626)
-     Memory: 13.6M (peak: 16.5M)
-        CPU: 458ms
+   Main PID: 2795 (pipewire)
+      Tasks: 3 (limit: 18880)
+     Memory: 5.5M (peak: 10.1M)
+        CPU: 104ms
      CGroup: /user.slice/user-1000.slice/user@1000.service/session.slice/pipewire.service
-             └─2276 /usr/bin/pipewire
+             └─2795 /usr/bin/pipewire

-Nov 08 20:44:09 localhost-live systemd[1980]: Started pipewire.service - PipeWire Multimedia Service.
-Nov 08 20:46:03 localhost-live pipewire[2276]: mod.raop-sink: sess.latency.msec 250.000000 should be an integer multiple of rtp.ptime 7.981859
+Nov 08 12:39:46 fedora systemd[2589]: Started pipewire.service - PipeWire Multimedia Service.
+Nov 08 12:39:46 fedora pipewire[2795]: mod.raop-sink: sess.latency.msec 250.000000 should be an integer multiple of rtp.ptime 7.981859

 ● pipewire-pulse.service - PipeWire PulseAudio
      Loaded: loaded (/usr/lib/systemd/user/pipewire-pulse.service; disabled; preset: disabled)
     Drop-In: /usr/lib/systemd/user/service.d
              └─10-timeout-abort.conf
-     Active: active (running) since Sat 2025-11-08 20:44:09 UTC; 5min ago
- Invocation: 89a9fca293b24633b5a8457f02f0b756
+     Active: active (running) since Sat 2025-11-08 12:39:49 PST; 2min 36s ago
+ Invocation: 447d06071c1146cd8f3b287d626d4189
 TriggeredBy: ● pipewire-pulse.socket
-   Main PID: 2279 (pipewire-pulse)
-      Tasks: 3 (limit: 18626)
-     Memory: 10.2M (peak: 11.6M)
-        CPU: 287ms
+   Main PID: 3269 (pipewire-pulse)
+      Tasks: 3 (limit: 18880)
+     Memory: 2.6M (peak: 3.8M)
+        CPU: 77ms
      CGroup: /user.slice/user-1000.slice/user@1000.service/session.slice/pipewire-pulse.service
-             └─2279 /usr/bin/pipewire-pulse
+             └─3269 /usr/bin/pipewire-pulse

-Nov 08 20:44:09 localhost-live systemd[1980]: Started pipewire-pulse.service - PipeWire PulseAudio.
+Nov 08 12:39:49 fedora systemd[2589]: Started pipewire-pulse.service - PipeWire PulseAudio.

 ● wireplumber.service - Multimedia Service Session Manager
      Loaded: loaded (/usr/lib/systemd/user/wireplumber.service; enabled; preset: enabled)
     Drop-In: /usr/lib/systemd/user/service.d
              └─10-timeout-abort.conf
-     Active: active (running) since Sat 2025-11-08 20:44:09 UTC; 5min ago
- Invocation: 68527d4504a54b36a60545078f577a21
-   Main PID: 2277 (wireplumber)
-      Tasks: 9 (limit: 18626)
-     Memory: 30.7M (peak: 31.5M)
-        CPU: 1.414s
+     Active: active (running) since Sat 2025-11-08 12:39:46 PST; 2min 39s ago
+ Invocation: 35eb434984fa406789216d66e80d2ca7
+   Main PID: 2797 (wireplumber)
+      Tasks: 9 (limit: 18880)
+     Memory: 6.7M (peak: 7.6M)
+        CPU: 434ms
      CGroup: /user.slice/user-1000.slice/user@1000.service/session.slice/wireplumber.service
-             └─2277 /usr/bin/wireplumber
+             └─2797 /usr/bin/wireplumber

-Nov 08 20:44:09 localhost-live systemd[1980]: Started wireplumber.service - Multimedia Service Session Manager.
-Nov 08 20:44:10 localhost-live wireplumber[2277]: [0:00:32.572363363] [2277]  INFO Camera camera_manager.cpp:330 libcamera v0.5.2
-Nov 08 20:44:10 localhost-live wireplumber[2277]: [0:00:32.709899230] [2321]  INFO Camera camera_manager.cpp:220 Adding camera '\_SB_.PCI0.XHCI.RHUB.HS07-7:1.0-05c8:03e1' for pipeline handler uvcvideo
+Nov 08 12:39:46 fedora systemd[2589]: Started wireplumber.service - Multimedia Service Session Manager.
+Nov 08 12:39:46 fedora wireplumber[2797]: wp-event-dispatcher: wp_event_dispatcher_unregister_hook: assertion 'already_registered_dispatcher == self' failed
+Nov 08 12:39:46 fedora wireplumber[2797]: wp-event-dispatcher: wp_event_dispatcher_unregister_hook: assertion 'already_registered_dispatcher == self' failed
+Nov 08 12:39:46 fedora wireplumber[2797]: wp-event-dispatcher: wp_event_dispatcher_unregister_hook: assertion 'already_registered_dispatcher == self' failed
+Nov 08 12:39:46 fedora wireplumber[2797]: wp-event-dispatcher: wp_event_dispatcher_unregister_hook: assertion 'already_registered_dispatcher == self' failed
+Nov 08 12:39:46 fedora wireplumber[2797]: [0:00:27.966520471] [2797]  INFO Camera camera_manager.cpp:330 libcamera v0.5.2
+Nov 08 12:39:47 fedora wireplumber[2797]: [0:00:28.068160633] [2851]  INFO Camera camera_manager.cpp:220 Adding camera '\_SB_.PCI0.XHCI.RHUB.HS07-7:1.0-05c8:03e1' for pipeline handler uvcvideo
diff -ru kde-soundcard-proaudio-on/wpctl.log gnome-soundcard/wpctl.log
--- kde-soundcard-proaudio-on/wpctl.log	2025-11-08 12:50:16
+++ gnome-soundcard/wpctl.log	2025-11-08 12:42:34
@@ -1,36 +1,25 @@
-PipeWire 'pipewire-0' [1.4.8, liveuser@localhost-live, cookie:2291419000]
+PipeWire 'pipewire-0' [1.4.9, syscl@fedora, cookie:1479073467]
  └─ Clients:
-        33. uresourced                          [1.4.8, liveuser@localhost-live, pid:2236]
-        34. pipewire                            [1.4.8, liveuser@localhost-live, pid:2279]
-        35. kwin_wayland                        [1.4.8, liveuser@localhost-live, pid:2243]
-        37. WirePlumber                         [1.4.8, liveuser@localhost-live, pid:2277]
-        45. System Settings                     [1.4.8, liveuser@localhost-live, pid:4407]
-        49. WirePlumber [export]                [1.4.8, liveuser@localhost-live, pid:2277]
-        50. QtPulseAudio:2348                   [1.4.8, liveuser@localhost-live, pid:2348]
-        55.                                     [1.4.8, liveuser@localhost-live, pid:2516]
-        56. libcanberra                         [1.4.8, liveuser@localhost-live, pid:2428]
-        60. plasmashell                         [1.4.8, liveuser@localhost-live, pid:2454]
-        61.                                     [1.4.8, liveuser@localhost-live, pid:2428]
-        68. libcanberra                         [1.4.8, liveuser@localhost-live, pid:2454]
-        70.                                     [1.4.8, liveuser@localhost-live, pid:2454]
-        71. xdg-desktop-portal                  [1.4.8, liveuser@localhost-live, pid:2251]
-       102. wpctl                               [1.4.8, liveuser@localhost-live, pid:4558]
+        33. uresourced                          [1.4.9, syscl@fedora, pid:2765]
+        34. WirePlumber                         [1.4.9, syscl@fedora, pid:2797]
+        45. WirePlumber [export]                [1.4.9, syscl@fedora, pid:2797]
+        46. Mutter                              [1.4.9, syscl@fedora, pid:2798]
+        62. pipewire                            [1.4.9, syscl@fedora, pid:3269]
+        63. GNOME Volume Control Media Keys     [1.4.9, syscl@fedora, pid:2952]
+        64. gnome-shell                         [1.4.9, syscl@fedora, pid:2798]
+        65. GNOME Shell Volume Control          [1.4.9, syscl@fedora, pid:2798]
+        66. xdg-desktop-portal                  [1.4.9, syscl@fedora, pid:3300]
+        67. libcanberra                         [1.4.9, syscl@fedora, pid:2952]
+        70. wpctl                               [1.4.9, syscl@fedora, pid:7030]

 Audio
  ├─ Devices:
- │      51. Comet Lake PCH-LP cAVS              [alsa]
+ │      50. Comet Lake PCH-LP cAVS              [alsa]
  │
  ├─ Sinks:
- │      36. Comet Lake PCH-LP cAVS Pro          [vol: 1.00]
- │      69. Comet Lake PCH-LP cAVS Pro 4        [vol: 1.00]
- │      73. Comet Lake PCH-LP cAVS Pro 3        [vol: 1.00]
- │  *   75. Comet Lake PCH-LP cAVS Pro 5        [vol: 1.00]
- │      76. Comet Lake PCH-LP cAVS Pro 2        [vol: 1.00]
+ │  *   40. Dummy Output                        [vol: 0.94]
  │
  ├─ Sources:
- │  *   67. Comet Lake PCH-LP cAVS Pro          [vol: 1.00]
- │      77. Comet Lake PCH-LP cAVS Pro 1        [vol: 1.00]
- │      78. Comet Lake PCH-LP cAVS Pro 8        [vol: 1.00]
  │
  ├─ Filters:
  │
@@ -38,14 +27,14 @@

 Video
  ├─ Devices:
- │      62. HP Wide Vision HD Camera            [v4l2]
- │      63. HP Wide Vision HD Camera            [v4l2]
- │      64. HP Wide Vision HD Camera: HP Wi     [libcamera]
+ │      57. HP Wide Vision HD Camera            [v4l2]
+ │      58. HP Wide Vision HD Camera            [v4l2]
+ │      59. HP Wide Vision HD Camera: HP Wi     [libcamera]
  │
  ├─ Sinks:
  │
  ├─ Sources:
- │  *   65. HP Wide Vision HD Camera (V4L2)
+ │  *   60. HP Wide Vision HD Camera (V4L2)
  │
  ├─ Filters:
  │
@@ -53,4 +42,3 @@

 Settings
  └─ Default Configured Devices:
-         0. Audio/Sink    alsa_output.pci-0000_00_1f.3-platform-cml_rt5682_def.pro-output-5
```
The key line is here:
```
-    Active Profile: pro-audio
+    Active Profile: off
```
so we just need to active the profile for the sound card in Gnome.
First list the sound card by `pactl list cards short`, here's an example output
```
48	alsa_card.pci-0000_00_1f.3-platform-cml_rt5682_def	alsa
```
Now set the audio to `pro-audio`:
```
pactl set-card-profile alsa_card.pci-0000_00_1f.3-platform-cml_rt5682_def pro-audio

```
You should see the sound setting in `Settings > Sound`'s `Input` and `Output` sections.

## Below method is a bit outdated and no needed.
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

- On ubuntu install a restart pulseaudio.service script on login using `/etc/profile.d/`. Since `profile.d/*.sh` is executed by `/etc/profile`, we need to create a shell script that will invoke another script. Just copy `fix-c1030-quirk.sh` and `fix-c1030-quirk.py` to the `/etc/profile.d`.
