#include <vector>
#include <iostream>
#include "utils/pretty_table/pretty_table.h"

int main() {
    utils::table t;
    // add data
    t.add_row({"", "Sex", "Age"});
    t.add("Moses");
    t.add("Male");
    t.add("4456");
    t.end_of_row();
    t.add_row({"Jesus", "Male", "2016"}).add_row({"Debora", "Female", "3001"});
    t.add_row({{"Moses", "Male",   "4556"},
               {"Maria", "F__a_e", "323"}});
    std::vector<std::string> strs = {"Bob", "Male", "25"};
    t.add_row(strs);

    std::cout << t << std::endl;

    // settings
    t.min_width(10).text_color(utils::color::none)
     .text_background(utils::color::none)
     .bold(false)
     .underline(false)
     .corner_separator('+')
     .horizontal_separator('-')
     .vertical_separator('|')
     .border_bold(true)
     .border_underline(false)
     .border_color(utils::color::black)
     .border_background(utils::color::grey)
     .padding(1)
     .border_size(2)
     .border_height(1);

    t[0].underline(false).bold(true).text_background(utils::color::green);

    t[0][0].text_background(utils::color::grey);

    for (int i = 0; i < t.row_count(); ++i) {
        t[i][0].bold(true);
    }

    int oldest_pos = 4;
    t[oldest_pos][2].text_color(utils::color::red);
    int youngest_pos = 6;
    t[youngest_pos][2].text_color(utils::color::green).bold(true);
    int data_error_pos = 5;
    t[data_error_pos][1].text_background(utils::color::red).text_color(utils::color::yellow).underline(true);

    t.set_alignment(0, utils::alignment::right);
    t.set_alignment(1, utils::alignment::center);
    t.set_alignment(2, utils::alignment::center);

    // print
    std::cout << t << std::endl;

    return 0;
}
