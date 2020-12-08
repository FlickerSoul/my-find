#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::string s = (std::string)"abcd";
    s.starts_with("a");
    // print("%i\n", s.starts_with("a"));
}