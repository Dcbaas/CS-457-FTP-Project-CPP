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

  bool packet::get_acknowledgment() const{ return acknowledgment; }

  char* packet::get_packet() const{ return packet_contents; }

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
