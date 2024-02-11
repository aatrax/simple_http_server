#include "server.h"
#include "thdpool.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
int main()
{
    server mys;
    const char* directoryPath = "index/";

    // 打开目录
    DIR* directory = opendir(directoryPath);
    if (directory == nullptr) {
        std::cerr << "Error opening directory." << std::endl;
        return 1;
    }

    // 遍历目录中的文件
    struct dirent* entry;
    while ((entry = readdir(directory)) != nullptr) {
        if (entry->d_type == DT_REG) {
            // 如果是普通文件，输出文件名
            mys.addpath("/" + std::string(entry->d_name), "index/"+std::string(entry->d_name));        }
    }

    // 关闭目录
    closedir(directory);

    const char* directoryPath1 = "index/doc/";

    // 打开目录
    directory = opendir(directoryPath1);
    if (directory == nullptr) {
        std::cerr << "Error opening directory." << std::endl;
        return 1;
    }

    // 遍历目录中的文件
    //struct dirent* entry;
    while ((entry = readdir(directory)) != nullptr) {
        if (entry->d_type == DT_REG) {
            // 如果是普通文件，输出文件名
            mys.addpath("/doc/" + std::string(entry->d_name), "index/doc/" + std::string(entry->d_name));
        }
    }

    // 关闭目录
    closedir(directory);
    mys.addpath("/","index/index.html");
    mys.addpath("/favicon.ico","favicon.ico");
    // mys.addpath("/beautiful.jpg","beautiful.jpg");
	
    // mys.addpath("/beauty.jpg","beauty.jpg");
    // mys.addpath("/blackbird.gif","blackbird.gif");
    // mys.addpath("/bluesky.jpg","bluesky.jpg");
    // mys.addpath("/darksky.jpg","darksky.jpg");
    // mys.addpath("/gift.html","gift.html");
    // mys.addpath("/goodboy.gif","goodboy.gif");
	mys.startsvr();
    return 0;
}
