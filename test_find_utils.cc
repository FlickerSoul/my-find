#include "find_utils.hh"

int main(int argc, char* argv[]) {
    auto map = parse_arguments(argc, argv);
    if (map == nullptr) {
        printf("invalid parsing\n");
    } else {
        for (auto const& pair : *map) {
            printf("key: %s, ", pair.first.c_str());
            if (pair.second->size() == 0) {
                printf("value: true\n");
            } else {
                printf("value: ");
                for (auto const & value : *pair.second) {
                    printf("%s ", value.c_str());
                }
                printf("\n");
            }
        }
        printf("========\n");
        auto loc = (*(map->find(LOCATION_FLAG)->second))[0];
        auto results = find_helper(map, loc);

        printf("\n======== result ========\n");
        for (auto & path: *results) {
            std::cout << path << std::endl;
        }
    }
}