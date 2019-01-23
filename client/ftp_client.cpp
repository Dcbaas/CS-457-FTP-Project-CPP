#include "ftp_client.h"
#include <fstream>

namespace ftp{
  ftp_client::ftp_client(){}

  void ftp_client::run(){
    setup_client();
    std::cout << "ding" <<std::endl;
    send_request();
    //TODO: wait for a packet that says this file exist then do the rest
    while(end == false){
      //rename to get transmission
      get_transmission();
      consolidate_transmission();
      send_ack();
      if(end == false){
        update_pipline();
      }
    }
    // file.~file_obj();
    file.end_file();
    std::cout << "end" <<std::endl;
    return;
    //Reset when done.
  }

  void ftp_client::send_request(){
    std::cout << "What file do you want?: ";

    std::string filename{"test.txt"};
    // std::cin >> filename;
    // std::cout << "Writing packet" << std::endl;
    packet_system::packet file_req{filename};
    // std::cout << "Wrote packet" << std::endl;
    file.start_file(filename);
    std::ofstream file(filename);
    socket.send_packet(file_req);
    std::cout << "Sent packet" << std::endl;
  }

  void ftp_client::get_response(){
  }

  void ftp_client::setup_client(){
    //Load five default packets to start
    for(int packet = 0; packet < 5; ++packet){
      pack_vector.push_back(packet_system::packet());
    }

    win_start = pack_vector.begin();
    win_end = pack_vector.end();

    std::cout << "Setup Client" << std::endl;
  }

  void ftp_client::get_transmission(){
    std::cout << "pre transmission" << std::endl;
    for(auto win_it = win_start; win_it < win_end; ++win_it){
      std::cout << "waiting" <<std::endl;
      socket.receive_packet(*win_it);
    }
    std::cout << "Got Transmission" << std::endl;
  }

  //Sort the window and write it to file.
  void ftp_client::consolidate_transmission(){

    for(auto win_it = win_start; win_it < win_end; ++win_it){
      
      std::cout << "writing" <<std::endl;
      // file.write_file(win_it->get_data());
      if(win_it->is_partial()){
        //End equals true;
        //Return
        end = true;
        return;
      }
      
    }

  }

  void ftp_client::send_ack(){
  }

  void ftp_client::update_pipline(){
    int offset = 5;
    // for(auto packet: window){
    //   if(packet->get_acknowledgment()){
    //     ++offset;
    //   }
    //   else{
    //     break;
    //   }
    // }

    //Load more data in
    for(int packet = 0; packet < offset; ++packet){
      pack_vector.push_back(packet_system::packet());
    }

    //Shift the window. If one of them reaches the end iterator than stop
    win_start += 5;
    win_end += 5;
  }

}

