//
// Created by Alan de Freitas on 20/11/2017.
//

#ifndef WPP_GRAMMAR_H
#define WPP_GRAMMAR_H

#include "utils/container/php_utils.h"
#include "datatype_alias.h"
//#include "blueprint.h"

namespace wpp {

    namespace db {

        class base_grammar {
            public:
                using self_t = base_grammar;
                /**
                 * The grammar table prefix.
                 *
                 * @var string
                 */
            protected:
                string _table_prefix = "";

                /**
                 * Wrap an array of values.
                 *
                 * @param  array  _values
                 * @return array
                 */
            public:
                template<typename array>
                array wrap_array(array _values) {
                    for (auto &value : _values) {
                        value = this->wrap(value);
                    }
                    return _values;
                }

                /**
                 * Wrap a table in keyword identifiers.
                 *
                 * @param  string|string  _table
                 * @return string
                 */
            public:

                string wrap_table(string _table) {
                    return this->wrap(this->_table_prefix + _table, true);
                }

                /**
                 * Wrap a value in keyword identifiers.
                 *
                 * @param  string|string  _value
                 * @param  bool    _prefix_alias
                 * @return string
                 */
            public:

                string wrap(string _value, bool _prefix_alias = false) {
                    // If the value being wrapped has a column alias we will need to separate out
                    // the pieces so we can wrap each of the segments of the string on it
                    // own, and then joins them both back together with the "as" connector.
                    if (utils::strtolower(_value).find(" as ") != string::npos) {
                        return this->wrap_aliased_value(_value, _prefix_alias);
                    }

                    return this->wrap_segments(utils::explode(".", _value));
                }

                /**
                 * Wrap a value that has an alias.
                 *
                 * @param  string  _value
                 * @param  bool  _prefix_alias
                 * @return string
                 */
            protected:

                string wrap_aliased_value(string _value, bool _prefix_alias = false) {
                    vector<string> _segments = utils::preg_split(std::regex("/\\s+as\\s+/i"), _value);

                    // If we are wrapping a table we need to prefix the alias with the table prefix
                    // as well in order to generate proper syntax. If this is a column of course
                    // no prefix is necessary. The condition will be true when from wrap_table.
                    if (_prefix_alias) {
                        _segments[1] = this->_table_prefix + _segments[1];
                    }

                    return this->wrap(_segments[0]) + " as " + this->wrap_value(_segments[1]);
                }

                /**
                 * Wrap the given value segments.
                 *
                 * @param  array  _segments
                 * @return string
                 */
            protected:

                string wrap_segments(vector<string> _segments) {
                    for (int key = 0; key < _segments.size(); ++key) {
                        auto &_segment = _segments[key];
                        if (key == 0 && !_segments.empty()) {
                            _segment = this->wrap_table(_segment);
                        } else {
                            _segment = this->wrap_value(_segment);
                        }
                    }
                    return utils::implode(".", _segments);
                }

                /**
                 * Wrap a single string in keyword identifiers.
                 *
                 * @param  string  _value
                 * @return string
                 */
            protected:

                string wrap_value(string _value) {
                    if (_value != "*") {
                        return "\"" + utils::str_replace("\"", "\"\"", _value) + "\"";
                    }

                    return _value;
                }

                /**
                 * Convert an array of column names into a delimited string.
                 *
                 * @param  array   _columns
                 * @return string
                 */
            public:
                string columnize(vector<string> _columns) {
                    for (int key = 0; key < _columns.size(); ++key) {
                        auto &_column = _columns[key];
                        _column = this->wrap(_column);
                    }
                    return utils::implode(", ", _columns);
                }

                /**
                 * Create query parameter place-holders for an array.
                 *
                 * @param  array   _values
                 * @return string
                 */
            public:

                string parameterize(vector<string> _values) {
                    for (int key = 0; key < _values.size(); ++key) {
                        auto &_value = _values[key];
                        _value = this->parameter(_value);
                    }
                    return utils::implode(", ", _values);
                }

                string parameterize(vector<pair<string,string>> _values) {
                    vector<string> _value_strings;
                    for (pair<string,string> &item : _values) {
                        _value_strings.emplace_back(this->parameter(item.second));
                    }
                    return utils::implode(", ", _value_strings);
                }

                /**
                 * Get the appropriate query parameter place-holder for a value.
                 *
                 * @param  mixed   _value
                 * @return string
                 */
            public:

                string parameter(string _value) {
                    return "?";
                }

                /**
                 * Determine if the given value is a raw string.
                 *
                 * @param  mixed  _value
                 * @return bool
                 */
            public:

                bool is_string(string _value) {
                    return true;
                }

                /**
                 * Get the value of a raw string.
                 *
                 * @param  string  _string
                 * @return string
                 */
            public:

                string get_value(string _string) {
                    return _string;
                }

                /**
                 * Get the format for database stored dates.
                 *
                 * @return string
                 */
            public:

                string get_date_format() {
                    return "Y-m-d H:i:s";
                }

                /**
                 * Get the grammar's table prefix.
                 *
                 * @return string
                 */
            public:

                string get_table_prefix() {
                    return this->_table_prefix;
                }

                /**
                 * Set the grammar's table prefix.
                 *
                 * @param  string  _prefix
                 * @return _this
                 */
            public:

                self_t& set_table_prefix(string _prefix) {
                    this->_table_prefix = _prefix;
                    return *this;
                }
        };


    }
}

#endif //WPP_GRAMMAR_H
