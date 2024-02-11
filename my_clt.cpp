#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
int main()
{
	int fd =socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("socket");
		return -1;
	};
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(9999);
	inet_pton(AF_INET,"192.168.88.129",&saddr.sin_addr.s_addr);
	int con=connect(fd,(struct sockaddr *) &saddr,sizeof(saddr));
	if(con==-1)
	{
		perror("connect");
		return -1;
	};
	char buff[1024]="i love you";
	if(send(fd,buff,strlen(buff)+1,0)==-1)
	{
		perror("send");
		return -1;
	};
	int rcv_flg=recv(fd,buff,sizeof(buff),0);
	std::cout<<"server message : "<<buff<<std::endl;
	close(fd);

	sleep(100);
	return 0;
}






