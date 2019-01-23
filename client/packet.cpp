#include "packet.h"
#include <string.h>
#include <string>

namespace packet_system{
  packet::packet(){
    data = nullptr;
    data_size = 0;
    order_num = 0;
    code = 0;
    footer = 0;
    acknowledgment = false;
  }

  // packet::packet(file_util::file_obj& file, bool acknowledgment, 
  // unsigned char order_num): acknowledgment(acknowledgment), order_num(order_num){
  //   data_size = (file.get_rem_size() < 1024)? file.get_rem_size() : 1024;
  //   data = new char[1024];
  //   file.read_file(data, data_size);
  //   //d for data.
  //   code = 'd';
  //   if(data_size < 1024){
  //     footer = 't';
  //   }
  //   else{
  //     footer = 'p';
  //   }
  // }

  packet::packet(std::string filename){
    data_size = filename.length() + 1; //length + null cahr at end.
    data = new char[1024];
    const char* temp_c_str = filename.c_str();

    for(int i = 0; i < data_size; ++i){
      data[i] = temp_c_str[i];
    }

    file_req = true;

    acknowledgment = false;

    code = 'f';
    order_num = 0;
    footer = 't';
  }



  //Send an already allocated packet
  void packet::construct_packet(char* packet){
    packet[0] = code;
    //Send the literal char value of the order num.
    packet[1] = order_num + ORDER_CHAR_OFFSET;
    for(int i = HEADER_OFFSET; i < MAX_DATA_SIZE + HEADER_OFFSET; ++i){
      if(i - HEADER_OFFSET < data_size){
        packet[i] = data[i - HEADER_OFFSET];
      }
      else if( i - HEADER_OFFSET == data_size){
        packet[i] = 0;
      }    
      else if(i -HEADER_OFFSET == data_size + 1){
        packet[i] = 33;
      }

    }
    //Apend the end with footer
      packet[1028] = footer;
  }

  void packet::assemble_sent_packet(char* packet){
    //get header
    data = new char[1029];
    code = packet[0];
    order_num = packet[2] - ORDER_CHAR_OFFSET;
    //get footer
    footer = packet[1028];

    data_size = (footer == 'p') ? 1024 : 0; 

    // //read the data
    // for(int i = HEADER_OFFSET; i < MAX_DATA_SIZE + HEADER_OFFSET; ++i){
    //   data[i - HEADER_OFFSET] = packet[i];
    //   //Found the end of the file
    //   if(packet[i] == 0 && packet[i + 1] == 33 && footer == 't'){
    //     data_size = i;
    //     break;
    //   }
    // }

    memcpy(data, packet + HEADER_OFFSET, MAX_DATA_SIZE);
    // for(int i = 0 i < MAX_DATA_SIZE; ++i){
    //   if(data[i])
    // }

    acknowledgment = true;
  }

  packet::~packet(){
    
    delete[] data;
  }

}  //namespace packet_system
