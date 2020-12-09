#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::string s = (std::string)"../find";
    // printf("original %s\n", s.c_str())
    // int pos = s.find("{}");
    // printf("pos: %i\n", pos);
    // s.replace(pos, 2, "bbbbb");
    printf("%s\n", s.c_str());
    auto file_path = fs::path(s);
    auto file_last_modified_time = fs::last_write_time(file_path);
    auto current_time = std::chrono::system_clock::now();
    // auto last = current_time - file_last_modified_time;
    // std::cout << last;
    const auto p0 = std::chrono::time_point<std::chrono::system_clock>{};
    const auto p1 = std::chrono::system_clock::now();

    // std::time_t epoch_time = std::chrono::system_clock::to_time_t(p0);
    // std::cout << "epoch: " << std::ctime(&epoch_time);
    // std::time_t today_time = std::chrono::system_clock::to_time_t(p1);
    // std::cout << "today: " << std::ctime(&today_time);

    // std::cout << "epoch since epoch: "
    //         << std::chrono::duration_cast<std::chrono::hours>(
    //             p0.time_since_epoch()).count() 
    //         << '\n';

 
    // std::cout << "hours since epoch: "
    //           << std::chrono::duration_cast<std::chrono::hours>(
    //                p1.time_since_epoch()).count() 
    //           << '\n';

    struct stat result;
    if(stat("./myfind.cc", &result)==0) {
        auto mod_time = result.st_mtime;
        printf("time %li: \n", mod_time);
    } 
    
    // if (fs::is_directory(file_path)) {
    //     printf("is dir\n");
    //     for (auto & p: fs::directory_iterator(s)) {
    //         std::cout << p.path() << std::endl;
    //     }
    // } else if (fs::is_regular_file(file_path)) {
    //     printf("is file\n");
    // }
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