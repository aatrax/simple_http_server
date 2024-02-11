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
	}
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(9999);
	saddr.sin_addr.s_addr=INADDR_ANY;
	if(bind(fd,(struct sockaddr*) & saddr,sizeof(saddr))==-1)
	{
		perror("bind");
		return -1;
	};
	if(listen(fd,128)==-1)
	{
		perror("listen");
		return -1;
	}; 
	std::cout<<"listen"<<std::endl;
	struct sockaddr_in caddr;
	socklen_t caddr_len=sizeof(caddr);
	int cfd=accept(fd,(struct sockaddr*)& caddr,&caddr_len);
	std::cout<<"accept"<<std::endl;
	char ip[32];
	std::cout<<"client ip: "<<inet_ntop(AF_INET,&caddr.sin_addr.s_addr,ip,sizeof(ip))<<"\n"<<"client port: "<<ntohs(caddr.sin_port)<<std::endl;
	char buffer[1024]="connection established";
	if(send(cfd,buffer,strlen(buffer)+1,0)==-1)
	{
		perror("server send");
		return -1;
	}
	while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int rcv_flg = recv(cfd, buffer, sizeof(buffer), 0);

        if (rcv_flg == -1)
        {
            perror("server recv");
            break; // 处理接收错误，跳出循环
        }
        else if (rcv_flg == 0)
        {
            std::cout << "Connection closed by client" << std::endl;
            break; // 客户端关闭连接，跳出循环
        }
        else
        {
            std::cout << "client message: " << buffer << std::endl;
        }
    }
	close(fd);
	close(cfd);
	return 0;
}













