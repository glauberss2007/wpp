#include <vector>
#include <iostream>
#include "utils/include/utils/cout_plot.h"

int main() {
    // the default constructor generates some values for x and y
    utils::plot p;
    std::cout << p << std::endl;
    return 0;
}
