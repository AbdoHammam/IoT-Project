import socket, sys
import threading
import time
#import mraa
import json
import webbrowser
import math
import urllib
import urllib2
from gmplot import gmplot
import webbrowser, os
import time
 
 
TCP_IP = '192.168.43.119' # your ip

TCP_PORTS = [5001,5002,5003,5004,5005,5006,5007,5008,5050]

flag=[]
flag.append(True) 
BUFFER_SIZE = 1024
lstOfLocations = {}
 
class listen_to_port(threading.Thread):
 
    def __init__(self,thread_name,ip,port_number,buffer_size):
                threading.Thread.__init__(self)
                self.thread_name=thread_name
                self.ip=ip
                self.port_number=port_number
                self.buffer_size=buffer_size
 

    def run(self):
        print("opening thread: "+self.thread_name)
 
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 
        s.bind((self.ip, self.port_number))
 
        s.listen(1)
       
        while 1:
                conn, addr = s.accept()
                print ('Connection address:', addr)
                #gmap = gmplot.GoogleMapPlotter(30.0307949, 31.2100348, 13)
                while 1:
                        data = conn.recv(self.buffer_size)
                        print ("received data:", data)
                        a, b, c = self.parseJson(data)
                        lstOfLocations[a]=(b,c)

                	gmap = gmplot.GoogleMapPlotter(30.0307949, 31.2100348, 13)
                	for i,j in lstOfLocations.items():
                    		gmap.marker(j[0]+(i/1000.0), j[1]+(i/1000.0), 'cornflowerblue')
                    	#conn.close()
                	if flag[0] == True:
                    		webbrowser.open("my_map.html", new=1)
                    		gmap.draw("my_map.html")
                    		flag[0]=False
                	else:
                    		gmap.draw("my_map.html")
                    		time.sleep(3)
 
        s.close()
        s = none
 
 
    def parseJson(self, json):
        json = str(json).split('\n')
        json = json[0]
        x, y, z = str(json).split(',')
        x = float(x[x.find(':')+1:])
        y = float(y[y.find(':')+1:])
        z = float(z[z.find(':')+1:-2])
        return  x, y, z
 
 
 
for port_number in TCP_PORTS:
    try:
        thread =listen_to_port("Thread"+str(port_number),TCP_IP,port_number,BUFFER_SIZE)
        thread.start()
    except:
        print("problem in starting thread")
