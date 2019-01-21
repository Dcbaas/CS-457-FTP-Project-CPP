#include "file_util.h"

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>

#include <sys/stat.h>

namespace file_util{
  file_obj::file_obj(){}

  file_obj::file_obj(std::string filename, bool read):
   filename(filename), read(read){
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
    }
  }

  file_obj& file_obj::operator=(file_obj other){
    std::swap(this->read, other.read);
    std::swap(this->filename, other.filename);
    std::swap(this->in_stream, other.in_stream);
    std::swap(this->out_stream,other.out_stream);
    std::swap(this->filesize, other.filesize);
    std::swap(this->remaining_file, other.remaining_file);

    return *this;
  }

  void file_obj::update_objet(std::string filename, bool read){
    this->filename = filename;
    this->read = read;
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
    }
  }

  size_t file_obj::get_filesize() const{
    return filesize;
  }

  size_t file_obj::get_rem_size() const{ return remaining_file; }

  void  file_obj::read_file(char* buffer, size_t num_bytes){
    in_stream.read(buffer, num_bytes);
    calulate_rem_file();
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

