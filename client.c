#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){

  char *ip = "127.0.0.1";
  int port = 5566;

  

  int sockfd;
  struct sockaddr_in addr;
  char buffer[1024];
  socklen_t addr_size;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = inet_addr(ip);

  char stop[10]="exit";
   
  while(1){

  printf("\nEnter the string: ");
  char temp[1024];
  scanf("%s",temp);

  bzero(buffer, 1024);
  strcpy(buffer, temp);
  if(strcmp(temp,stop)==0)
  {
     sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
     break;
  }
  sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
  printf("\n[+]Data send: %s\n", buffer);

  bzero(buffer, 1024);
  addr_size = sizeof(addr);
  recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
  printf("[+]Data recieved: %s\n", buffer);
  }


  printf("\n[+]Client disconnected.\n\n");
  return 0;
}