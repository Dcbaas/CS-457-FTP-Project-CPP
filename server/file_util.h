#ifndef         FILE_UTIL_H
#define         FILE_UTIL_H

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace file_util{
  class file_obj{
    public:

      file_obj();
      /**
       * The constructor creates a file_obj. The flag determines if the 
       * file is written or read.
       *
       * Param: filename the name of the file.
       * Param: read sets weather the file is read or write.
       **/

      void update_objet(std::string filename, bool read);

      /**
       * Reads data from the file. By default. 1024 bytes are read
       * unless specified.
       *
       * Param: buffer a constant pointer to the buffer this file is 
       * being read to.
       * Param: num_bytes The number of bytes being read from the file
       * default is 1024;
       **/
      void read_file(char* buffer, size_t num_bytes = 1024);

      void write_file(char* buffer, size_t num_bytes = 1024);

      /**
       * Gets the size of the file
       *
       * Return: Size of the file.
       **/
      size_t get_filesize() const;

      /**
       * Gets how much is remaining in the filestream if the file is 
       * being read. 
       *
       * Returns: Size of file remaining.
       **/
      size_t get_rem_size() const;

      /**
       * Handles closing the file streams after the object is destroyed
       **/
      ~file_obj();
    private:
      //A bool to set read or write only
      bool read;

      std::string filename;

      FILE* file_descriptor;

      size_t filesize;

      //The size of the remaining file in readmode;
      size_t remaining_file;

      //Function to determine the size of the file.
      //Called in constructor.
      void determine_file_size();

      //Function to determine how much of the file remains
      //Called in every read call and constructor.
      void calulate_rem_file();
  };
}
#endif

