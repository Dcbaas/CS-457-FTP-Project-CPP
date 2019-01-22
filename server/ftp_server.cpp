#include "ftp_server.h"

namespace ftp{
  ftp_server::ftp_server(){}

  void ftp_server::reset(){
    pack_vector.clear();
  }

  void ftp_server::run(){
    while(true){
      await_request();
      if(pack_vector.front().is_file()){
        std::cout << "was file" << std::endl;
      }
      else{
        std::cout << "wasn't file" << std::endl;
      }
      if(!pack_vector.empty() && pack_vector.front().is_file()){
        setup_transmission_pipline();
        do{
          transmit_window();
          //await_ack();
          update_pipline();
        }while(file.get_rem_size() > 0 && win_size >=5);
        std::cout << "Sent File" << std::endl;
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

    //if file is not open don't do stuff. 

    //Clear the pack_vector 
    pack_vector.clear();
    curr_order_num = 0;

    //Load 5 packets
    //for 5 packets or until the file ends.
    
    for(int packet = 0 ; packet < 5 && file.get_rem_size() > 0; ++packet){
      pack_vector.push_back(packet_system::packet(file, false, curr_order_num++));
    }

    win_start = pack_vector.begin();

    for(int i = 0; i <= 5; ++i){
      if(win_end == pack_vector.end()){
        win_size = i + 1;
        break;
      }
      win_end = win_start + i;
    }
  }

  void ftp_server::transmit_window(){
    std::cout<< "Transmitting" <<std::endl;
    for(auto win_it = win_start; win_it < win_end; ++win_it){
      socket.send_packet(*win_it);
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
    for(auto win_it = win_start; win_it < win_end; ++win_it){
      if(win_it->get_acknowledgment()){
        ++offset;
      }
    }

    //Load more data in
    for(int packet = 0; packet < offset && file.get_rem_size() > 0; ++packet){
      pack_vector.push_back(packet_system::packet(file, false, curr_order_num++));
    }

    win_start += offset;

    for(int i = 0; i <= offset; ++i){
      if(win_end == pack_vector.end()){
        win_size = i + 1;
        break;
      }
      win_end = win_start + i;
    }
  }
}

