#ifndef __MOVE__
#define __MOVE__

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define PURPLE  "\033[35m"

namespace fs = std::filesystem;

inline void move(std::string input, std::string output) {
    try {
        if (fs::exists(input)){ 
            fs::rename(input, output);
            std::cout<<YELLOW<<"DONE!"; 
        }
        else std::cout<<PURPLE<<input<<" does not exist in the directory.";
    } catch (const fs::filesystem_error& e) {
        std::cout <<RED<<"ERROR: " << e.what();
    }
    std::cout<<RESET<<'\n';
}

#endif