#ifndef         FTP_SERVER_H
#define         FTP_SERVER_H

#include "socket.h"
#include "file_util.h"
#include "packet.h"
#include <vector>
#include <iostream>

namespace ftp{
  class ftp_server{
    public:

      ftp_server();
      void run();

    private:
      int curr_order_num{0};
      std::vector<packet_system::packet> pack_vector;
      file_util::file_obj file;
      sockets::udp_socket socket;

      //std::array<std::vector<packet_system::packet>::iterator, 5> window;
      std::vector<packet_system::packet>::iterator win_start;
      std::vector<packet_system::packet>::iterator win_end;
      char win_size{5};
      
      bool at_end{false};

      int offset{0};
      char current_seq_num{0};
      
      void reset();
      void await_request();

      void setup_transmission_pipline();
      void transmit_window();
      void await_ack();
      void update_pipline();
      bool verify_ack();

      static constexpr char ORDER_NUM_LIMIT = 10;

  };
}

#endif
