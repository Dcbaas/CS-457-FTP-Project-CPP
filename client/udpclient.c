#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char** argv){
  int sockfd = socket(AF_INET,SOCK_DGRAM,0);
  if(sockfd < 0){
    printf("There was an error creating the socket\n");
    return 1;
  }

  struct sockaddr_in serveraddr;
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_port=htons(8008);
  serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

  char line[1030];
  line[0] = 'n';
  line[1] = 'm';
  line[2] = 'l';
  line[3] = 5;
  line[4] = 0;
  line[5] = 26;

  FILE* test = fopen("test.txt", "r");

  fread(line+6, 25, sizeof(char), test);
  
 // sendto(sockfd,line,strlen(line)+1,0,
 //     (struct sockaddr*)&serveraddr,sizeof(serveraddr));
  close(sockfd);
  return 0;
}
