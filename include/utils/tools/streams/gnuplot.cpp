#include <iostream>
#include <vector>
#include <cmath>
#include "utils/include/utils/plots.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    utils::plot(std::vector<double>({0,1,2,3,4,6,20}),std::vector<double>({2,3,4,5,6,7,100}));
    utils::plot(std::vector<double>({0,1,2,3,4,6.5,3.2,5.4}));
    // create_and_print_r_tree();
    return 0;
}