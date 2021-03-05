# This project requires PyBluez
from Tkinter import *

import bluetooth

# Look for all Bluetooth devices
# the computer knows about.
print "Searching for devices..."
print ""
# Create an array with all the MAC
# addresses of the detected devices
nearby_devices = bluetooth.discover_devices()
# Run through all the devices found and list their name
num = 0
print "Select your device by entering its coresponding number..."
for i in nearby_devices:
    num += 1
    print num, ": ", bluetooth.lookup_name(i)

# Allow the user to select their Arduino
# bluetooth module. They must have paired
# it before hand.
selection = input("> ") - 1
print "You have selected", bluetooth.lookup_name(nearby_devices[selection])
bd_addr = nearby_devices[selection]

port = 1


# Create the GUI
class Application(Frame):
    # Create a connection to the socket for Bluetooth
    # communication
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)

    def disconnect(self):
        # Close socket connection to device
        self.sock.close()

    def forward(self):
        # Send 'H' which the Arduino
        # detects as turning the light on
        data = "a"
        self.sock.send(data)

    def stop(self):
        data = "c"
        self.sock.send(data)

    def left(self):
        data = "d"
        self.sock.send(data)

    def right(self):
        data = "b"
        self.sock.send(data)

    def rev(self):
        data = "e"
        self.sock.send(data)

    def lighton(self):
        data = "m"
        self.sock.send(data)

    def lightoff(self):
        data = "n"
        self.sock.send(data)


    def createWidgets(self):

        self.but1 = Button(root)
        self.but1["text"] = "^",
        self.but1["fg"] = "black"
        self.but1["command"] = self.forward
        self.but1.place(relx=0.2, rely=0.35, relwidth=0.1, relheight=0.2)

        self.but2 = Button(root)
        self.but2["text"] = "stop"
        self.but2["fg"] = "gray"
        self.but2["command"] = self.stop
        self.but2.place(relx=0.5, rely=0.6, relwidth=0.4, relheight=0.2)

        self.but3 = Button(root)
        self.but3["text"] = "<"
        self.but3["fg"] = "gray"
        self.but3["command"] = self.left
        self.but3.place(relx=0.05, rely=0.6, relwidth=0.1, relheight=0.2)

        self.but4 = Button(root)
        self.but4["text"] = ">"
        self.but4["fg"] = "gray"
        self.but4["command"] = self.right
        self.but4.place(relx=0.35, rely=0.6, relwidth=0.1, relheight=0.2)

        self.but5 = Button(root)
        self.but5["text"] = "v"
        self.but5["fg"] = "gray"
        self.but5["command"] = self.rev
        self.but5.place(relx=0.2, rely=0.6, relwidth=0.1, relheight=0.2)

        self.but6 = Button(root)
        self.but6["text"] = "horn"
        self.but6["fg"] = "gray"
        self.but6["command"] = self.stop
        self.but6.place(relx=0.55, rely=0.35, relwidth=0.1, relheight=0.2)

        self.but7 = Button(root)
        self.but7["text"] = "empty"
        self.but7["fg"] = "gray"
        self.but7["command"] = self.stop
        self.but7.place(relx=0.75, rely=0.35, relwidth=0.1, relheight=0.2)

        root.bind("w", lambda event: self.forward())
        root.bind("a", lambda event: self.left())
        root.bind("s", lambda event: self.rev())
        root.bind("d", lambda event: self.right())
        root.bind("e", lambda event: self.stop())
        root.bind("r", lambda event: self.lighton())
        root.bind("t", lambda event: self.lightoff())



    def __init__(self, master=None):
        # Connect to the bluetooth device
        # and initialize the GUI
        self.sock.connect((bd_addr, port))
        Frame.__init__(self, master)
        self.pack()
        self.createWidgets()

root = Tk()
root.geometry("600x300")
root.title("Wonderer")
app = Application(master=root)
app.mainloop()
root.destroy()