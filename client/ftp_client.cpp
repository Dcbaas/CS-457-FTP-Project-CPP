#include "ftp_client.h"

namespace ftp{
  ftp_client::ftp_client(){}

  void ftp_client::run(){
    setup_client();
    send_request();
    //TODO: wait for a packet that says this file exist then do the rest
    while(!end){
      //rename to get transmission
      get_transmission();
      send_ack();
      if(!end){
        update_pipline();
      }
    }
    //Reset when done.
  }

  void ftp_client::send_request(){
    std::cout << "What file do you want?: ";

    std::string filename;
    std::cin >> filename;
    packet_system::packet file_req{filename};
    socket.send_packet(file_req);
  }

  void ftp_client::get_response(){
  }

  void ftp_client::setup_client(){
    //Load five default packets to start
    for(int packet = 0; packet < 5; ++packet){
      pack_vector.push_back(packet_system::packet());
    }

    //Setup the window
    for(int win_element = 0; win_element < 5; ++win_element){
      window[win_element] = pack_vector.begin() + win_element;
    }
  }

  void ftp_client::get_transmission(){
    for(auto packet: window){
      socket.receive_packet(*packet);
    }
  }

  //Sort the window and write it to file.
  void ftp_client::consolidate_transmission(){
    for(auto packet: window){
      if(packet->get_size() > 0){
        file.write_file(packet->get_data());
        if(packet->get_packet()[0] == 's'){
          //End equals true;
          return;
        }
      }
    }

  }

  void ftp_client::send_ack(){
  }

  void ftp_client::update_pipline(){
    for(auto packet: window){
      if(packet->get_acknowledgment()){
        ++offset;
      }
      else{
        break;
      }
    }

    //Load more data in
    for(int packet = 0; packet < offset; ++packet){
      pack_vector.push_back(packet_system::packet());
    }

    //Shift the window. If one of them reaches the end iterator than stop
    for(auto packet: window){
      packet = packet + offset;
      //if we hit the end, stop shifting iterators this is the stopping point.
    }
  }

}

