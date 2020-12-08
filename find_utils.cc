#include "find_utils.hh"


static auto default_name_regex = "*";

static std::vector<parser_t> parsers;

// parser guildline 
// if -1 is returned, parsing error 
// other wise a new counter is returned 


int parser_base(std::string flag, argument_map_t* const argument_map, int current_counter, int argc, char* const argv[], eliminator_t eliminator_func, string_processor processor) {
    printff("started %s parsing\n", flag.c_str());
    if (current_counter < argc && ((std::string) argv[current_counter]).compare(flag) == 0) {
        // if (argument_map->contains(flag)) {
        //     printff("duplicated symbol %s\n", flag.c_str());
        //     return -1;
        // }

        printff("matched flag %s\n", flag.c_str());

        current_counter += 1;
        std::string value = "";
        
        while (current_counter < argc && eliminator_func(argv[current_counter])) {
            value += (std::string) argv[current_counter++] + " ";
            printff("eliminated %s\n", argv[current_counter-1]);
        }

        value.erase(value.end() - 1);
        auto temp_vector = processor(value);

        if (temp_vector == nullptr) {
            printff("invalid processing for %s flag\n", flag.c_str());
            return -1;
        }

        argument_map->insert(std::pair<std::string, argument_map_value_t*>((std::string)(flag), temp_vector));

        printff("parsed %s with value %s\n", flag.c_str(), value.c_str());
        return current_counter;
    } 

    return current_counter;
}

bool default_eliminator(char* const cstr) {
    return !((std::string) cstr).starts_with("-");
}

argument_map_value_t* default_parser(std::string value) {
    if (value == "") {
        return nullptr;
    }

    argument_map_value_t* temp_vector = new argument_map_value_t();
    temp_vector->push_back(value);
    return temp_vector;
} 


// -name 
int parse_name(argument_map_t* const argument_map, int current_counter, int argc, char* const argv[]) {
    return parser_base(
        NAME_ARG_FLAG, 
        argument_map, 
        current_counter, 
        argc,
        argv,
        default_eliminator,
        default_parser
    );
}

// -mtime 
/**
 *  File's data was last modified n*24 hours ago. When  find  figures  out
 *  how  many  24-hour  periods  ago the file was last accessed, any
 *  fractional part is ignored, so to match -atime +1, a file has to
 *  have been accessed at least two days ago.
 */
int parse_mtime(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {
    return parser_base(
        MTIME_ARG_FLAG,
        argument_map, 
        current_counter, 
        argc,
        argv,
        default_eliminator,
        default_parser
    );
}

argument_map_value_t* type_processor(std::string value) {
    if (value == "") {
        return nullptr;
    }
    argument_map_value_t* result = new argument_map_value_t();

    std::stringstream ss(value);

    std::string str;
    while (getline(ss, str, ',')) {
        printff("parsed type %s\n", str.c_str());
        if (str.compare("b") && str.compare("c") && str.compare("d") && str.compare("p") && str.compare("f") && str.compare("l") && str.compare("s")) {
            return nullptr;
        }
        result->push_back(str);
    }

    return result;
}

// -type 
/**
 *  To  search  for  more  than one type at once, you can supply the
    combined list of type letters separated  by  a  comma  `,'  (GNU
    extension). "f,d"

    b      block (buffered) special

    c      character (unbuffered) special

    d      directory

    p      named pipe (FIFO)

    f      regular file

    l      symbolic link; this is never true if the -L option or the
            -follow  option is in effect, unless the symbolic link is
            broken.  If you want to search for symbolic links when -L
            is in effect, use -xtype.

    s      socket
 */
int parse_type(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {
    return parser_base(
        TYPE_ARG_FLAG,
        argument_map, 
        current_counter, 
        argc,
        argv,
        default_eliminator,
        type_processor
    );
}


bool exec_eliminator(char* const cstr) {
    return ((std::string) cstr).compare(";");
}


// -exec 
int parse_exec(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {
    return parser_base(
        EXEC_ARG_FLAG, 
        argument_map, 
        current_counter, 
        argc,
        argv,
        exec_eliminator,
        default_parser
    );
}

void post_parsing(argument_map_t* argumnt_map) {
    
}

// if the key is not in the mapping, it's evaluated false 
// otherwise it's true

argument_map_value_t* boolean_value_processor(std::string value) {
    return new argument_map_value_t;
}

// -print
int parse_print(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {
    return parser_base(
        PRINT_ARG_FLAG,
        argument_map, 
        current_counter, 
        argc,
        argv,
        default_eliminator,
        default_parser
    );
}

// -L
int parse_symbolic_link(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {
    return parser_base(
        SL_ARG_FLAG,
        argument_map, 
        current_counter, 
        argc,
        argv,
        default_eliminator,
        default_parser
    );
}

bool wild_card_match(char const *first, char const * second) { 
    // If we reach at the end of both strings, we are done 
    if (*first == '\0' && *second == '\0') 
        return true; 
  
    // Make sure that the characters after '*' are present 
    // in second string. This function assumes that the first 
    // string will not contain two consecutive '*' 
    if (*first == '*' && *(first+1) != '\0' && *second == '\0') {
        return false; 
    }
  
    // If the first string contains '?', or current characters 
    // of both strings match 
    if (*first == '?' || *first == *second) {
        return wild_card_match(first+1, second+1); 
    }
  
    // If there is *, then there are two possibilities 
    // a) We consider current character of second string 
    // b) We ignore current character of second string. 
    if (*first == '*') {
        return wild_card_match(first+1, second) || wild_card_match(first, second+1); 
    }
    return false; 
} 


argument_map_t* parse_arguments(int argc, char* argv[]) {
    // the first argument is the program name, ignored 
    printff("argc: %i\n", argc);

    if (argc < 2) {
        return nullptr;
    }

    auto objects = new argument_map_t;

    int counter = 1; 

    std::string argument;

    // find find all the specified locations
    while (counter < argc && !(argument = (std::string)(argv[counter])).starts_with("-")) {
        // std::cout << argument << std::endl;
        counter += 1;
    }

    // load all locations 
    std::vector<std::string>* search_locations = new std::vector<std::string>();
    for (int index = 1; index < counter; index++) {
        auto location_string = (std::string)argv[index];
        std::cout << "location " << location_string << std::endl;
        search_locations->push_back(location_string);
    }

    // if the location is not specified 
    if (search_locations->size() == 0) {
        return nullptr;
    }

    // parse arguments 
    parsers.push_back(parse_name);
    parsers.push_back(parse_mtime);
    parsers.push_back(parse_type);
    parsers.push_back(parse_exec);
    parsers.push_back(parse_print);
    parsers.push_back(parse_symbolic_link);

    while (counter < argc) {
        int temp_counter = counter;
        for (auto const & parser : parsers) {
            temp_counter = parser(objects, temp_counter, argc, argv);
            if (temp_counter == -1) {
                return nullptr;
            }
        }

        if (temp_counter == counter) {
            return nullptr;
        }
        counter = temp_counter;
    }
    
    return objects;
}


result_list_t* find_helper(argument_map_t* argument_map) {

}

void exec_helper(result_list_t* result_list) {

}

void print_helper(result_list_t* result_list_t) {

}
