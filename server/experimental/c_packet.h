#ifndef             C_PACKET_H
#define             C_PACKET_H

#include "file_util.h"


typedef struct packet{
    char data[1024];
    int data_size;
    int order_num;
    bool ack;
    bool is_file;
} packet;



void construct_from_file(packet* c_packet,file_util::file_obj& file, bool acknowledgment, int order_num, bool is_file);

void construct_from_packet(packet* c_packet, char* buffer);

void send_packet(char* buffer);

#endif
