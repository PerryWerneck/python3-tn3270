#!/usr/bin/python
#-*- coding: utf-8

import tn3270

print("Teste extensão pw3270")

print("Using TN3270 Version " + tn3270.version())
print(tn3270.revision())

session = tn3270.Session(":a")

#print "Using pw3270 version " + term.Version() + " revision " + term.Revision()

#term.Connect("tn3270://zos.efglobe.com:telnet",10);

#print term.IsConnected()
#print term.IsReady()

#print term.GetStringAt(14,19,38)

#print "-----------------------------------------------------------------------"
#print term
#print "-----------------------------------------------------------------------"








