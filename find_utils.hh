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

typedef std::vector<std::string> argument_map_value_t;
typedef std::map<std::string, argument_map_value_t*> argument_map_t;
typedef int _parser_t(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]);
typedef std::function<_parser_t> parser_t;
typedef std::vector<std::string> result_list_t;
typedef bool _eliminator_t(char* const cstr);
typedef std::function<_eliminator_t> eliminator_t;
typedef argument_map_value_t* _string_processor(std::string const);
typedef std::function<_string_processor> string_processor;


// parser strings 
static auto NAME_ARG_FLAG = "-name";
static auto MTIME_ARG_FLAG = "-mtime";
static auto TYPE_ARG_FLAG = "-type";
static auto EXEC_ARG_FLAG = "-exec";
static auto PRINT_ARG_FLAG = "-print";
static auto SL_ARG_FLAG = "-L";
static bool _DEBUG = true;

// parsers 
argument_map_t* parse_arguments(int argc, char* argv[]);

static void printff(const char* format, ...) {
    if (_DEBUG) {
        va_list args;
        va_start (args, format);
        vprintf (format, args);
        va_end (args);
    }
}

#endif
