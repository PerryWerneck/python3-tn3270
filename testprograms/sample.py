#!/usr/bin/python
#-*- coding: utf-8

#import inspect
import tn3270

print("Using TN3270 Version " + tn3270.version())
print(tn3270.revision())

session = tn3270.Session("")
session.timeout = 10

print("Using tn3270 version " + session.version + " revision " + session.revision)

print(session.timeout)

#print(session.cstate)
#print(session.width)
#print(session.connected)
print(session.url)
session.url = "http://www.google.com"
print(session.url)

#print(session.reconnect)

#
# Can reconnect? If yes do it!
#
#if session.reconnect.activatable:
#    print("Reconnecting...")
#    session.reconnect().wait(10)

#print(session.connected)
#print(session.find('sisbb'))
#print(session.count('sisbb'))

#print('----------------------')
#print(dir(session))
#print('----------------------')

#print(session.get(14,22,38))

#print("-----------------------------------------------------------------------")
#print(session)
#print("-----------------------------------------------------------------------")

#session.enter().wait(14,2,"Senha")

#session.set("value")

#print("-----------------------------------------------------------------------")
#print(session)
#print("-----------------------------------------------------------------------")

input("Press enter to exit")








