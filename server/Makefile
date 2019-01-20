#Server Makefile
#Author: David Baas

test: file_util.o test.o
	clang++ file_util.o test.o

packet_server.o: packet_server.cpp
	clang++ -c packet_sever.cpp
file_util.o: file_util.cpp
	clang++ -c file_util.cpp

test.o: test.cpp
	clang++ -c test.cpp
