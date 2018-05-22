//
// Created by Alan de Freitas on 20/11/2017.
//

#ifndef WPP_QUERY_GRAMMAR_HPP
#define WPP_QUERY_GRAMMAR_HPP

namespace wpp {
    namespace db {
        string query_grammar::compile_select(query_builder& _query) {
            // If the query does not have any columns set, we'll set the columns to the
            // * character to just get all of the columns from the database. Then we
            // can build the query and concatenate all the pieces together as one.
            vector<string> _original = _query._columns;

            if (is_null(_query->columns)) {
                _query->columns = {'*'};
            }

            // To compile the query, we'll spin through each component of the query and
            // see if that component exists. If it does we'll just call the compiler
            // function for the component which is responsible for making the SQL.
            _sql = trim(_this->concatenate(
                    _this->compile_components(_query))
            );

            _query->columns = _original;

            return _sql;
        }

        vector<string> query_grammar::compile_components(query_builder& _query) {
            vector<string> _sql = {};

            for (auto& _component: this->_select_components) {
                // To compile the query, we'll spin through each component of the query and
                // see if that component exists. If it does we'll just call the compiler
                // function for the component which is responsible for making the SQL.
                if (!is_null(_query->_component)) {
                    _method = 'compile'.ucfirst(_component);

                    _sql[_component] = _this->_method(_query, _query->_component);
                }
            }

            return _sql;
        }

        string query_grammar::compile_aggregate(query_builder& _query, vector<string> _aggregate) {
            _column = _this->columnize(_aggregate['columns']);

            // If the query has a "distinct" constraint and we're not asking for all columns
            // we need to prepend "distinct" onto the column name so that the query takes
            // it into account when it performs the aggregating operations on the data.
            if (_query->distinct && _column != = '*') {
                _column = 'distinct '._column;
            }

            return 'select '._aggregate['function'].
            '('._column.
            ') as aggregate';
        }


    }
}

#endif //WPP_QUERY_GRAMMAR_HPP
