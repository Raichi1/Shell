#ifndef __ECHO__
#define __ECHO__

#include <string>

inline void echo(std::string var){
    const char* env = std::getenv((var.c_str()));
    if(env)std::cout<<env;
    else std::cout<<"~";
    std::cout<<'\n';
}

#endif