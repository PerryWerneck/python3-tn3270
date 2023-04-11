#!/usr/bin/python
#-*- coding: utf-8

import tn3270

# Get TN3270 headless object
session = tn3270.Session(":A")

# Connect to host with 10 seconds timeout
session.connect("tn3270://localhost:3270",10)

# Show connection state.
print("Cstate: " + str(session.cstate))
print("Width: " + str(session.width))
print("Connected: " + str(session.connected))

# Show cursor position
print(session.cursor)

# Search for string on terminal
print(session.find("Host"))

# Count string
print(session.count("Host"))

# Get 38 characters at position 14,22
print(session.get(14,22,38))

session.disconnect()

input("Press enter to exit")








