
# ECU AUTOPILOT

## Configuration

+ User:Pass (Prototyping only, please!):
```
pi:asdf,.123 
```

+ Comment all lines in /etc/update-motd.d/10-uname

+ Remove ssh last log info in /etc/ssh/sshd.conf
```
PrintLastLog no
````

+ Copy asciiart.txt content to nano /etc/motd

+ Disable Wifi and Bluetooth. In /boot/config.txt add:
```
dtoverlay=disable-wifi
dtoverlay=disable-bt
```

+ Set a Static IP. Add in /etc/dhcpcd.conf
```
interface eth0
    static ip_address=10.0.0.30/24
```

+ Change hostname with raspi-config:
```
sudo raspi-config
autopilot-ecu
```

+ PICAN2 CAN Bus Shield Configuration. Add in /boot/config.txt:
```
dtparam=spi=on
dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25 
dtoverlay=spi-bcm2835-overlay
```

+ Enable CAN Bus Interface on boot and execute app. Add in /etc/rc.local:
```
/sbin/ip link set can0 up type can bitrate 500000
/home/pi/autopilot_app.py &
```
+ Install required Python libraries
```
sudo apt install python3-gpiozero
```

+ Copy autopilot python app to /home/pi/autopilot_app.py

+ Install Apache Web Server
```
apt-get install apache2
apt-get install php libapache2-mod-php -y
```