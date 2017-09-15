#include <boost/cstdint.hpp>
#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    std::cout << termcolor::on_yellow << termcolor::bold << termcolor::underline << "Types for integers with number of bits" << termcolor::reset << std::endl;
    {
        std::cout << termcolor::bold << termcolor::underline << "boost::int8_t and boost::uint64_t carry the exact memory size in their names" << termcolor::reset << std::endl;
        boost::int8_t i8 = 1;
        std::cout << "sizeof(i8): " << sizeof(i8) << '\n';

        #ifndef BOOST_NO_INT64_T
        boost::uint64_t ui64 = 1;
        std::cout << "sizeof(ui64): " << sizeof(ui64) << '\n';
        #endif

        std::cout << termcolor::bold << termcolor::underline << "boost::int_least8_t and boost::uint_least32_t contain at least as many bits as their names say" << termcolor::reset << std::endl;

        boost::int_least8_t il8 = 1;
        std::cout << "sizeof(il8): " << sizeof(il8) << '\n';

        boost::uint_least32_t uil32 = 1;
        std::cout << "sizeof(uil32): " << sizeof(uil32) << '\n';

        std::cout << termcolor::bold << termcolor::underline << "boost::int_fast8_t and boost::uint_fast16_t also have a minimum size. Their actual size is set to a value that guarantees the best performance" << termcolor::reset << std::endl;

        boost::int_fast8_t if8 = 1;
        std::cout << "sizeof(if8): " << sizeof(if8) << '\n';

        boost::uint_fast16_t uif16 = 1;
        std::cout << "sizeof(uif16): " << sizeof(uif16) << '\n';

        std::cout << termcolor::bold << termcolor::underline << "boost::intmax_t and boost::uintmax_t, for the maximum width integer types available on a platform" << termcolor::reset << std::endl;

        boost::intmax_t imax = 1;
        std::cout << "sizeof(imax): " << sizeof(imax) << '\n';

        std::cout << "sizeof(UINT8_C(1)): " << sizeof(UINT8_C(1)) << '\n';

        #ifndef BOOST_NO_INT64_T
        std::cout << "sizeof(INT64_C(1)): " << sizeof(INT64_C(1)) << '\n';
        #endif
    }

}
