#!/usr/bin/python
#-*- coding: utf-8

import inspect
import tn3270

print("Teste extensão pw3270")

print("Using TN3270 Version " + tn3270.version())
print(tn3270.revision())

session = tn3270.Session("")

print("Using tn3270 version " + session.version + " revision " + session.revision)

print(session.cstate)
print(session.width)
print(session.connected)
print(session.url)

session.connect('')

print(session.connected)

print('----------------------')
inspect.getmembers(session)
print('----------------------')



#print term.IsConnected()
#print term.IsReady()

#print term.GetStringAt(14,19,38)

#print "-----------------------------------------------------------------------"
#print term
#print "-----------------------------------------------------------------------"

del session
input("Press enter to exit")








