#include "find_utils.hh"

int main(int argc, char* argv[]) {
    auto argument_mapping = parse_arguments(argc, argv);
    if (argument_mapping == nullptr) {
        printf("invalid syntax\n");
        printf("myfind [-L] paths [expression]");
        return 1;
    }

    auto locations = (*argument_mapping)[LOCATION_FLAG];
    result_list_t result_list;
    for (auto & location: *locations) {
        auto new_result_list = find_helper(argument_mapping, location);
        result_list.insert(result_list.end(), new_result_list->begin(), new_result_list->end());
        free(new_result_list);
    }

    if (should_print(argument_mapping)) {
        print_helper(&result_list);
    }

    if (should_exec(argument_mapping)) {
        exec_helper(&result_list, (*(*argument_mapping)[EXEC_ARG_FLAG])[0]);
    }

    return 0;
}