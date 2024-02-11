#include "server.h"
#include <sstream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
void server::startsvr()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 创建套接字文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 设置套接字选项
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 绑定套接字到端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 开始监听
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    char buff[BUFFSIZE];//用来接受请求消息

    
    while(true)
    {
        std::cout<<"hello"<<std::endl;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        recv(new_socket,buff,BUFFSIZE,0);
        std::istringstream req_stm(buff);
        std::string req_mtd,req_pth,req_ptc;
        req_stm>>req_mtd>>req_pth>>req_ptc;
        std::cout<<req_pth<<" |@| ";
        rtnhtml(req_pth,new_socket);
        close(new_socket);
    }

}


//根据客户发送的请求头的路径返回对应的html文件
void server::rtnhtml(std::string &req_path,int rtn_sock)
{
    std::string html_response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
    auto it_path=resolve_map.find(req_path);
    std::ifstream html_file;
    if(it_path==resolve_map.end())
    {
        std::cout<<"invalid requested path "<<req_path<<std::endl;
        return;
    }
    else
    {
        html_file.open(it_path->second);
    }
    std::stringstream html_content;
    html_content << html_file.rdbuf();
    html_response+=html_content.str();
    send(rtn_sock , html_response.c_str(), html_response.length(), 0);
    return;
}

void server::addpath(const std::string &req_path,const std::string &nat_path)
{
    resolve_map[req_path]=nat_path;
    return;
}

void server::addfolder(const std::string &req_path,const std::string &nat_path)
{
    //const char* directoryPath = nat_path;

    // 打开目录
    DIR* directory = opendir(nat_path.c_str());
    if (directory == nullptr) {
        std::cerr << "Error opening directory." << std::endl;
        return ;
    }

    // 遍历目录中的文件
    struct dirent* entry;
    while ((entry = readdir(directory)) != nullptr) {
        if (entry->d_type == DT_REG) {
            // 如果是普通文件，输出文件名
            this->addpath(req_path + std::string(entry->d_name), nat_path+std::string(entry->d_name));        }
    }
}
