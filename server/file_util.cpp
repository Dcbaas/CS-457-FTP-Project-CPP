#include "file_util.h"

#include <exception>

namespace file_util{
  file_obj::file_obj(std::string filename, bool read): filename(filename), read(read){
    if(read){
      in_stream.open(filename);

      if(!in_stream){
        in_stream.close();
        throw std::ios_base::failure("Error loading file");
      }

      determine_file_size();
      calulate_rem_file();
    }
    else{
      out_stream = std::ofstream(filename);

      if(!out_stream){
        out_stream.close();
        throw std::ios_base::failure("Error creating write stream");
      }
    }
  }
}
