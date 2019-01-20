#Server Makefile
#Author: David Baas

test: file_util.o test.o
	clang++ file_util.o packet_server.o test.o -g

packet_server.o: packet_server.cpp
	clang++ -c packet_server.cpp

file_util.o: file_util.cpp
	clang++ -c file_util.cpp

test.o: test.cpp
	clang++ -c test.cpp
