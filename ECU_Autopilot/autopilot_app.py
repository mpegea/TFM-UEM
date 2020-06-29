# Autopilot App
#!/usr/bin/python3

import socket
import os
#from gpiozero import LED

#led = LED(17)

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serverSocket.bind(("10.0.0.30", 12345))
serverSocket.listen()
while True:
        clientSocket,addr = serverSocket.accept()
        print("Connection from %s" % str(addr))
        command = clientSocket.recv(1024).decode('ascii')
        print("\t" + 'Command Received: ' + command + "\r\n")
        log = command + ' [ACK]' + "\r\n"
        clientSocket.send(log.encode('ascii'))
        clientSocket.close()
        if command == 'ENABLE':
                os.system("cansend can0 007#FFFFFFFF")
                #led.blink()
        else:
                os.system("cansend can0 007#00000000")
                #led.off()