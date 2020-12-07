#include <filesystem>
#include <iostream>
#include <stdio.h>

namespace fs = std::filesystem;

int main() {
    auto path = fs::path(".");
    printf("%s\n", path.c_str());
}