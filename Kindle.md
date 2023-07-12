# Kindle Paperwhite 3-5, Kindle Scribe

This is the kindle devices I owned, some notes about the them.

## Extract kindle screensavers from firmware (refer to [post#3](https://www.mobileread.com/forums/showthread.php?t=343834))
Kindle screensavers are high quality and elegant. I would like my other e-reader to use this nice screensavers.
- Download kindle firmware from [amazon](https://www.amazon.com/gp/help/customer/display.html?nodeId=GKMQC26VQQMM8XSW).
- Download [kindletool](https://www.mobileread.com/forums/showthread.php?t=225030), you can also find the Linux/macOS exectuable in `kindletool/` from this repo
- Use `./kindletool extract <input> <output>` to unpack the fimrware
- Use 7zip/gzip to unzip the `rootfs.img.gz`, e.g. `gzip -d rootfs.img.gz`
- Use 7zip to access `rootfs.img.gz/fwo_rootfs.img/usr/share/blanket/screensaver/`

You will find the `.png` images for the screensaver there.