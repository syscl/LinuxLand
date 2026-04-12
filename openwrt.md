# This aims for the usage of OpenWrt 25.12.0 on Netgear RBR/RBS/RBK50(v1) or Asus Chromebox 3 or tplink_archer-a7-v5 (TP-Link Archer A7 v5)

## Wireless Mesh setup
This currently using 802.11s, note, I use RBR+RBS backhaul as an example (version 25.12.2). This just list the essential steps:
- On all routers installed `wpad-mbedtls`: `apk update && apk del wpad-basic-mbedtls && apk add wpad-mbedtls && reboot`

### On main router
- Picked on radio as backhaul, in this case I used QCA9984 as backhaul raido:
```
uci set wireless.radio0.channel='157'
uci set wireless.radio0.htmode='VHT80'
uci set wireless.radio0.country='US'
uci set wireless.mesh_backhaul=wifi-iface
uci set wireless.mesh_backhaul.device='radio0'
uci set wireless.mesh_backhaul.network='lan'
uci set wireless.mesh_backhaul.mode='mesh'
uci set wireless.mesh_backhaul.mesh_id='syscl-rb50-mesh'
uci set wireless.mesh_backhaul.encryption='sae'
uci set wireless.mesh_backhaul.key=${BACKHAUL_PASSWORD}
```
### On other routers:
1. Disable DHCP and set the other router's lan IP different than main router, set gateway to main router:
```
uci set network.lan.proto='static'
uci set network.lan.ipaddr='192.168.1.2'
uci set network.lan.netmask='255.255.255.0'
uci set network.lan.gateway='192.168.1.1'
uci set network.lan.dns='192.168.1.1'
uci commit network
/etc/init.d/network restart
uci set dhcp.lan.ignore='1'
uci commit dhcp
/etc/init.d/dnsmasq restart
```
2. Set the same backhaul config as above
```
uci set wireless.radio0.channel='157'
uci set wireless.radio0.htmode='VHT80'
uci set wireless.radio0.country='US'
uci set wireless.mesh_backhaul=wifi-iface
uci set wireless.mesh_backhaul.device='radio0'
uci set wireless.mesh_backhaul.network='lan'
uci set wireless.mesh_backhaul.mode='mesh'
uci set wireless.mesh_backhaul.mesh_id='syscl-rb50-mesh'
uci set wireless.mesh_backhaul.encryption='sae'
uci set wireless.mesh_backhaul.key=${BACKHAUL_PASSWORD}
```
3. Set AP's SSID and password the same as the main router to enable seamless connection

### To verify if the mesh works:
1. Connect the the access point(AP), and access each router's lan ip
2. Connect to a close router (or just disable other router's radio), then connect and check internet connection

### Note: on RBR/RBS50, it is recommended to use non-ct firmware to imporve performance for mesh
```
apk del kmod-ath10k-ct ath10k-firmware-qca4019-ct ath10k-firmware-qca9984-ct
apk add kmod-ath10k ath10k-firmware-qca4019 ath10k-firmware-qca9984
reboot
```

## Create Guest WiFi for one specific Radio
0. Export the SSID and password:
```
GUEST_WIFI_SSID=<your_guestwifi_ssid>
GUEST_WIFI_PASSWORD=<your_guest_wifi_password>
```
Follow the official doc: https://openwrt.org/docs/guide-user/network/wifi/guestwifi/guest-wlan
```
1. Configure network
uci -q delete network.guest_dev
uci set network.guest_dev="device"
uci set network.guest_dev.type="bridge"
uci set network.guest_dev.name="br-guest"
uci -q delete network.guest
uci set network.guest="interface"
uci set network.guest.proto="static"
uci set network.guest.device="br-guest"
uci set network.guest.ipaddr="192.168.3.1/24"
uci commit network
service network restart
```
2. Set up a wireless interface bound to the guest network interface.
```
# Configure wireless
WIFI_DEV="$(uci get wireless.@wifi-iface[0].device)"
uci -q delete wireless.guest
uci set wireless.guest="wifi-iface"
uci set wireless.guest.device="${WIFI_DEV}"
uci set wireless.guest.mode="ap"
uci set wireless.guest.network="guest"
uci set wireless.guest.ssid=${GUEST_WIFI_SSID}
uci set wireless.guest.encryption="sae-mixed"
uci set wireless.guest.key=${GUEST_WIFI_PASSWORD}
uci set wireless.guest.isolate="1"
wifi-iface
uci commit wireless
wifi reload
```
3. Configure a DHCP pool for the guest network.
```
uci -q delete dhcp.guest
uci set dhcp.guest="dhcp"
uci set dhcp.guest.interface="guest"
uci set dhcp.guest.start="100"
uci set dhcp.guest.limit="150"
uci set dhcp.guest.leasetime="1h"
uci commit dhcp
service dnsmasq restart
```
4. Configure firewall for the guest network. Allow to forward traffic from the guest network to WAN. Allow DHCP requests and DNS queries.
```
uci -q delete firewall.guest
uci set firewall.guest="zone"
uci set firewall.guest.name="guest"
uci set firewall.guest.network="guest"
uci set firewall.guest.input="REJECT"
uci set firewall.guest.output="ACCEPT"
uci set firewall.guest.forward="REJECT"
uci -q delete firewall.guest_wan
uci set firewall.guest_wan="forwarding"
uci set firewall.guest_wan.src="guest"
uci set firewall.guest_wan.dest="wan"
uci -q delete firewall.guest_dns
uci set firewall.guest_dns="rule"
uci set firewall.guest_dns.name="Allow-DNS-Guest"
uci set firewall.guest_dns.src="guest"
uci set firewall.guest_dns.dest_port="53"
uci set firewall.guest_dns.proto="tcp udp"
uci set firewall.guest_dns.target="ACCEPT"
uci -q delete firewall.guest_dhcp
uci set firewall.guest_dhcp="rule"
uci set firewall.guest_dhcp.name="Allow-DHCP-Guest"
uci set firewall.guest_dhcp.src="guest"
uci set firewall.guest_dhcp.dest_port="67"
uci set firewall.guest_dhcp.proto="udp"
uci set firewall.guest_dhcp.family="ipv4"
uci set firewall.guest_dhcp.target="ACCEPT"
uci commit firewall
service firewall restart
```

Note for guest WiFI, I used quad9 DNS such that it has a more restricted less ad experienced.

# DSA (Distributed Switch Architecture) no internet on most of the app(except chromium-based browsers)
The 25.12.x introduces DSA that RBS(satteliate)50 no longer see the WAN port and causing problem, this will use LAN1 as WAN to fix the issue:
1. Remove LAN1 from bridge in Network > Devices > Bridge Ports > unchecked LAN1
2. Network > Interfaces > Add new interfac:
```
Protocol: DHCP client
Device: lan1
Advance Settings: "unchecked Use DNS servers advertised by peer", Use Custom DNS: 1.1.1.1,secondary: 1.0.0.1
```
3. Repeated this for wan6 (except DNS)
4. Network > Firewall > Add > name: wan, input: reject, output: accept, IPv4 Masquerading: check, Covered Network, wan and wan6
Should hopefully see the internet.

Note RBS50 needs to set the QCA9984 (4x4 MIMO) to a higher channel, e.g. 149 to make it active (otherwise fail for some reason).


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
