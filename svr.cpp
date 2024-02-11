#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 80
#define BUFFSIZE 1024

std::string read_html(const std::string &path)
{
    std::ifstream rdhtml;
    rdhtml.open(path);
    std::string rtn;
    rdhtml>>rtn;
    rdhtml.close();
    return rtn;
}
void *thread_handle(void* arg)
{
	int handle_fd= *((int *)arg);
	std::string html_response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
	//resolve the request
	
    //std::ifstream html_file("index.html");
    //std::stringstream html_content;
    //html_content << html_file.rdbuf();
    html_response += read_html("index.html");
    send(handle_fd , html_response.c_str(), html_response.length(), 0);
    close(handle_fd);

    pthread_exit(NULL);
}	

void sendico(int sock_ico)
{
    std::ifstream icofile("favicon.ico", std::ios::binary);
    std::string fileContent((std::istreambuf_iterator<char>(icofile)), std::istreambuf_iterator<char>());
    icofile.close();
    std::string httpResponse = "HTTP/1.1 200 OK\nContent-Type: image/x-icon\n\n";
    send(sock_ico, httpResponse.c_str(), httpResponse.size(), 0);
    send(sock_ico, fileContent.c_str(), fileContent.size(), 0);
}

void norm_rsp(int norm_sock)
{

}
int main() {
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

    char buffer[BUFFSIZE] = {0};

    //char* req_msg=req_msg_s.c_str();
    // 接受连接并返回HTML文件
    while(true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
		recv(new_socket,buffer,BUFFSIZE,0);
		//std::cout<<buffer<<std::endl;
		//create a new thread to handle request
		//pthread_t tid;
        //if (pthread_create(&tid, NULL, handle_client, &new_socket) != 0) {
        //    perror("pthread_create");
        //   close(new_socket);
     //   }
   // }
		std::istringstream request(buffer);
        std::string method, path, protocol;
        request >> method >> path >> protocol;
		std::cout<<path<<std::endl;
        if(path=="/favicon.ico")
            sendico(new_socket);
        else
        {
            std::string html_response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
            std::ifstream html_file("index.html");
            std::stringstream html_content;
            html_content << html_file.rdbuf();
            html_response+=html_content.str();
            send(new_socket , html_response.c_str(), html_response.length(), 0);
        }
        close(new_socket);
    }
    return 0;
}

