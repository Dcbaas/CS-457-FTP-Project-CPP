#include "socket.h"

namespace sockets{
  udp_socket::udp_socket(){
    if(socket_file_descriptor < 0){
      //Do some exception stuff
    }
    port = 8008;

    timeout.tv_sec=5;
    timeout.tv_usec=0;
    setsockopt(socket_file_descriptor, SOL_SOCKET,
        SO_RCVTIMEO,&timeout,sizeof(timeout));

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    bind(socket_file_descriptor, (struct sockaddr*)&serveraddr,
        sizeof(serveraddr));
  }

  void udp_socket::send_packet(packet_system::packet& send_packet){
    sendto(socket_file_descriptor, send_packet.get_packet(), send_packet.get_size(),
        0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
  }

  int udp_socket::receive_packet(packet_system::packet& recv_packet){
    char* buffer = new char[1030];
    socklen_t len = sizeof(clientaddr);

    int success = recvfrom(socket_file_descriptor, buffer, 1030, 0, (sockaddr*)&clientaddr, &len);
    if(success != -1){
      recv_packet.construct_packet(buffer);
    }

    return success;
    
  }

  udp_socket::~udp_socket(){
    close(socket_file_descriptor);
  }
}
