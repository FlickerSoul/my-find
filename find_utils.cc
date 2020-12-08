#include "find_utils.hh"


static auto default_name_regex = "*";

static std::vector<parser_t> parsers;



// parser guildline 
// if -1 is returned, parsing error 
// other wise a new counter is returned 


// -name 
int parse_name(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {
    if (argument_map->contains("-name")) {
        return -1;
    }

    if (((std::string) argv[current_counter]).compare("-name")) {
        current_counter += 1;
        if (current_counter < argc) {
            argument_map_value_t* temp_vector = new argument_map_value_t();
            temp_vector->push_back((std::string) argv[current_counter]);
            argument_map->insert(std::pair<std::string, argument_map_value_t*>((std::string)("name"), temp_vector));

            return current_counter + 1;
        } else {
            return -1;
        }
    } else {
        return current_counter;
    }
}

// -mtime 
int parse_mtime(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {
    
}

// -type 
int parse_type(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {

}


// -exec 
int parse_exec(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {

}

void post_parsing(argument_map_t* argumnt_map) {
    
}

// if the key is not in the mapping or the value of the key is nullptr, it's evaluated false 
// otherwise it's true

// -print
int parse_print(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {

}

// -L
int parse_symbolic_link(argument_map_t* argument_map, int current_counter, int argc, char* const argv[]) {

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
    if (argc < 2) {
        return nullptr;
    }

    auto objects = new argument_map_t;

    int counter = 1; 

    std::string argument;

    // find find all the specified locations
    while (counter < argc && !(argument = (std::string)(argv[counter++])).starts_with("-")) {
        // std::cout << argument << std::endl;
    }

    // load all locations 
    std::vector<std::string>* search_locations = new std::vector<std::string>();
    for (int index = 1; index < counter; index++) {
        search_locations->push_back((std::string)argv[index]);
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

        // assert(counter != temp_counter); 
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
