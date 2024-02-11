#ifndef SERVER_H
#define SERVER_H

#include <unordered_map>
#include "thdpool.h"
#include <string>

#define PORT 80
#define BUFFSIZE 1024

class server
{
private:
    std::unordered_map<std::string,std::string> resolve_map;//网页路径和本地html文件路径的关系
    threadpool pool;
public:
    server() : pool(1,5){};
    //static std::string read_html(std::string &path); 
    void rtnhtml(std::string &req_path,int rtn_sock);
    void addpath(const std::string &req_path,const std::string &nat_path);//添加网页路径和本地html文件路径的关系
    void addfolder(const std::string &req_path,const std::string &nat_path);//添加网页路径和本地html文件的关系
    void startsvr();//启动服务器

};


#endif
