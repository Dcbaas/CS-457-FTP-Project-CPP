#include "ftp_server.h"

int main(int argc, char** argv){
  ftp::ftp_server server;

  server.run();

  return 0;
}
