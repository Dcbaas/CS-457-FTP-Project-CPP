#include "file_util.h"

#include <exception>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>

namespace file_util{
  file_obj::file_obj(){}

  void file_obj::update_objet(std::string filename, bool read){
    this->filename = filename;

    if(read){
      file_descriptor = fopen(filename.c_str(), "r");

      determine_file_size(); 
      calulate_rem_file();
    }
    else{
      file_descriptor = fopen(filename.c_str(), "w");
    }

    if(!file_descriptor){
      printf("File loading failed\n");
      fclose(file_descriptor);
      return;
    }

  }

  size_t file_obj::get_filesize() const{
    return filesize;
  }

  size_t file_obj::get_rem_size() const{ return remaining_file; }

  void  file_obj::read_file(char* buffer, size_t num_bytes){
    fread(buffer, num_bytes, sizeof(char), file_descriptor);
    
    calulate_rem_file();
  }


  void file_obj::determine_file_size(){
    struct stat file_stat;
    stat(filename.c_str(), &file_stat);
    filesize = file_stat.st_size;
  }

  void file_obj::calulate_rem_file(){
    remaining_file = filesize - ftell(file_descriptor);
  }

  file_obj::~file_obj(){
    fclose(file_descriptor);
  }
}

