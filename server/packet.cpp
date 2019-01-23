#include "packet.h"
#include <string.h>
#include <string>

namespace packet_system{

    packet::packet(int acknowleged){
      this->acknowledgment = true;
      code = 'a';

      //The order num becomes the num of the acknowledged packet.
      order_num = acknowleged;
    }

    packet::packet(file_util::file_obj& file, bool acknowledgment, int order_num){
      data_size = (file.get_rem_size() < 1024) ? file.get_rem_size() : 1024;

      code = 'd';

      char temp[1024];

      file.read_file(temp, data_size);

      for(int i = 0; i < data_size; ++i){
        data.push_back(temp[i]);
      }

      this->order_num = order_num; 

      footer = (data_size < 1024) ? 't' : 'p';
    }

    packet::packet(std::string filename){
      for(auto file_it = filename.begin(); file_it != filename.end(); ++file_it){
        data.push_back(*file_it);
      }
        code = 'f'; 
        data_size = filename.length() + 1;
        footer = 't';
    }

    void packet::construct_packet(char* packet){
      packet[0] = code;
      memcpy(&packet[1], &order_num, 4);

      memcpy(&packet[5], &data[0], 1024);

      packet[1031] = footer;
    }

    void packet::assemble_sent_packet(char* packet){
      code = packet[0];
      if(code == 'f'){
        file_req = true;
      }
      memcpy(&order_num, &packet[1], 4);
      footer = packet[1031];
      for(int i = 5; i < 5 + 1024; ++i){
        if(i < 5+ 1024 - 1 && footer == 't'){
          if(packet[i] == 0 && packet[i+1] == 33){
            data_size = i;
            break;
          }
        }
        data.push_back(packet[i]);
      }
      acknowledgment = true;
    }
}
