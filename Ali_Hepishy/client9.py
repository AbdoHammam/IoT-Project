#!/usr/bin/env python
import socket               # Import socket module
import os
import mraa
import time

from ctypes import *
lib = cdll.LoadLibrary('./example.so')  # example.so is the name of your C/C++ dynamic library you created.
lib.return_string.restype = c_char_p
s = socket.socket()         # Create a socket object
host = "10.13.1.22"    # the ip address of the machine that you run the server
port = 5004              # Reserve a port for your service.

s.connect((host, port))

while 1:
    inp = lib.return_string()
    s.send(inp)
    time.sleep(1)
s.close