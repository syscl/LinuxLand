#!/usr/bin/env bash

echo "Restarting pulseaudio.service and start pavucontrol..."

# check /usr/share/applications/pavucontrol.desktop `Exec` section for more information
nohup pavucontrol >/dev/null 2>&1 &

systemctl --user restart pulseaudio.service
