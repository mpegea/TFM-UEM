# Autopilot App
# !/usr/bin/python3
from tkinter import *
from tkinter import messagebox
import socket

# Functions
def sendCommand(command):
        import socket
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.connect(("10.0.0.30", 12345))
        serverSocket.send(command.encode('ascii'))
        log = serverSocket.recv(1024)
        serverSocket.close()
        print (log.decode('ascii'))

def enableAutonomousMode():
        sendCommand('ENABLE')
        msg = messagebox.showinfo( "Autopilot Info", "Autonomous Mode Enabled!")
        button.config(text = 'Disable')
        button.config(command = disableAutonomousMode)

def disableAutonomousMode():
        sendCommand('DISABLE')
        msg = messagebox.showinfo( "Autopilot Info", "Autonomous Mode Disabled!")
        button.config(text='Enable')
        button.config(command = enableAutonomousMode)

# Main Window
mainWindow = Tk()
mainWindow.title('Autopilot Management Console')
mainWindow.geometry("480x360")
backgroundImage = PhotoImage(file = "background.gif")
label=Label(mainWindow, image=backgroundImage)
label.pack(side=TOP)
button = Button(mainWindow, text = 'Enable', command = enableAutonomousMode) #Startup status, then updated through button
button.place(x = 200,y = 200)
mainWindow.mainloop()