#ifndef __cmd__
#define __cmd__

#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <filesystem>

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define PURPLE  "\033[35m"

namespace fs = std::filesystem;

void cd(std::string filename){
    const char *route = filename.c_str();
    if (!chdir(route)) std::cout<<YELLOW<<"DONE!";
    else std::cout<<PURPLE<<filename<<" not found directory";
}

void makeDirectory(std::string filename){
    try {
        if (!fs::exists(filename)){ 
            fs::create_directory(filename); 
            std::cout<<YELLOW<<"DONE!"; 
        }
        else std::cout<<PURPLE<<filename<<" File exist!!!";
    } catch (const fs::filesystem_error& e) {
        std::cout<<RED<<"ERROR during file creation "<<e.what();
    }
}

void removeFile(std::string filename){
    try {
        if (fs::exists(filename)){ 
            fs::remove_all(filename); 
            std::cout<<YELLOW<<"DONE!"; 
        }
        else std::cout<<PURPLE<<filename<<" doesn't exist";
    } catch (const fs::filesystem_error& e) {
        std::cout <<RED<<"ERROR during file deletion "<<e.what();
    }
}

void nvim(std::string filename){
    // const char* archive = filename;
    std::system(("nvim " + filename).c_str());
}

inline void category(std::string command, std::string content){
    if(command == "cd")cd(content);
    else if(command == "rm")removeFile(content);
    else if(command == "mkdir")makeDirectory(content);
    else nvim(content);

    std::cout<<RESET<<'\n';
}

#endif