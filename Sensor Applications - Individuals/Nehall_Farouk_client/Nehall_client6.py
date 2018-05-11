import mraa
import time
import socket           # socket module
import os

from ctypes import *

lib = cdll.LoadLibrary('./example.so')
lib.return_string.restype = c_char_p
s = socket.socket()     

host = "192.168.3.2"   
port = 5006        

s.connect((host, port))

while 1:
    inp = lib.return_string()
    s.send(inp)
    time.sleep(1)
s.close
