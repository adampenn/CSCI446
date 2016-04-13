## Authors:
##  Adam Penn
##  Thomas Greenman
## Class:
## 	CSCI446-01
##	Spring 2016	
## Makfile for creating two executables named 'server' and 'client'

all: client server

client: client.c
	gcc -Wall client.c -o client
server: server.c
	gcc -Wall server.c -o server
clean:
	rm client server
