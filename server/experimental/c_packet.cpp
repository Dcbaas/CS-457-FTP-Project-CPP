#include "c_packet.h"

#include <string.h>



void construct_from_file(packet* c_packet,file_util::file_obj& file, bool acknowledgment, int order_num, bool is_file){
  c_packet->data_size = (file.get_rem_size() < 1024)? file.get_rem_size() : 1024;
  file.read_file(c_packet->data, c_packet->data_size);
  c_packet->ack = acknowledgment;
  c_packet->order_num = order_num;
  c_packet->is_file = is_file;
}

void construct_from_packet(packet* c_packet, char* buffer){
}
