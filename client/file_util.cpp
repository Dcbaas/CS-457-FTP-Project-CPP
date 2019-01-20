#include "file_util.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>

#include <sys/stat.h>

namespace file_util{
  file_obj::file_obj(std::string filename, bool read): filename(filename), read(read){
    if(read){
      in_stream.open(filename);

      if(!in_stream){
        in_stream.close();
        std::cout << "File failure" << std::endl;
      }

      determine_file_size();
      calulate_rem_file();
    }
    else{
      out_stream = std::ofstream(filename);

      if(!out_stream){
        out_stream.close();
        std::cout << "File failure" << std::endl << filesize << std::endl;
      }
      filesize = 0;
      remaining_file = 0;
    }
  }

  size_t file_obj::get_filesize() const{
    return filesize;
  }

  size_t file_obj::get_rem_size() const{ return remaining_file; }

  void  file_obj::read_file(char* buffer, size_t num_bytes){
    in_stream.read(buffer, num_bytes);
    std::cout << buffer << std::endl;
  }

  void file_obj::write_file(char*buffer, size_t num_bytes){
    out_stream.write(buffer,num_bytes);
  }

  file_obj::~file_obj(){
    if(read){
      in_stream.close();
    }
    else{
      out_stream.close();
    }
  }

  void file_obj::determine_file_size(){
    struct stat file_stat;
    stat(filename.c_str(), &file_stat);
    filesize = file_stat.st_size;
  }

  void file_obj::calulate_rem_file(){
    remaining_file = filesize - in_stream.tellg();
  }
}

