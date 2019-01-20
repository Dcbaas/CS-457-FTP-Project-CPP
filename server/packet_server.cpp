#include "packet.h"

namespace packet_system{
  packet::packet(file_util::file_obj& file, bool acknowledgment, unsigned char order_num): acknowledgment(acknowledgment), order_num(order_num){

    //The file remaining is less then 1024 bytes
    if(file.get_rem_size() < 1024){
      packet_size = file.get_rem_size() + PACKET_CODE_SIZE + ORDER_NUM_SIZE + SIZE_INDICATOR_SIZE;

      packet_code = {'s','r','t'};

      //Split the value of remaining size into 2 chars for inside the packet.
      char front_rem = (file.get_rem_size() & FRONT_MASK) >> BITSHIFT;
      char back_rem = file.get_rem_size() & BACK_MASK;

      packet_contents = new char[packet_size];

      for(int index = 0; index < PACKET_CODE_SIZE; ++index){
        packet_contents[index] = packet_code[index];
      }

      packet_contents[3] = order_num;

      packet_contents[4] = front_rem;
      packet_contents[5] = back_rem;
      file.read_file(packet_contents + PACKET_CODE_SIZE + ORDER_NUM_SIZE + SIZE_INDICATOR_SIZE, file.get_rem_size());
    }
    //Normal packet
    else{
      packet_size = MAX_CONTENT_SIZE + PACKET_CODE_SIZE + ORDER_NUM_SIZE;
      packet_contents = new char[packet_size];

      packet_code = {'n','m', 'l'};

      //Load the code 
      for(int index = 0; index < PACKET_CODE_SIZE; ++index){
        packet_contents[index] = packet_code[index];
      }

      //Load order number
      packet_contents[3] = order_num;

      //Read the data in
      file.read_file(packet_contents + PACKET_CODE_SIZE + ORDER_NUM_SIZE);
    }
  }

  void packet::set_acknowledgment(bool acknowledgment){
    this->acknowledgment = acknowledgment;
  }

  bool packet::get_acknowledgment() const{ return acknowledgment; }

  char* packet::get_packet() const{ return packet_contents; }

  packet::~packet(){
    delete[] packet_contents;
  }

}  //namespace packet_system
