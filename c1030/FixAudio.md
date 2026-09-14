# GNOME on the HP Chromebook c1030 (Jinlon)

This records the audio and fingerprint setup completed in this conversation. It is a guide for this machine, not a claim that all Chromebook hardware or Fedora features were tested.

## Tested system

- HP Chromebook c1030, board **Jinlon**, reported as `HP-Jinlon-rev5`.
- Fedora Linux 44 Workstation, kernel `7.2.4-200.fc44.x86_64`.
- GNOME Shell `50.4`, GDM `50.3`. **44 is the Fedora version; the installed GNOME version is 50.**
- PipeWire `1.6.8`.
- SELinux remained **Enforcing** throughout.

## 1. Restore Fedora's PipeWire audio service if it was replaced

An earlier command installed `pulseaudio` with `--allowerasing`, removing `pipewire-pulseaudio`. To reverse that audio-server change:

```bash
sudo dnf swap --allowerasing pulseaudio pipewire-pulseaudio
sudo dnf install wireplumber pipewire-alsa
```

Reboot after the replacement. `pactl info` should then report `PulseAudio (on PipeWire ...)`; that wording means PipeWire is providing PulseAudio compatibility.

`pulseaudio-utils` supplies `pactl` and can stay installed. The optional **Volume Control** application is `pavucontrol`; it works with PipeWire but is unnecessary for the fix:

```bash
sudo dnf remove pavucontrol
```

## 2. Fix the built-in audio configuration

The sound card was `sof-rt5682`. The kernel detected the speakers, but the desktop showed only Dummy Output (`auto_null`). Profile-switching commands failed. The important diagnostic was:

```bash
aplay -l
alsaucm -c hw:0 list _verbs
```

`aplay` listed the Speakers device, while `alsaucm` failed to load a use-case configuration. Fedora's `alsa-ucm-1.2.16.1-1.fc44` was already installed and current, but `/usr/share/alsa/ucm2/conf.d/sof-rt5682` was absent. Installing or updating that package alone did not solve this machine's problem.

Install the diagnostic utility if needed:

```bash
sudo dnf install alsa-ucm-utils
```

The working fix was the community Chromebook audio setup tool:

```bash
sudo dnf install git
mkdir -p ~/git
cd ~/git
git clone --depth 1 https://github.com/WeirdTreeThing/chromebook-linux-audio.git
cd chromebook-linux-audio
./setup-audio
```

If already cloned, use the existing directory instead of cloning again. The tool detected **Intel Cometlake**, **max98357a**, and **rt5682**, installed the Chromebook UCM configuration, passed its kernel checks, and added a WirePlumber headroom adjustment. Save your work and reboot when it finishes successfully.

Verify:

```bash
alsaucm -c hw:0 list _verbs
pactl info
pactl list cards
pactl list sinks short
```

Our result: **HiFi available and active**, real speaker/headphone/HDMI outputs, speakers selected as the default output, and no dummy output. The user confirmed sound worked. Keep the **HiFi** profile; forcing `pro-audio` was not the solution. Other outputs being `SUSPENDED` while idle does not establish a fault.

Source: https://github.com/WeirdTreeThing/chromebook-linux-audio

## 3. Build experimental Jinlon fingerprint support

Standard fprintd/libfprint did not expose this reader. Experimental `rust-fp` support did work. We used the GNOME fixes from PR #20, pinned to the exact revision inspected during setup:

https://github.com/ChocolateLoverRaj/rust-fp/pull/20

First confirm that the device exists:

```bash
ls -l /dev/cros_fp
```

It appeared as a root-only character device. Leave its permissions unchanged; the reader service runs as root.

```bash
sudo dnf install git cargo rust gcc clang clang-devel pkgconf-pkg-config pam-devel pamtester
mkdir -p ~/git
cd ~/git
git clone --branch fix-gnome-polkit https://github.com/yuexiaoyong-star/rust-fp.git rust-fp-jinlon
cd rust-fp-jinlon
git checkout --detach 4d8ae905e1d02be2b06160c8eeb60154d8641b45
cargo build --release --locked -p rust-fp-cli -p rust-fp-dbus-interface -p rust-fp-pam-module
```

If the directory exists, skip cloning and use it. Rust lifetime and unused-dependency warnings appeared, but the builds completed successfully. A warning alone is not a failed build.

## 4. Install the reader service and enroll a finger

From `~/git/rust-fp-jinlon`:

```bash
sudo install -m 644 dbus-interface/org.rust_fp.RustFp.conf /usr/share/dbus-1/system.d/org.rust_fp.RustFp.conf
sudo install -m 755 target/release/rust-fp-dbus-interface /usr/local/bin/rust-fp-dbus-interface
sudo install -m 755 target/release/rust-fp /usr/local/bin/rust-fp

sudo tee /etc/systemd/system/rust-fp-dbus-interface.service >/dev/null <<'EOF'
[Unit]
Description=Chromebook fingerprint reader service
After=dbus.service
Requires=dbus.service

[Service]
Type=exec
ExecStart=/usr/local/bin/rust-fp-dbus-interface
Restart=on-failure
RestartSec=3

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl daemon-reload
sudo systemctl enable --now rust-fp-dbus-interface
rust-fp get-max-templates
```

Stop any manually launched instance before starting the system service. Our reader reported **5** template slots.

Enroll as your normal user, **without sudo**:

```bash
rust-fp add right-index
```

Touch and lift the finger as prompted until enrollment completes. If already enrolled, do not add the same label again.

Test the enrolled finger, then an unenrolled finger:

```bash
rust-fp match | sed -u '/^Output:/d'
```

Expected: `Matched: right-index.` for the enrolled finger and `No match` for the other. The filter hides fingerprint-template bytes that this version prints in its debug output. Do not share full template dumps.

## 5. Test authentication before connecting GNOME

```bash
cd ~/git/rust-fp-jinlon
sudo install -m 755 target/release/librust_fp_pam_module.so /usr/lib64/security/librust_fp_pam_module.so
sudo restorecon -v /usr/lib64/security/librust_fp_pam_module.so

sudo tee /etc/pam.d/rust-fp-test >/dev/null <<'EOF'
auth required librust_fp_pam_module.so
EOF
sudo restorecon -v /etc/pam.d/rust-fp-test
sudo pamtester rust-fp-test "$USER" authenticate
```

Run the test with each finger. We verified the enrolled finger authenticated and the other failed. Also verify that touching nothing cannot authenticate:

```bash
sudo -v
sudo timeout --kill-after=3s 20s pamtester rust-fp-test "$USER" authenticate
echo "Test exit code: $?"
sudo systemctl restart rust-fp-dbus-interface
```

Our no-touch test returned **124**, meaning it timed out without authenticating. These tests establish the observed behavior, not a comprehensive security audit of the experimental software.

## 6. Add GNOME reader discovery

PR #20 alone did not include the extra service needed to advertise the reader to GNOME. We created a small discovery-only service for this setup, based on GNOME Shell 50.4's device-detection interface. It does **not** accept fingerprints or authenticate users; the tested rust-fp PAM module performs authentication.

The companion files in this folder are:

- `discovery.py`: the custom discovery service.
- `install.sh`: installs it and connects the tested PAM module to GNOME fingerprint authentication.
- `rollback.sh`: restores the previous GNOME fingerprint configuration.

Keep these three files together. From their folder, run:

```bash
sudo bash ./install.sh
```

This is a first-install script, not an idempotent update tool. It deliberately stops if a previous setup backup exists; do not delete that backup to force a rerun.

The installer:

- Saves the original `/etc/pam.d/gdm-fingerprint` under `/var/lib/rust-fp-gnome-setup`.
- Masks normal `fprintd.service` so the discovery service can own its D-Bus name.
- Enables `rust-fp-gnome-discovery.service`.
- Changes only the fingerprint authentication entry in `gdm-fingerprint`; preserves its account/session checks and leaves the password stack unchanged.
- Schedules automatic rollback after ten minutes for the initial test.

Our installer completed successfully, returned the reader's device path, and reported its scan type as `press`.

Lock with **Super+L** and check: wrong finger stays locked; enrolled finger unlocks; password still unlocks on a separate attempt. The user reported that GNOME fingerprint unlock worked nicely. After all checks pass, cancel automatic rollback:

```bash
sudo systemctl stop rust-fp-gnome-rollback.timer
```

The conversation did not include command output confirming that the timer was stopped. If reproducing the setup, complete this step promptly after testing. Both fingerprint services are enabled for startup, but post-reboot fingerprint behavior was not separately demonstrated in the conversation.

## Recovery and limitations

To undo the custom GNOME integration:

```bash
sudo /usr/local/sbin/rust-fp-gnome-rollback
```

This restores the saved GNOME fingerprint configuration, disables the discovery service, and unmasks normal fprintd. It retains the rust-fp reader service, binaries, and enrolled fingerprints.

Useful status checks:

```bash
systemctl status rust-fp-dbus-interface rust-fp-gnome-discovery --no-pager
systemctl status rust-fp-gnome-rollback.timer --no-pager
getenforce
```

Fingerprint enrollment remains through `rust-fp`, not GNOME Settings. The custom service does not implement the complete fprintd API. Administrator prompts, sudo fingerprint authentication, fresh-boot login, and suspend/resume reliability were not verified. Fedora/GDM updates may require rechecking the integration. SELinux was never disabled, and no custom SELinux policy was needed for the successful test.

The earlier statement that this reader could not work on Linux was too broad: standard support was missing, but the experimental fork plus the custom GNOME discovery service worked on this Jinlon.
