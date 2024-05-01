#!/usr/bin/env python3

import time
import shlex
import subprocess
import os

from typing import Dict


def listSinks() -> Dict[str, str]:
    ret = subprocess.check_output(shlex.split("pactl list sinks short"))
    sinks = dict()
    for line in ret.decode().splitlines():
        items = line.split("\t")
        if len(items) >= 2:
            sinks[items[1]] = line

    return sinks


if __name__ == "__main__":
    time.sleep(10)
    # Restart the pulseaudio service
    os.system("systemctl --user restart pulseaudio > /home/syscl/result1.txt")
    with open("/home/syscl/result.txt", "w") as f:
        f.write(f"Restarted pulseaudio service\n{listSinks()}")
    # Wait until the headphone sink is available
    headphone_sink = "alsa_output.pci-0000_00_1f.3-platform-sof_rt5682.stereo-fallback"
    while True:
        sinks = listSinks()
        if headphone_sink in sinks:
            subprocess.run(shlex.split(f"pactl set-default-sink {headphone_sink}"))
            break
        else:
            time.sleep(1)

    exit(0)
