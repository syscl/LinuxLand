# This aims for the usage of OpenWrt 22.03.4+ on Asus Chromebox 3
Hardware specification:
- Ethernet (eth0) RTL 8169
- Wireless: AC 7265D
- BIOS: Coreboot EFI


- First install the EFI img to the chromebox
- Enable the dhcp for the OpenWrt system otherwise you are not able to connect the network. Here's the steps:
```
uci show network # show the network config for the ethernet, for example: eth0
uci delete network.lan.ipaddr
uci delete network.lan.netmask
uci set network.lan.proto=dhcp
uci commit
reboot
```
After the reboot, the system will be able to connect to the internet over the wire. You can check if the ping is able to get packets via `ping google.com`

- Install Intel firmwares and load kernel models
```
opkg update
opkg install iwlwifi-firmware-iwl7265d
opkg install kmod-iwlwifi
reboot
```

- Install security encryption package for setting up password for the device. More detail can be found in [link](https://openwrt.org/docs/guide-user/network/wifi/encryption) and [link](https://openwrt.org/docs/guide-user/network/wifi/basic#wpa_modes)'s `Encryption Modes`:
```
opkg install wpad-openssl
```

- Expand root partition and filesystem
Please refer to this [link](https://openwrt.org/docs/guide-user/advanced/expand_root)


TODO:
- /lib/firmware/i915's intel graphics card's DMC was failed to load even with manually copied bin
- Wireless AP is still disabled
- 

