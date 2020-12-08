#include <filesystem>
#include <map>
#include <stdbool.h>
#include <map>
#include <string.h>
#include <vector>
#include <iostream>
#include <functional>

typedef std::vector<std::string> argument_map_value_t;
typedef std::map<std::string, argument_map_value_t*> argument_map_t;
typedef int _parser_t(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]);
typedef std::function<_parser_t> parser_t;
typedef std::vector<std::string> result_list_t;

// parsers 
argument_map_t* parse_arguments(int argc, char* argv[]);

