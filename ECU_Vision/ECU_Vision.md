
# ECU VISION

## Configuration
+ User:Pass (Prototyping only, please!)
```
pi:asdf,.123
vision:asdf,.123
```

+ Raspberry Pi Camera installation
```
https://projects.raspberrypi.org/en/projects/getting-started-with-picamera
```

+ Comment all lines in /etc/update-motd.d/10-uname

+ Remove ssh last log info in /etc/ssh/sshd.conf:
```
    PrintLastLog no
```

+ Copy asciiart.txt content to /etc/motd.

+ Disable Wifi and Bluetooth. In /boot/config.txt add:
```
dtoverlay=disable-wifi
dtoverlay=disable-bt
```

+ Set a Static IP. In /etc/dhcpcd.conf add:
```
interface eth0
    static ip_address=10.0.0.20/24
```

+ Change hostname with raspi-config to
```
vision-ecu
```

+ Execute vision streaming server on boot
```
sudo nano /etc/rc.local
/home/vision/vision-streaming-server.py &
```
