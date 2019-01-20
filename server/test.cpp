#include <iostream>
#include "file_util.h"
#include "packet.h"
#include "socket.h"

using namespace packet_system;
int main(int argc, char** argv){

  file_util::file_obj test_file{"test.txt", true};

  packet_system::packet test_pack{test_file, false, 5};

  sockets::udp_socket test_socket;

  test_socket.send_packet(test_pack);

  return 0;
}
