#include "ftp_server.h"

namespace ftp{
  ftp_server::ftp_server(){}

  void ftp_server::reset(){
    pack_vector.clear();
  }

  void ftp_server::run(){
    while(true){
      await_request();

      if(!pack_vector.empty() && pack_vector.front().get_is_file_req()){
        setup_transmission_pipline();
        while(file.get_rem_size() > 0 && !verify_ack()){
          transmit_window();
          //await_ack();
          update_pipline();
        }
        reset();
      }
    }
  }

  void ftp_server::await_request(){
    pack_vector.push_back(packet_system::packet());
    while(socket.receive_packet(pack_vector.front()) == -1){
      std::cout << "Waiting for messg" << std::endl;
    }
  }

  void ftp_server::setup_transmission_pipline(){
    //Setup file
    std::string filename{pack_vector.front().get_data()};

    file.update_objet(filename, true);

    //Clear the pack_vector 
    pack_vector.clear();
    curr_order_num = 0;

    //Load 5 packets
    //for 5 packets or until the file ends.
    int packet = 0;
    for(packet ; packet < 5 && file.get_rem_size() > 0; ++packet){
      pack_vector.push_back(packet_system::packet(file, false, curr_order_num++));
    }

    //Assign the window
    for(int win_element = 0; win_element < packet; ++win_element){
      window[win_element] = pack_vector.begin() + win_element;
    }

  }

  void ftp_server::transmit_window(){
    //Transmit all of the packets in sequence 
    //For each packet iterator in the window
    for(auto packet: window){
      //If we are at the end of the vector
      //Stop transmitting stuff.
      if(packet == pack_vector.end()){
        break;
      }
      socket.send_packet(*packet);
      //TODO remove the next line. This line maually sets the acknowledgment to true
      packet->set_acknowledgment(true);
    }
  }

  //TODO implement this memeber function
  void ftp_server::await_ack(){
    return;
  }

  void ftp_server::update_pipline(){
    char offset = 0;

    //Check for all acknowledged packets until one is found 
    //not to be acknowledged. This determines the offset to go to 
    //for the next transmission.
    for(auto packet: window){
      if(packet->get_acknowledgment()){
        ++offset;
      }
      else{
        break;
      }
    }

    //Load more data in
    for(int packet = 0; packet < offset && file.get_rem_size() > 0; ++packet){
      pack_vector.push_back(packet_system::packet(file, false, curr_order_num++));
    }

    //Shift the window. If one of them reaches the end iterator than stop
    for(auto packet: window){
      packet = packet + offset;
      //if we hit the end, stop shifting iterators this is the stopping point.
      if(packet == pack_vector.end()){
        break;
      }
    }
  }

  bool ftp_server::verify_ack(){
    for(auto packet : pack_vector){
      if(!packet.get_acknowledgment()){
        return false;
      }
    }
    return true;
  }
}

