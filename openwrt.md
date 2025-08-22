# This aims for the usage of OpenWrt 24.10.1 on Asus Chromebox 3 / tplink_archer-a7-v5 (TP-Link Archer A7 v5)

# DNS using quad9 / cloudflare
Note smartdns seems not working for me, what it is working is using https://docs.quad9.net/Setup_Guides/Open-Source_Routers/OpenWrt_LuCi/:
- Install (bring back dnsmasq package): `opkg install dnsmasq`
- Navigate to `Network` -> `DHCP and DNS`
- Set `9.9.9.9` and `149.112.112.112`, or the addresses of your preferred Quad9 service in the "DNS forwardings" input fields.
- If your network supports IPv6, you can also add 2620:fe::fe and 2620:fe::9, or the IPv6 addresses of your preferred Quad9 service.
- Navigate to `Resolv and Hosts Files` sub-tab, and make sure `Ignore resolv file` is Enabled.
- Click Save & Apply at the bottom. Since you are not changing the DHCP settings, the change should be instantaneous.
- Access https://on.quad9.net/ to verify the change works
~~
- First install [smartdns](https://pymumu.github.io/smartdns/)
- Configured smartns: Service > SmartDNS > Upstream Servers > Add:
  - Name: Quad9
    - Address: 9.9.9.9
    - Port: 53
    - Protocol: UDP
    - Priority: 1
    - Weight: 1
    - Enabled: Yes
  - Name: Cloudflare
    - Address: 1.1.1.1
    - Port: 53
    - Protocol: UDP
    - Priority: 2
    - Weight: 1
    - Enabled: Yes~~
Some comparison between quad9 vs cf: https://www.reddit.com/r/HomeNetworking/comments/1j7eql7/cloudflare_dns_vs_quad_9_dns/
For cloudflare dns test visit https://one.one.one.one/help/


# Hit module 'luci.ucodebridge' not found when access luci
refer this [link](https://github.com/openwrt/luci/issues/7314):
`
Did you leave the Automatically remove unused dependencies checkbox checked? This is a known issue that shows up from time to time.

You should be able to access LuCI again if you run opkg install luci-lua-runtime, see https://forum.openwrt.org/t/removed-clamav-package-with-all-dependacies-and-broke-luci/204187/4
`

# When dnsq removed, how to access router
Wired connected to router, set ip address as static: 192.168.1.2, mask: 255.255.255.0, gateway: 192.168.1.1, then access 192.168.1.1 (if it is win11, filled the dns: 9.9.9.9)

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


- Change default shell with chsh
```
opkg update
opkg install shadow-chsh
opkg install bash # or zsh if you like
chsh -s /bin/bash
```

- Power on the Access Point
As for now, we need to change the AP setting as following to make it able to associate with:
- Network->Tab->Edit->Operating frequency: Mode: N, Band 2.4 Ghz, Channel: manually select one except `auto`
- `Save & Apply`

TODO:
- /lib/firmware/i915's intel graphics card's DMC was failed to load even with manually copied bin
- Makes the AP able to use 5G auto switch
- install git-http for git clone?
- bash cannot load `~/.bashrc` by default
