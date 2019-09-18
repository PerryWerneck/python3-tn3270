#!/usr/bin/python
#-*- coding: utf-8

import weakref
import tn3270

print("Teste extensão pw3270")

print("Using TN3270 Version " + tn3270.version())
print(tn3270.revision())

session = tn3270.Session("")

del session

input("Press enter to exit")

#print("Using tn3270 version " + session.version + " revision " + session.revision)

#print(session.cstate)
#print(session.width)
#print(session.connected)
#print(session.url)

# print(session.connect)

#print(session.connected)

#print term.IsConnected()
#print term.IsReady()

#print term.GetStringAt(14,19,38)

#print "-----------------------------------------------------------------------"
#print term
#print "-----------------------------------------------------------------------"








