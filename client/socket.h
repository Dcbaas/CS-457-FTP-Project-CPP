#ifndef     UDP_SOCKET_H
#define     UDP_SOCKET_H

#include "packet.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace sockets{
  class udp_socket{
    public:
      udp_socket();
      udp_socket(int port);
      void send_packet(packet_system::packet& send_packet);
      int receive_packet(packet_system::packet& recv_packet);
      ~udp_socket();
    private:
      int socket_file_descriptor{socket(AF_INET,SOCK_DGRAM,0)};
      int port;
      struct timeval timeout;
      struct sockaddr_in serveraddr;
      struct sockaddr_in clientaddr;
  };
}
#endif
