#include "utils/container_overloads.h"
#include "utils/container_utils.h"
#include <vector>
#include <set>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    using namespace std;
    using namespace utils;

    cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Container Generators" << termcolor::reset << endl;
    {
        cout << termcolor::bold << termcolor::underline << "Eye" << termcolor::reset << endl;
        cout << "eye(3): " << eye(3) << endl;
        cout << "eye<int>(3): " << eye<int>(3) << endl;
        cout << termcolor::bold << termcolor::underline << "Linspace" << termcolor::reset << endl;
        cout << "linspace(3.0,10.0,11.0): " << linspace(3.0, 10.0, 11.0) << endl;
        cout << "linspace<int>(3,10,11): " << linspace<int>(3, 10, 11) << endl;
        cout << termcolor::bold << termcolor::underline << "Rand" << termcolor::reset << endl;
        cout << "rand(10): " << rand(10) << endl;
        cout << "rand(4,4): " << rand(4, 4) << endl;
        cout << "rand(2,3,2): " << rand(2, 3, 2) << endl;
        cout << termcolor::bold << termcolor::underline << "Zeros" << termcolor::reset << endl;
        cout << "zeros(3): " << zeros(3) << endl;
        cout << "zeros(3,3): " << zeros(3, 3) << endl;
        cout << termcolor::bold << termcolor::underline << "Ones" << termcolor::reset << endl;
        cout << "ones(3): " << ones(3) << endl;
        cout << "ones(3,3): " << ones(3, 3) << endl;
        cout << termcolor::bold << termcolor::underline << "Perm" << termcolor::reset << endl;
        cout << "perm(10): " << perm(10) << endl;
        cout << "perm(20): " << perm(20) << endl;
        cout << "perm(30,3): " << perm(30, 3) << endl;
    }

    cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Container Methods" << termcolor::reset << endl;
    {
        cout << termcolor::bold << termcolor::underline << "Random numbers" << termcolor::reset << endl;
        vector<double> a = rand(10);
        disp(a);
        cout << termcolor::bold << termcolor::underline << "Statistics" << termcolor::reset << endl;
        cout << "mean(a): " << mean(a) << endl;
        cout << "stdev(a): " << stdev(a) << endl;
        cout << "stdev(a,mean(a)): " << stdev(a,mean(a)) << endl;
        cout << termcolor::bold << termcolor::underline << "Math" << termcolor::reset << endl;
        cout << "pow(a, 3.2): " << pow(a, 3.2) << endl;
        cout << "prod(a): " << prod(a) << endl;
        cout << "sum(a): " << sum(a) << endl;
    }

    cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Operation between containers" << termcolor::reset << endl;
    {
        cout << termcolor::bold << termcolor::underline << "Random numbers" << termcolor::reset << endl;
        vector<double> a = rand(10);
        cout << "a: " << a << endl;
        vector<double> b = rand(10);
        cout << "b: " << b << endl;
        vector<int> c = ones(20);
        cout << "c: " << c << endl;
        vector<vector<double>> d = rand(1,2);
        cout << "d: " << d << endl;
        vector<vector<double>> e = rand(3,3);
        cout << "e: " << e << endl;
        cout << termcolor::bold << termcolor::underline << "Operations" << termcolor::reset << endl;
        cout << "cat(a,b): " << cat(a, b) << endl;
        cout << "copyshape(c,a): " << copyshape(c,a) << endl;
        cout << "copyshape(e,d): " << copyshape(e,d) << endl;
        cout << "inner(a,b): " << inner(a,b) << endl;

    }

}
