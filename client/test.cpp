#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "file_util.h"
#include "packet.h"
#include <unistd.h>
#include "socket.h"
int main(int argc, char** argv){


  packet_system::packet test_pack;

  file_util::file_obj test_file{"out.txt", false};

  sockets::udp_socket in_socket{8008};

  in_socket.receive_packet(test_pack);

  char* result = test_pack.get_packet();

  for(int i = 0; i < test_pack.get_size(); ++i){
    std::cout << result[i];
  }


  return 0;
}
