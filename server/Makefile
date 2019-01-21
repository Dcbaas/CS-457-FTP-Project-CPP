#Server Makefile
#Author: David Baas

all: packet_server.o file_util.o socket.o ftp_server.o main.o
	clang++ main.o packet_server.o file_util.o socket.o ftp_server.o -o server

packet_server.o: packet_server.cpp
	clang++ -c packet_server.cpp

file_util.o: file_util.cpp
	clang++ -c file_util.cpp

test.o: test.cpp
	clang++ -c test.cpp

socket.o: socket.cpp
	clang++ -c socket.cpp

ftp_server.o: ftp_server.cpp
	clang++ -c ftp_server.cpp

main.o: main.cpp
	clang++ -c main.cpp	
