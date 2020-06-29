# ECU INFOTAINMENT
## Configuration
+ User:Pass (Prototyping only, please!)
```
pi:asdf,.123
infotainment:asdf,.123
```

+ Touchscreen installation
```
https://www.raspberrypi.org/documentation/hardware/display/
```

+ Set desktop wallpaper as a real infotainment. As example, Apple Carplay.

+ Comment all lines in /etc/update-motd.d/10-uname

+ Remove ssh last log info in /etc/ssh/sshd.conf:
```
    PrintLastLog no
```

+ Copy asciiart.txt content to /etc/motd.

+ Set a Static IP. Add in /etc/dhcpcd.conf:
```
interface eth0
    static ip_address=10.0.0.10/24
```

+ Change hostname with raspi-config to:
```
infotainment-ecu
```

# Front Vision Camera Stream

+ Open video stream through web browser:
```
http://10.0.0.20:8000
```

# Autopilot Management App
+ Execute autopilot_app.py
