#ifndef       FTP_CLIENT_H
#define       FTP_CLIENT_H

#include "socket.h"
#include "file_util.h"
#include "packet.h"

#include <vector>
#include <iostream>

namespace ftp{
  class ftp_client{
    public:
      ftp_client();
      void run();

    private:
      std::array<std::vector<packet_system::packet>::iterator, 5> window;
      std::vector<packet_system::packet> pack_vector;
      file_util::file_obj file;
      sockets::udp_socket socket;

      int offset = 0;
      char current_seq_num{0};

      void send_request();
      void get_response();
      void get_window();
      void send_ack();
      void update_pipline();

      constexpr char ORDER_NUM_LIMIT = 10;
  };
}
#endif
