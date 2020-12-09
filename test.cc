#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::string s = (std::string)"../{}find";
    printf("original %s\n", s.c_str());
    int pos = s.find("{}");
    printf("pos: %i\n", pos);
    s.replace(pos, 2, "bbbbb");
    printf("%s\n", s.c_str());
    auto file_path = fs::path(s);
    if (fs::is_directory(file_path)) {
        printf("is dir\n");
        for (auto & p: fs::directory_iterator(s)) {
            std::cout << p.path() << std::endl;
        }
    } else if (fs::is_regular_file(file_path)) {
        printf("is file\n");
    }
    auto entry = fs::directory_entry(s);
    auto status = entry.status().type();

    
    // s.starts_with("a");
    // std::string str ("This is an example sentence.");
    // std::cout << str << '\n';
    //                                         // "This is an example sentence."
    // str.erase (str.end() - 1);                        //            ^^^^^^^^
    // std::cout << str << '\n';
    // print("%i\n", s.starts_with("a"));
}