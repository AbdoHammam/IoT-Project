import socket               # Import socket module
import os
import mraa
import time

from ctypes import *
lib = cdll.LoadLibrary('./motion_lib.so')
lib.motion_detection.restype = c_char_p
s = socket.socket()         # Create a socket object
host = "192.168.3.2"    # the ip address of the machine that you run the server
port = 5001              # Reserve a port for your service.

s.connect((host, port))

while 1:
    inp = lib.return_string()
    s.send(inp)
    time.sleep(1)
s.close
