#include "socket.h"

namespace sockets{
  udp_socket::udp_socket(int port){
    if(socket_file_descriptor < 0){
      //Do some exception stuff
    }

    timeout.tv_sec=3;
    timeout.tv_usec=0;
    setsockopt(socket_file_descriptor, SOL_SOCKET,
        SO_RCVTIMEO,&timeout,sizeof(timeout));

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);
    //TODO: Remove default IP
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(socket_file_descriptor, (struct sockaddr*)&serveraddr,
        sizeof(serveraddr));
  }

  void udp_socket::send_packet(packet_system::packet& send_packet){
    char* packet = new char[1029];
    send_packet.construct_packet(packet);
    sendto(socket_file_descriptor,packet, packet_system::packet::PACKET_SIZE, 
        0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));

    delete[] packet;
  }

  int udp_socket::receive_packet(packet_system::packet& recv_packet){
    char* buffer = new char[1029];
    socklen_t len = sizeof(serveraddr);

    int success = recvfrom(socket_file_descriptor, buffer, 1030, 0, 
    (sockaddr*)&serveraddr, &len);
    if(success != -1){
      recv_packet.construct_packet(buffer);
    }
    delete[] buffer;
    return success;
  }

  udp_socket::~udp_socket(){
    close(socket_file_descriptor);
  }
}

