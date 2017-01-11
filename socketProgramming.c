#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){

  int sock, cli;
  struct sockaddr_in server, client;
  unsigned int len;
  int sent;
  char mesg[] = "Hello socket world programming!";

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("socket: ");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(&server.sin_zero, 8);

  len = sizeof(struct sockaddr_in);

  if( (bind(sock, (struct sockaddr *)&server, len)) == -1){
    perror("bind");
    exit(-1);
  }

  if((listen(sock, 5)) == -1){
    perror("Listen");
    exit(-1);
  }

  while(1){

    if((cli =  accept(sock, (struct sockaddr *)&client, &len)) ==  -1){
      perror("Accept");
      exit(-1);
    }

    sent = send(cli, mesg, strlen(mesg),0);
    printf("Sent %d bytes to client : %s\n", sent, inet_ntoa(client.sin_addr) );
    close(cli);

  }

  return 0;

}

/*
1. open two terminals in Linux
2. compile this as gcc helloServer.c -o helloServer in one of the terminal
3. execute in same terminal with ./helloServer
4. in second terminal run command telnet localhost 10000. 10000 is the port we communicate with
*/