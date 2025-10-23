This will mainly focus on server and client setup, as this plugin is great but also a nightmare to use(the logic is complicated and unreliable).

A few things needs to be careful.

First, it requires a containerized databased - couchdb (I have no clue what this is). However we need it. People may want to set it up without container, that is fine but I tried and ends up a lot of not working steps. So to keep things simple (this plugin is already a huge mess I have ever seen in my life), just use docker or podman.

The reason why I use podman, because I have to use docker for work related stuff, so to isolate things, I just switch to podman.

The starts, I only tested this on Debian 13 and Ubuntu 24.04 LTS, and my setup flow is as following:

[[Obsidian Livesync Topology]]

Why? The main reason is:
1. Keep controller machine for routing purpose only to avoid resource congestion, usually cloud machine is expensive and resource limited
2. Secure isolation as the obsidian machine is placed in an isolated virtual machine (VM) environment dedicated for a few things, with large storage, RAM and etc.
3. We offload the control (mainly data) for ourself instead of cloud provider

With this in mind, my setup became this:
cloud machine mainly serves as the endpoint for others as it has public IP, while VM uses fast reverse proxy (frp) to establish a tunnel from cloud to VM.


## Setup
In brief this will be the setup steps
1. Enable ingress rule for cloud machine for port 5984 (usually the port for couchdb)
2. Install frps(frp service) to cloud machine
3. Install frpc(frp client) to vm
4. Create volumes for persistent data and config for couch-db
5. Create a systemd service for the couchdb to start at boot
6. Client side settings

### frp service settings
in the `frps.toml`:
```
bindPort = 7000
```

### frp client config
```
serverAddr = <your-domain>
serverPort = 7000

[[proxies]]
name = "livesync"
type = "tcp"
localIP = "127.0.0.1"
localPort = 5984
remotePort = 5984
```

frp client service (systemd) in `/etc/systemd/system/frpc.service`
```
[Unit]
Description=Frp Client Service
After=network.target

[Service]
Type=simple
User=syscl
Restart=on-failure
RestartSec=5s
ExecStart=/home/syscl/frp/frpc -c /home/syscl/frp/frpc.toml
ExecReload=/bin/kill -s HUP $MAINPID

[Install]
WantedBy=multi-user.target
```

```
sudo systemctl enable frpc.service
sudo systemctl start frpc.service
sudo systemctl status frpc.service
```
### Create volumes for persisting data
```
podman volume create couchdb-data
podman volume create couchdb-etc
```
Now it is time to setup the livesync service
- So we need to create a systemd service for podman using Quadlet (more detail can be found here: https://www.redhat.com/en/blog/quadlet-podman)
To achieve that, create rootless service config:
```
mkdir -p $HOME/.config/containers/systemd
```
Create livesync.env (which is your password and username) in `$HOME/.config/containers/systemd`
```

COUCHDB_USER=<your_username>
COUCHDB_PASSWORD=<your_password>
```

Now create livesync.container (this is the actual livesync.service in systemd)
```
[Unit]
Description=Obsidian Livesync CouchDB (Quadlet)
Wants=network-online.target
After=network-online.target
# If you defined .volume units, uncomment:
# Requires=couchdb-data.volume couchdb-etc.volume
# After=couchdb-data.volume couchdb-etc.volume

[Container]
Image=docker.io/library/couchdb:latest
ContainerName=livesync
PublishPort=5984:5984
Volume=couchdb-data:/opt/couchdb/data
Volume=couchdb-etc:/opt/couchdb/etc/local.d
EnvironmentFile=%h/.config/containers/systemd/livesync.env

[Install]
WantedBy=default.target

[Service]
Restart=always
```
Note this service command is actually the following command:
```
podman run -d \
  --name couchdb-for-ols \
  --restart=always \
  -e COUCHDB_USER="${username}" \
  -e COUCHDB_PASSWORD="${password}" \
  -v couchdb-data:/opt/couchdb/data \
  -v couchdb-etc:/opt/couchdb/etc/local.d \
  -p 5984:5984 \
  docker.io/library/couchdb:latest
```


Then use quadlet to verify the config:
```
/usr/libexec/podman/quadlet -dryrun -user
quadlet-generator[2875366]: Loading source unit file /home/syscl/.config/containers/systemd/livesync.container

...
echo $?
0
```
you should expect the return value to be 0 (succeed).

Now let's start the service 
```
systemctl --user daemon-reload && systemctl --user restart livesync.service
```

Verify the pod is started
```
systemctl --user status livesync.service
```

Once service started, follow this command to do the initialization
```
export hostname=127.0.0.1:5984
export username=goojdasjdas     #Please change as you like.
export password=kpkdasdosakpdsa #Please change as you like
curl -s https://raw.githubusercontent.com/vrtmrz/obsidian-livesync/main/utils/couchdb/couchdb-init.sh | bash
```

Verify if the service work, you should see:
```
curl 127.0.0.1:5984
curl: (1) Received HTTP/0.9 when not allowed
```

Also modify the docker.ini for couchdb:
```
cat docker.ini 

[admins]
<your_username> = <your_keys_hash> 

[chttpd]
bind_address = 0.0.0.0
port = 0 
require_valid_user = true
enable_cors = true
max_http_request_size = 4294967296

[cluster]
n = 1

[chttpd_auth]
require_valid_user = true

[httpd]
WWW-Authenticate = Basic realm="couchdb"
enable_cors = true

[couchdb]
max_document_size = 50000000
uuid = 38858dad34456cb191150ad0793e2eac

[cors]
credentials = true
origins = app://obsidian.md,capacitor://localhost,http://localhost

[ssl]
enable = true
port = 5984
cert_file = /opt/couchdb/etc/local.d/ssl/fullchain.pem
key_file = /opt/couchdb/etc/local.d/ssl/privkey.pem
ca_file = /opt/couchdb/etc/local.d/ssl/fullchain.pem
secure_renegotiate = true
tls_versions = ['tlsv1.2', 'tlsv1.3']
```

Note a few tips:
- livesync plugin is not only hard to use, but buggy and problematic, if for some reason it does not work properly on Linux, clean the config and cache by doing
```
rm -rf ~/.config/obsidian ~/Documents/Obsidian\ Valut\.obsidian
```

### Client side settings
Once you installed livesync plugin and enabled it, click remote configuration, fill out the following:
Server URI > <your-domain-name>:5984 (usually https://xxx:5984)
- <password > 
- database name
- enable end-to-end encryption with your end-to-end password
Then click "Fetch"

Go to `Sync Settings` > Presets > Live Sync > Apply.

If databases or sync are not working, try fetch or rebuild database in the `Maintenance` tab

