#!/usr/bin/python
# -*- coding: utf-8 -*-
import urllib, sys, re, BeautifulSoup
from xml.dom import minidom

params = ""
i = 1
while i < len(sys.argv):
    params += sys.argv[i]
    if i != len(sys.argv) - 1:
        params += ' '
    i += 1

r = re.compile(r"(quel(le|).(es(t|).(la.m.teo|le temps).|temps.fai..il).(a|à).)(.{0,200})")
results = r.findall(params)

codeSrc = urllib.urlopen('http://api.openweathermap.org/data/2.5/weather?lang=fr&q=' + results[0][len(results[0]) - 1] +'&mode=xml').read()

xmlFile = open('test.xml', 'w')
xmlFile.write(codeSrc)
xmlFile.close()

xmldoc = minidom.parse('test.xml')
temperature = xmldoc.getElementsByTagName('temperature')
humidity = xmldoc.getElementsByTagName('humidity')
weather = xmldoc.getElementsByTagName('weather')
print str(float(temperature[0].attributes['value'].value.encode('utf-8','ignore')) - 273.15) + ' °C'
print humidity[0].attributes['value'].value.encode('utf-8','ignore') + ' %'
print weather[0].attributes['value'].value.encode('utf-8','ignore')

