#include "utils/container_overloads.h"
#include "utils/container_utils.h"
#include <vector>
#include <set>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    using namespace std;
    using namespace utils;

    cout << termcolor::bold << termcolor::underline << "Operating on a container" << termcolor::reset << endl;
    {
        vector<double> x1 = {3.4,2.5,2.6,4.6,3.5};
        vector<double> x2 = {2.3,3.2,1.8,3.6,2.5};
        vector<double> x3 = x1 + x2;
        vector<double> x4 = x3 + 10.0;
        vector<double> x5 = x4 * x2;
        vector<double> x6 = x5 / x1;
        cout << x6 << endl;
    }

    cout << termcolor::bold << termcolor::underline << "Operating on a container with scalars" << termcolor::reset << endl;
    {
        vector<double> x1 = {3.4,2.5,2.6,4.6,3.5};
        double x2 = 20.0;
        vector<double> x3 = x1 * x2;
        cout << x3 << endl;
    }

    cout << termcolor::bold << termcolor::underline << "Numerical attribution" << termcolor::reset << endl;
    {
        vector<double> x1 = {3.4,2.5,2.6,4.6,3.5};
        x1 += 20.0;
        vector<double> x2 = {2.3,3.2,1.8,3.6,2.5};
        x1 *= x2;
        cout << x1 << endl;
    }


    cout << termcolor::bold << termcolor::underline << "2D operations" << termcolor::reset << endl;
    {
        vector<vector<double>> x1 = {{3.4,2.5,2.6,4.6,3.5},{2.3,3.2,1.8,3.6,2.5}};
        x1 += 20.0;
        vector<vector<double>> x2 = {{3.4,2.5,2.6,4.6,3.5},{2.3,3.2,1.8,3.6,2.5}};
        x1 += x2;
        x1 *= x2;
        cout << x1 << endl;
    }

}
