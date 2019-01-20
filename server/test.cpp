#include <iostream>
#include "file_util.h"
#include "packet.h"

int main(int argc, char** argv){

  file_util::file_obj test_file{"test.txt", true};

  packet_system::packet test_pack{test_file, false, 5};


  char* result = test_pack.get_packet();

  for(int i = 0; i < test_pack.get_size(); ++i){
    std::cout << result[i];
  }
  return 0;
}
