#include <iostream>
#include "file_util.h"

int main(int argc, char** argv){

  file_util::file_obj test_file{"test.txt", true};

  char* test_buffer = new char[1000];

  test_file.read_file(test_buffer, test_file.get_filesize());

  std::cout << test_buffer << std::endl;

  delete[] test_buffer;
  return 0;
}
