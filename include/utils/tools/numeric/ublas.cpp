#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_sparse.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    std::cout << termcolor::bold << termcolor::underline << "Vector" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        vector<double> v(3);
        for (unsigned i = 0; i < v.size(); ++i) {
            v(i) = i;
        }
        std::cout << v << std::endl;
        v -= v * 12;
        std::cout << v << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Unit Vector" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        for (int i = 0; i < 3; ++i) {
            unit_vector<double> v(3, i);
            std::cout << v << std::endl;
        }
    }

    std::cout << termcolor::bold << termcolor::underline << "Zero Vector" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        zero_vector<double> v(3);
        std::cout << v << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Scalar Vector" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        scalar_vector<double> v(3);
        std::cout << v << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Mapped Vector" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        mapped_vector<double> v(3, 3);
        for (unsigned i = 0; i < v.size(); ++i) {
            v(i) = i;
        }
        std::cout << v << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Compressed Vector" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        compressed_vector<double> v(3, 3);
        for (unsigned i = 0; i < v.size(); ++i) {
            v(i) = i;
        }
        std::cout << v << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Coordinate Vector" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        coordinate_vector<double> v(3, 3);
        for (unsigned i = 0; i < v.size(); ++i) {
            v(i) = i;
        }
        std::cout << v << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Vector Range" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        vector<double> v(3);
        vector_range<vector<double> > vr(v, range(0, 3));
        for (unsigned i = 0; i < vr.size(); ++i) {
            vr(i) = i;
        }
        std::cout << vr << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Generic Projections" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        vector<double> v(3);
        for (int i = 0; i < 3; ++i) {
            project(v, range(0, 3))(i) = i;
        }
        std::cout << project(v, range(0, 3)) << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Vector Slice" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        vector<double> v (3);
        vector_slice<vector<double> > vs (v, slice (0, 1, 3));
        for (unsigned i = 0; i < vs.size (); ++ i)
            vs (i) = i;
        std::cout << vs << std::endl;
    }

    std::cout << termcolor::bold << termcolor::underline << "Generic Projections" << termcolor::reset << std::endl;
    {
        using namespace boost::numeric::ublas;
        vector<double> v (3);
        for (int i = 0; i < 3; ++ i)
            project (v, slice (0, 1, 3)) (i) = i;
        std::cout << project (v, slice (0, 1, 3)) << std::endl;
    }

}
