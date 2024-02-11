#include "server.h"
#include "thdpool.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
int main()
{
    server mys;
    mys.addfolder("/","index/");
    mys.addfolder("/doc/","index/doc/");
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
