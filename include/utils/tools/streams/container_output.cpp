#include "dump.hpp"

static void test_map() {

    std::cout << "-----------------------" << std::endl;
    std::cout << "          MAP          " << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::map<std::string, std::string> simple;

    simple["prenom"] = "Jeremie";
    simple["nom"] = "Taboada";
    simple["promo"] = "2016";

    std::cout << simple;

    // int map
    std::map<size_t, size_t> map;

    for (size_t i = 0; i <= 10; i++) {
        map[i] = i + 42;
    }

    std::cout << map;

}

static void test_vector(void) {

    std::cout << "-----------------------" << std::endl;
    std::cout << "        VECTOR         " << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::vector<char> vec;

    for (char i = 'a'; i <= 'z'; i++) {
        vec.push_back(i);
    }
    std::cout << vec;
}

static void test_list(void) {
    std::cout << "-----------------------" << std::endl;
    std::cout << "         LIST          " << std::endl;
    std::cout << "-----------------------" << std::endl;

    std::list<bool> list;

    for (size_t i = 0; i < 10; i++) {
        list.push_back(i % 2);
    }

    std::cout << list;
}

int main() {
    test_map();
    test_vector();
    test_list();
    return 0;
}