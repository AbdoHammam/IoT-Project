import socket
import os
import mraa
import time

from ctypes import *
lib = cdll.LoadLibrary('./temperature.so')
lib.my_string.restype = c_char_p
s = socket.socket()         # Create a socket object
host = "192.168.3.2"    # the ip address of the machine that you run the server
port = 5003              # Reserve a port for your service.

s.connect((host, port))

while 1:
        inp = lib.my_string()
        s.send(inp)
        time.sleep(1)
s.close
