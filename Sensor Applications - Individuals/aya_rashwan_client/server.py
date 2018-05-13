import socket, sys
import threading
import time
import mraa
 
TCP_IP = '169.254.155.152' # your ip
 
TCP_PORTS = [5008]
 
BUFFER_SIZE = 1024
 
 
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
                        gpio_1.write(current_status)
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
