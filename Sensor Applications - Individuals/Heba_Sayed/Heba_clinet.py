import socket             
import os
import mraa
import time
 
from ctypes import *
lib = cdll.LoadLibrary('./light.so')  
lib.return_string.restype = c_char_p
s = socket.socket()         
host = "192.168.3.2"    
port = 5002             
 
s.connect((host, port))
 
while 1:
    inp = lib.return_string()
    s.send(inp)
    time.sleep(1)
s.close