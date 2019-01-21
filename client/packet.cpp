#include "packet.h"

namespace packet_system{

  packet::packet(){
    packet_contents = nullptr;
    packet_size = 0;
    order_num = 0;
    acknowledgment = false;
  }

  void packet::set_acknowledgment(bool acknowledgment){
    this->acknowledgment = acknowledgment;
  }

  packet::packet(std::string filename){
    packet_size = PACKET_CODE_SIZE + ORDER_NUM_SIZE + filename.length() + 1;
    packet_contents = new char[packet_size];

    packet_code = {'f', 'i', 'l'};

    //Load the Code 
    for(int index = 0; index < PACKET_CODE_SIZE; ++index){
      packet_contents[index] = packet_code[index];
    }

    packet_contents[3] = 0;

    const char* c_str_filename = filename.c_str();
    for(int index = PACKET_CODE_SIZE + ORDER_NUM_SIZE; index < packet_size; ++index){
      packet_contents[index] = 
        c_str_filename[index - (PACKET_CODE_SIZE + ORDER_NUM_SIZE)];
    }

    is_file_req = true;
  }

  bool packet::get_acknowledgment() const{ return acknowledgment; }

  char* packet::get_packet() const{ return packet_contents; }

  char* packet::get_data(){
    if(is_file_req || packet_contents[0] == 'n'){
      return packet_contents + PACKET_CODE_SIZE + ORDER_NUM_SIZE;
    }
    return packet_contents + 
      PACKET_CODE_SIZE + ORDER_NUM_SIZE + SIZE_INDICATOR_SIZE;
  }

  void packet::construct_packet(char* data){
    this->packet_contents = data;

    //Extract the header
    for(int index = 0; index < PACKET_CODE_SIZE + ORDER_NUM_SIZE; ++index){
      if(index < 3){
        packet_code[index] = packet_contents[index];
      }
      else{
        order_num = packet_contents[index];
      }
      //Check for partial packet
      if(packet_contents[0] == 'n'){
        packet_size = MAX_CONTENT_SIZE + PACKET_CODE_SIZE + ORDER_NUM_SIZE;

      }
      else if( packet_contents[0] == 's'){
        packet_size = (packet_contents[4] << BITSHIFT) + packet_contents[5];
      }
      else if(packet_contents[0] == 'a'){
        //Do something
      }

      acknowledgment = true;
    }
  }

  packet::~packet(){
    delete[] packet_contents;
  }

}  //namespace packet_system
