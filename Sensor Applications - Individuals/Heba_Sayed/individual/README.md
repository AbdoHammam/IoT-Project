Temperature/Humidity sensor used is DHT11 

Recieved Data format:
The 8bit humidity integer data + 8bit the Humidity decimal data 
+8 bit temperature integer data + 8bit fractional temperature data +8 bit parity bit.

Example: 
40 bit data is received:
0011 0101 High humidity
0000 0000 Low humidity
0001 1000 High temperature
0000 0000 Low temperature
0100 1001 Parity bit
 
Calculations:
0011 0101+0000 0000+0001 1000+0000 0000
=
0100 1101
01001101
?
0100 1001
The received data is not correct, as the checksum is not equal

.................
Recieved bits ar calculated in the code using how many times the signal came high then went low or vice versa

the refrence datasheet for DHT11
https://akizukidenshi.com/download/ds/aosong/DHT11.pdf