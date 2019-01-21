#include <iostream>
#include "file_util.h"

int main(int argc,char** argv){
  file_util::file_obj test_file{"test.txt", true};

  char* test_arr = new char[test_file.get_filesize()];

  test_file.read_file(test_arr, test_file.get_filesize());

  size_t result = test_file.get_rem_size();

  if(result == 0){
    std::cout << "Success" << std::endl;
  }

  delete[] test_arr;
}
