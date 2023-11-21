#ifndef __dirs__
#define __dirs__

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>

#define f first
#define s second
#define RESET       "\033[0m"  
#define DIRECTORY   "\033[32m"            //GREEN   
#define ARCHIVE     "\033[38;5;208m"      //ORANGE

inline void listShow(){
    DIR* dir = opendir(".");
    if (dir != nullptr) {
        struct dirent* entrada;
        while ((entrada = readdir(dir)) != nullptr) {
            std::string arch = entrada->d_name;
            std::string route = "./" + arch;

            struct stat infoArchivo;
            if (stat(route.c_str(), &infoArchivo) == 0) {
                if (S_ISDIR(infoArchivo.st_mode)) {
                    std::cout<<DIRECTORY<<arch;
                } else {
                    std::cout<<ARCHIVE<<arch;
                }
                std::cout<<"   ";
            }
        }
        closedir(dir);
    }
    std::cout<<RESET<<'\n';
}

#endif