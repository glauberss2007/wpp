#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "utils/progress_bar.h"
#include "utils/container_overloads.h"
#include "utils/container_utils.h"

int main() {
    int goal = 3000000;
    int progress_resolution = 20;

    std::vector<double> v = utils::rand(goal);
    std::vector<double> v2(goal);

    utils::progress_bar p(goal,progress_resolution);
    std::cout << p.bar() << std::endl;
    for (int i = 0; i < goal; ++i) {
        std::cout << p.star(i);
        // do something that takes time here
        v2[i] = std::pow(v[i],2);
    }
    std::cout << std::endl;
    double sum = 0;
    for (auto &&item : v2) {
        sum+=item;
    }
    std::cout << sum << std::endl;
    return 0;
}
