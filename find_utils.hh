#ifndef __FIND_UTILS
#define __FIND_UTILS

#include <filesystem>
#include <map>
#include <stdbool.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <functional>
#include <stdarg.h>
#include <sstream>
#include <stdlib.h>

namespace fs = std::filesystem;

typedef std::vector<std::string> argument_map_value_t;
typedef std::map<std::string, argument_map_value_t*> argument_map_t;
typedef int _parser_t(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]);
typedef std::function<_parser_t> parser_t;
typedef std::vector<std::string> result_list_t;
typedef bool _eliminator_t(char* const cstr);
typedef std::function<_eliminator_t> eliminator_t;
typedef argument_map_value_t* _string_processor(std::string const);
typedef std::function<_string_processor> string_processor;
typedef bool _matcher_t(argument_map_t* const argument_map_ptr, fs::path const target_path);
typedef std::function<_matcher_t> matcher_t;


// parser strings 
static auto LOCATION_FLAG = "location";
static auto NAME_ARG_FLAG = "-name";
static auto MTIME_ARG_FLAG = "-mtime";
static auto TYPE_ARG_FLAG = "-type";
static auto EXEC_ARG_FLAG = "-exec";
static auto PRINT_ARG_FLAG = "-print";
static auto SL_ARG_FLAG = "-L";
static bool _DEBUG = true;

static std::vector<parser_t> parsers;
static std::vector<matcher_t> matchers;


static std::map<std::string, std::function<bool (const fs::path& )>> validation_mapping = {
    {"b", static_cast<bool(*) (const fs::path& )>(fs::is_block_file)},
    {"c", static_cast<bool(*) (const fs::path& )>(fs::is_character_file)},
    {"d", static_cast<bool(*) (const fs::path& )>(fs::is_directory)},
    {"p", static_cast<bool(*) (const fs::path& )>(fs::is_fifo)},
    {"f", static_cast<bool(*) (const fs::path& )>(fs::is_regular_file)},
    {"l", static_cast<bool(*) (const fs::path& )>(fs::is_symlink)},
    {"s", static_cast<bool(*) (const fs::path& )>(fs::is_socket)}
};

// parsers 
argument_map_t* parse_arguments(int argc, char* argv[]);
result_list_t* find_helper(argument_map_t* argument_map, fs::path path);
bool should_print(argument_map_t* const argument_map_ptr);
bool should_exec(argument_map_t* const argument_map_ptr) ;
void exec_helper(result_list_t* result_list, std::string exec_string);
void print_helper(result_list_t* result_list_t);

static void printff(const char* format, ...) {
    if (_DEBUG) {
        va_list args;
        va_start (args, format);
        vprintf (format, args);
        va_end (args);
    }
}

#endif
