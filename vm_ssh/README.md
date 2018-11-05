To use the ssh from host to guest virtual machine (VM) using VirtualBox, you have to setting up
the port forwarding by attaching the VM to ```NAT```. 
In the VM/Guest:

```sh
ipaddr show
```
to check the ip address, usually, ```10.0.2.15``` 

Then go to VM->```Settings```->```Network```->```Port Forwarding```, set the ```Protocol```, ```Host IP```, ```Host Port```, ```Guest IP``` and ```Guest Port``` as follwing:
```
TCP 127.0.0.1 2222 10.0.2.15 22
```

Then you can ssh from the host by
```sh
ssh -p 2222 user@localhost 
```

Once you've done this, just execute the ```vm_init``` or ```vm_halt``` to start or power off the VM as you like.