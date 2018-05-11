import socket, sys
import threading
import time
import mraa
import json
TCP_IP = '192.168.1.100'
from math import sin,cos,atan2,sqrt,radians
TCP_PORTS = [5005,5008]
 
BUFFER_SIZE = 1024




l1=[]
l1.append(-1.0)
l1.append(-1.0)
l2=[]
l2.append(-1.0)
l2.append(-1.0)
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
                gpio_1 = mraa.Gpio(7)
                gpio_1.dir(mraa.DIR_OUT)
                current_status = 0
                while 1:
 
                        data = conn.recv(self.buffer_size)
                        if data.find("on") != -1:
          	        	current_status = 1
                        else:
                                current_status = 0
                        if data.find("Board") != -1:
				data = data.replace('\n','')
				j = json.loads(data)

				if j["Board"]==1:
					l1[0] = radians(j["Latitude"])
					l1[1] = radians(j["Longitude"])
					print "Board1\n"
				else:
					l2[0] = radians(j["Latitude"])
					l2[1] = radians(j["Longitude"])
					print "Board2\n"

				if l1[0] != -1.0 and l2[0] != -1.0:
					dlong = l2[1] - l1[1]
					dlat = l2[0] - l1[0]
					a = sin(dlat / 2)**2 + cos(l1[0]) * cos(l2[0]) * sin(dlong/2)**2
					c = 2 * atan2(sqrt(a) , sqrt(1-a))
					distance = 6373.0 * c * 1000
					print distance
					if distance < 2000:
						gpio_1.write(1)
					#break
#			gpio_1.write(current_status)
                        print ("received data:", data)

                        if data == 'close':
                                break
                conn.close()
        s.close()
        s = none
for port_number in TCP_PORTS:
    try:
        thread =listen_to_port("Thread"+str(port_number),TCP_IP,port_number,BUFFER_SIZE)
        thread.start()
    except:
	print("problem in starting thread")
