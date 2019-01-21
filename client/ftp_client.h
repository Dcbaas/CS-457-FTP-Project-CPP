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
      sockets::udp_socket socket{8008};

      int offset = 0;
      bool end{false};
      char current_seq_num{0};

      void setup_client();
      void send_request();
      void get_response();
      void get_transmission();
      void consolidate_transmission();
      void send_ack();
      void update_pipline();

      static constexpr char ORDER_NUM_LIMIT = 10;
  };
}
#endif
