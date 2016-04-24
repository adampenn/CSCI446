## Authors:
##  Adam Penn
##  Thomas Greenman
## Class:
## 	CSCI446-01
##	Spring 2016	
## Makfile for creating two executables named 'server' and 'client'

all: client server

## creating client executable
client: client.c
	gcc -g -Wall client.c -o client

## creating server executable
server: server.c
	gcc -g -Wall server.c -o server

## adding remove client and server executable option
clean:
	rm client server
