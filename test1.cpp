#include <iostream>
#include <fstream>
#include <dirent.h>

int main() {
    // 指定目录路径
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
            std::cout << entry->d_name << std::endl;
        }
    }

    // 关闭目录
    closedir(directory);

    return 0;
}
