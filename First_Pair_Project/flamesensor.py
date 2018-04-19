import socket             
import os
import mraa
import time
 
from ctypes import *
lib = cdll.LoadLibrary("./example.so")  
lib.return_string.restype = c_char_p
s = socket.socket()         
host = "169.254.155.152"   
port = 5008              
 
s.connect((host, port))
 
while 1:
    inp = lib.return_string()
    s.send(inp)
    time.sleep(1)
s.close
