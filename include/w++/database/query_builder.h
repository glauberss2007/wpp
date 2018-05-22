//
// Created by Alan de Freitas on 16/11/2017.
//

#ifndef WPP_DB_QUERY_BUILDER_H
#define WPP_DB_QUERY_BUILDER_H

#include <algorithm>
#include <memory>

#include "utils/container/php_utils.h"
#include "utils/string_utils.h"

#include "datatype_alias.h"
#include "aux_data_types.h"
#include "processor.h"
#include "result.h"

namespace wpp {

    namespace db {

        // forward declarations
        class connection;

        class query_grammar;

        class join_clause;

        struct where_properties;
        struct having_properties;
        struct order_properties;
        struct union_properties;

        // class
        class query_builder {
                using self_t = query_builder;

            public:
                // The database connection instance.
                wpp::db::connection &_connection;

                // The database query grammar instance.
                std::shared_ptr<query_grammar> _grammar;

                // The database query post processor instance.
                std::shared_ptr<processor> _processor;

                // The current query value bindings.
                // @var vector<string>
                flat_map<string, vector<string>> _bindings = {
                        {"select", {}},
                        {"join",   {}},
                        {"where",  {}},
                        {"having", {}},
                        {"order",  {}},
                        {"union",  {}}
                };

                // An aggregate self_t& and column to be run.
                vector<pair<string,vector<string>>> _aggregate;

                // The columns that should be returned.
                vector<string> _columns;

                // Indicates if the query returns distinct results.
                bool _distinct = false;

                // The table which the query is targeting.
                string _from;

                // The table joins for the query.
                vector<join_clause> _joins;

                // The where constraints for the query.
                vector<where_properties> _wheres;

                // The groupings for the query.
                vector<string> _groups;

                // The having constraints for the query.
                vector<having_properties> _havings;

                // The maximum number of records to return.
                int _limit;

                // The number of records to skip.
                int _offset;

                // The query union statements.
                vector<union_properties> _unions;

                // The maximum number of union records to return.
                int _union_limit{-1};

                // The number of union records to skip.
                int _union_offset{-1};

                // The orderings for the query.
                vector<order_properties> _orders;

                // The orderings for the union query.
                vector<order_properties> _union_orders;

                // Indicates whether row locking is being used.
                string _lock;

                // All of the available clause operators.
                vector<string> _operators =
                        {
                                "=", "<", ">", "<=", ">=", "<>", "!=",
                                "like", "like binary", "not like", "between", "ilike",
                                "&", "|", "^", "<<", ">>",
                                "rlike", "regexp", "not regexp",
                                "~", "~*", "!~", "!~*", "similar to",
                                "not similar to", "not ilike", "~~*", "!~~*",
                        };

                // Whether use write pdo for select.
                bool _use_write_pdo = false;

                // Create a new query query_builder instance.
                query_builder(db::connection &_connection,
                              std::shared_ptr<db::query_grammar> __grammar = nullptr,
                              std::shared_ptr<db::processor> __processor = nullptr);

                query_builder(db::connection& _connection,
                                             db::query_grammar &__grammar,
                                             db::processor &__processor);


                // Chunk the results of the query.
                template<typename callable>
                bool chunk(int _count, callable _callback) {
                    this->enforce_order_by();

                    int _page = 1;

                    size_t _count_results;

                    do {
                        // We'll execute the query for the given page and get the results. If there are
                        // no results we can just break and return from here. When there are results
                        // we will call the callback with the current chunk of these results here.
                        db::result _results = this->for_page(_page, _count).get();

                        _count_results = _results.size();

                        if (_count_results == 0) {
                            break;
                        }

                        // On each chunk result set, we will pass them to the callback and then let the
                        // developer take care of everything within the callback, which allows us to
                        // keep the memory low for spinning through large result sets for working.
                        if (!_callback(_results)) {
                            return false;
                        }

                        _page++;
                    } while (_count_results == _count);

                    return true;
                }

                // Execute a callback over each item while chunking
                template<typename callable>
                bool each(callable _callback, int _count = 1000) {
                    return this->chunk(_count, [&_callback](db::result _results) {
                        for (db::row r: _results) {
                            if (!_callback(r)) {
                                return false;
                            }
                        }
                        return true;
                    });
                }

                // Execute the query and get the first result.
                wpp::db::row first(vector<string> _columns = {"*"}) {
                    return this->take(1).get(_columns).front();
                }

                // Apply the callback's query changes if the given "value" is true.
            public:
                template<typename mixed, typename Closure>
                mixed when(bool _value, Closure _callback, Closure _default = nullptr) {
                    if (_value) {
                        auto r = _callback(*this, _value);
                        return r ? r : *this;
                    } else {
                        if (_default != nullptr) {
                            auto r = _default(*this, _value);
                            return r ? r : *this;
                        }
                    }

                    return *this;
                }

                // Set the columns to be selected.
                // @param  vector<string>|mixed  _columns
                // @return _this
                self_t &select(vector<string> _columns = {"*"}) {
                    this->_columns = _columns;
                    return *this;
                }

                self_t &select(string column1) {
                    this->_columns = {column1};
                    return *this;
                }

                template<typename ...Args>
                self_t &select(string column1, Args... args) {
                    this->_columns = func_get_args(column1, args...);
                    return *this;
                }

                // Add a new "raw" select expression to the query.
                self_t &select_raw(string _expression, vector<string> _bindings = {}) {
                    this->add_select(_expression);
                    if (!_bindings.empty()) {
                        this->add_binding(_bindings, "select");
                    }

                    return *this;
                }

                // Add a subselect expression to the query.
                template<typename string_or_self>
                self_t &select_sub(string_or_self _query, string _as);

                // Add a subselect expression to the query.
                self_t &select_sub(function<string(query_builder &)> _callback, string _as) {
                    // If the given query is a Closure, we will execute it while passing in a new
                    // query instance to the Closure. This will give the developer a chance to
                    // format and work with the query before we cast it to a raw SQL string.
                    query_builder _query = this->new_query();
                    _callback(_query);

                    return select_sub(_query, _as);
                }

                // Parse the sub-select query into SQL and bindings.
                std::tuple<string, vector<string>> parse_sub_select(query_builder _query) {
                    _query._columns = {_query._columns[0]};
                    return std::make_tuple(_query.to_sql(), _query.get_bindings());
                }

                // Parse the sub-select query into SQL and bindings.
                std::tuple<string, vector<string>> parse_sub_select(string _query) {
                    return make_tuple(_query, vector<string>());
                }

                // Add a new select column to the query.
                self_t &add_select(vector<string> _column) {
                    _column = _column;
                    this->_columns.insert(this->_columns.end(), _column.begin(), _column.end());
                    return *this;
                }

                template<typename ...StringArgs>
                self_t &add_select(StringArgs... columns) {
                    vector<string> _column = func_get_args(columns...);
                    return this->add_select(_column);
                }

                // Force the query to only return distinct results.
                self_t &distinct() {
                    this->_distinct = true;
                    return *this;
                }

                // Set the table which the query is targeting.
                self_t &from(string _table) {
                    this->_from = _table;
                    return *this;
                }

                // Add a join clause to the query.
                self_t &join(string _table,
                             string _first,
                             string _operator = "",
                             string _second = "",
                             string _type = "inner",
                             bool _where = false);

                // Add a join clause to the query.
                self_t &join(string _table,
                             function<string(join_clause &)> _first,
                             string _operator = "",
                             string _second = "",
                             string _type = "inner",
                             bool _where = false);

                // Add a "join where" clause to the query.
                self_t &
                join_where(string _table, string _first, string _operator, string _second, string _type = "inner") {
                    return this->join(_table, _first, _operator, _second, _type, true);
                }

                // Add a left join to the query.
                self_t &left_join(string _table, string _first, string _operator = "", string _second = "") {
                    return this->join(_table, _first, _operator, _second, "left");
                }

                // Add a "join where" clause to the query.
                self_t &left_join_where(string _table, string _first, string _operator, string _second) {
                    return this->join_where(_table, _first, _operator, _second, "left");
                }

                // Add a right join to the query.
                self_t &right_join(string _table, string _first, string _operator = "", string _second = "") {
                    return this->join(_table, _first, _operator, _second, "right");
                }

                // Add a "right join where" clause to the query.
                self_t &right_join_where(string _table, string _first, string _operator, string _second) {
                    return this->join_where(_table, _first, _operator, _second, "right");
                }

                // Add a "cross join" clause to the query.
                self_t &cross_join(string _table, string _first = "", string _operator = "", string _second = "");

                // Pass the query to a given callback.
                template<typename Closure>
                self_t &tap(Closure _callback) {
                    return this->when(true, _callback);
                }

                // Merge an vector<string> of where clauses and bindings.
                void merge_wheres(vector<where_properties> _wheres, vector<string> _bindings);

                self_t &where(string column, string _operator = "");

                self_t &where(string column, string _operator, string value, string boolean = "and");

                self_t &where(string column, string _operator, bool value, string boolean = "and") {
                    if (this->invalid_operator(_operator)) {
                        _operator = "=";
                    }

                    return this->where_null(column, boolean, _operator != "=");
                }

                self_t &where(string column, string _operator, int value, string boolean = "and") {
                    return this->where(column,_operator,std::to_string(value),boolean);
                }

                template<typename Closure>
                self_t &where(string column, string _operator, Closure value, string boolean = "and") {

                    if (this->invalid_operator(_operator)) {
                        value = _operator;
                        _operator = "=";
                    }
                    return this->where_sub(column, _operator, value, boolean);
                }


                self_t &where(vector<pair<string, string>> column,
                              string _operator = "",
                              string value = "",
                              string boolean = "and") {
                    return this->add_array_of_wheres(column, boolean);
                }

                template<typename Closure>
                self_t &
                where(vector<pair<string, string>> column,
                      string _operator = "",
                      Closure value = "",
                      string boolean = "and") {
                    return this->add_array_of_wheres(column, boolean);
                }

                template<typename Closure>
                self_t &where(Closure column, string _operator = "", string value = "", string boolean = "and") {
                    this->prepare_value_and_operator(value, _operator, !_operator.empty() && value.empty());
                    // If the columns is actually a Closure instance, we will assume the developer
                    // wants to begin a nested where statement which is wrapped in parenthesis.
                    // We"ll add that Closure to the query then return back out immediately.
                    return this->where_nested(column, boolean);

                }

                template<typename Closure>
                self_t &where(Closure column, string _operator, bool value, string boolean = "and") {
                    if (this->invalid_operator(_operator)) {
                        _operator = "=";
                    }
                    // If the columns is actually a Closure instance, we will assume the developer
                    // wants to begin a nested where statement which is wrapped in parenthesis.
                    // We"ll add that Closure to the query then return back out immediately.
                    return this->where_nested(column, boolean);

                }

                template<typename Closure>
                self_t &where(Closure column, string _operator, Closure value, string boolean = "and") {
                    if (this->invalid_operator(_operator)) {
                        _operator = "=";
                    }
                    // If the columns is actually a Closure instance, we will assume the developer
                    // wants to begin a nested where statement which is wrapped in parenthesis.
                    // We"ll add that Closure to the query then return back out immediately.
                    return this->where_nested(column, boolean);

                }

                // Add an list of where clauses to the query.
                // key/value pairs
                self_t &
                add_array_of_wheres(vector<pair<string, string>> _column, string _boolean, string _method = "where") {
                    return this->where_nested([&_column, &_method](query_builder query) {
                        for (pair<string, string> &c: _column) {
                            const string key = c.first;
                            const string value = c.second;
                            if (_method == "where") {
                                query.where(key, "=", value);
                            } else if (_method == "where_column") {
                                query.where_column(key, "=", value);
                            } else if (_method == "or_where") {
                                query.or_where(key, "=", value);
                            } else if (_method == "where_date" && utils::is_int(value)) {
                                query.where_date(key, "=", std::stol(value));
                            } else if (_method == "where_day" && utils::is_int(value)) {
                                query.where_day(key, "=", std::stol(value));
                            } else if (_method == "where_month" && utils::is_int(value)) {
                                query.where_month(key, "=", std::stol(value));
                            } else if (_method == "where_time" && utils::is_int(value)) {
                                query.where_time(key, "=", std::stol(value));
                            } else if (_method == "where_year" && utils::is_int(value)) {
                                query.where_year(key, "=", std::stol(value));
                            } else {
                                query.where(key, "=", value);
                            }
                        }
                    });
                }

                // Prepare the value and operator for a where clause.
                // @param  string  _value
                // @param  string  _operator
                // @param  bool  _use_default
                // @return vector<string>
                // @throws \Invalid_argument_exception

                void prepare_value_and_operator(string &_value, string &_operator, bool _use_default = false) {
                    if (_use_default) {
                        _value = _operator;
                        _operator = "=";
                    } else if (this->invalid_operator_and_value(_operator, _value)) {
                        throw "Illegal operator and value combination.";
                    }
                }

                void prepare_value_and_operator(bool &_value, string &_operator, bool _use_default = false) {
                    if (_use_default) {
                        _operator = "=";
                    } else if (this->invalid_operator_and_value(_operator, _value)) {
                        throw "Illegal operator and value combination.";
                    }
                }

                void prepare_value_and_operator(int &_value, string &_operator, bool _use_default = false) {
                    if (_use_default) {
                        _operator = "=";
                    } else if (this->invalid_operator_and_value(_operator, _value)) {
                        throw "Illegal operator and value combination.";
                    }
                }

                // Determine if the given operator and value combination is legal.
                // Prevents using Null values with invalid operators.
                bool invalid_operator_and_value(string _operator, string _value) {
                    return _value.empty() && utils::in_array(_operator, this->_operators) &&
                           !utils::in_array(_operator, vector<string>({"=", "<>", "!="}));
                }

                template<typename bool_or_number>
                bool invalid_operator_and_value(string _operator, bool_or_number _value) {
                    return utils::in_array(_operator, this->_operators) &&
                           !utils::in_array(_operator, vector<string>({"=", "<>", "!="}));
                }

                // Determine if the given operator is supported.
                bool invalid_operator(string _operator);

                // Add an "or where" clause to the query.
                template<class COL_TYPE, class VALUE_TYPE>
                self_t &or_where(COL_TYPE _column, string _operator = "", VALUE_TYPE _value = "") {
                    return this->where(_column, _operator, _value, "or");
                }

                // Add a "where" clause comparing two columns to the query.
                self_t &where_column(vector<pair<string, string>> _first,
                                     string _operator = "",
                                     string _second = "",
                                     string _boolean = "and") {
                    // If the column is an vector<string>, we will assume it is an vector<string> of key-value pairs
                    // and can add them each as a where clause. We will maintain the boolean we
                    // received when the method was called and pass it into the nested where.
                    return this->add_array_of_wheres(_first, _boolean, "where_column");
                }

                self_t &
                where_column(string _first, string _operator = "", string _second = "", string _boolean = "and");

                // Add an "or where" clause comparing two columns to the query.
                // @param  string|vector<string>  _first
                // @param  string|null  _operator
                // @param  string|null  _second
                // @return query_builder|static
                template<class COL_TYPE>
                self_t &or_where_column(COL_TYPE _first, string _operator = "", string _second = "") {
                    return this->where_column(_first, _operator, _second, "or");
                }

                // Add a raw where clause to the query.
                self_t &where_raw(string _sql, vector<string> _bindings = {}, string _boolean = "and");

                // Add a raw or where clause to the query.
                self_t &or_where_raw(string _sql, vector<string> _bindings = {}) {
                    return this->where_raw(_sql, _bindings, "or");
                }

                // Add a "where in" clause to the query.
                self_t &where_in(string _column, query_builder _values, string _boolean = "and", bool _not = false) {
                    string _type = _not ? "NotIn" : "In";

                    // If the value is a query query_builder instance we will assume the developer wants to
                    // look for any values that exists within this given query. So we will add the
                    // query accordingly so that this query is properly executed when it is run.
                    return this->where_in_existing_query(_column, _values, _boolean, _not);
                }

                // Add a "where in" clause to the query.
                template<typename Closure>
                self_t &where_in(string _column,
                                 Closure _values,
                                 string _boolean = "and",
                                 bool _not = false) {
                    string _type = _not ? "NotIn" : "In";

                    // If the value of the where in clause is actually a Closure, we will assume that
                    // the developer is using a full sub-select for this "in" statement, and will
                    // execute those Closures, then we can re-construct the entire sub-selects.
                    return this->where_in_sub(_column, _values, _boolean, _not);
                }

                // Add a "where in" clause to the query.
                self_t &
                where_in(string _column, vector<string> _values, string _boolean = "and", bool _not = false);

                // Add an "or where in" clause to the query.
                template<typename MIXED>
                self_t &or_where_in(string _column, MIXED _values) {
                    return this->where_in(_column, _values, "or");
                }

                // Add a "where not in" clause to the query.
                template<typename MIXED>
                self_t &where_not_in(string _column, MIXED _values, string _boolean = "and") {
                    return this->where_in(_column, _values, _boolean, true);
                }

                // Add an "or where not in" clause to the query.
                template<typename MIXED>
                self_t &or_where_not_in(string _column, MIXED _values) {
                    return this->where_not_in(_column, _values, "or");
                }

                // Add a where in with a sub-select to the query.
                template<typename Closure>
                self_t &where_in_sub(string _column, Closure _callback, string _boolean, bool _not);

                // Add an external sub-select to the query.
                self_t &where_in_existing_query(string _column, query_builder _query, string _boolean, bool _not);

                // Add a "where null" clause to the query.
                self_t &where_null(string _column, string _boolean = "and", bool _not = false);

                // Add an "or where null" clause to the query.
                self_t &or_where_null(string _column) {
                    return this->where_null(_column, "or");
                }

                // Add a "where not null" clause to the query.
                self_t &where_not_null(string _column, string _boolean = "and") {
                    return this->where_null(_column, _boolean, true);
                }

                // Add a where between statement to the query.
                self_t &
                where_between(string _column, vector<string> _values, string _boolean = "and", bool _not = false);

                // Add an or where between statement to the query.
                self_t &or_where_between(string _column, vector<string> _values) {
                    return this->where_between(_column, _values, "or");
                }

                // Add a where not between statement to the query.
                self_t &where_not_between(string _column, vector<string> _values, string _boolean = "and") {
                    return this->where_between(_column, _values, _boolean, true);
                }

                // Add an or where not between statement to the query.
                self_t &or_where_not_between(string _column, vector<string> _values) {
                    return this->where_not_between(_column, _values, "or");
                }

                // Add an "or where not null" clause to the query.
                self_t &or_where_not_null(string _column) {
                    return this->where_not_null(_column, "or");
                }

                // Add a "where date" statement to the query.
                template<typename MIXED>
                self_t &where_date(string _column, int _value) {
                    string _boolean = "and";
                    string _operator = "=";
                    return this->add_date_based_where("Date", _column, _operator, _value, _boolean);
                }

                self_t &where_date(string _column, string _operator, int _value, string _boolean = "and") {
                    if (this->invalid_operator(_operator)){
                        _operator = "=";
                    }
                    return this->add_date_based_where("Date", _column, _operator, _value, _boolean);
                }

                // Add an "or where date" statement to the query.
                self_t &or_where_date(string _column, string _operator, int _value) {
                    return this->where_date(_column, _operator, _value, "or");
                }

                // Add a "where time" statement to the query.
                self_t &where_time(string _column, string _operator, int _value, string _boolean = "and") {
                    return this->add_date_based_where("Time", _column, _operator, _value, _boolean);
                }

                // Add an "or where time" statement to the query.
                self_t &or_where_time(string _column, string _operator, int _value) {
                    return this->where_time(_column, _operator, _value, "or");
                }

                // Add a "where day" statement to the query.
                template<typename MIXED>
                self_t &where_day(string _column, string _operator, MIXED _value, string _boolean = "and") {
                    if (this->invalid_operator(_operator)) {
                        _operator = "=";
                    }
                    return this->add_date_based_where("Day", _column, _operator, _value, _boolean);
                }


                self_t &where_day(string _column, int _value) {
                    string _boolean = "and";
                    string _operator = "=";
                    return this->add_date_based_where("Day", _column, _operator, _value, _boolean);
                }


                // Add a "where month" statement to the query.
                self_t &where_month(string _column, int _value) {
                    string _operator = "=";
                    string _boolean = "and";
                    return this->add_date_based_where("Month", _column, _operator, _value, _boolean);
                }

                self_t &where_month(string _column, string _operator, int _value, string _boolean = "and") {
                    if (this->invalid_operator(_operator)) {
                        _operator = "=";
                    }
                    return this->add_date_based_where("Month", _column, _operator, _value, _boolean);
                }

                // Add a "where year" statement to the query.
                self_t &where_year(string _column, int _value) {
                    string _operator = "=";
                    string _boolean = "and";
                    return this->add_date_based_where("Year", _column, _operator, _value, _boolean);
                }

                self_t &where_year(string _column, string _operator, int _value, string _boolean = "and") {
                    if (this->invalid_operator(_operator)) {
                        _operator = "=";
                    }
                    return this->add_date_based_where("Year", _column, _operator, _value, _boolean);
                }

                // Add a date based (year, month, day, time) statement to the query.
                self_t &add_date_based_where(string _type,
                                             string _column,
                                             string _operator,
                                             int _value,
                                             string _boolean = "and");

                // Add a nested where statement to the query.
                template<typename Closure>
                self_t &where_nested(Closure _callback, string _boolean = "and") {
                    query_builder _query = this->for_nested_where();
                    _callback(_query);
                    return this->add_nested_where_query(_query, _boolean);
                }

                // Create a new query instance for nested where condition.
                self_t &for_nested_where() {
                    return this->new_query().from(this->_from);
                }

                // Add another query query_builder as a nested where to the query query_builder.
                self_t &add_nested_where_query(query_builder _query, string _boolean = "and");

                // Add a full sub-select to the query.
                template<typename Closure>
                self_t &where_sub(string _column, string _operator, Closure _callback, string _boolean);

                // Add an exists clause to the query.
                template<typename Closure>
                self_t &where_exists(Closure _callback, string _boolean = "and", bool _not = false) {
                    query_builder _query = this->new_query();

                    // Similar to the sub-select clause, we will create a new query instance so
                    // the developer may cleanly specify the entire exists query and we will
                    // compile the whole thing in the grammar and insert it into the SQL.
                    _callback(_query);

                    return this->add_where_exists_query(_query, _boolean, _not);
                }

                // Add an or exists clause to the query.
                template<typename Closure>
                self_t &or_where_exists(Closure _callback, bool _not = false) {
                    return this->where_exists(_callback, "or", _not);
                }

                // Add a where not exists clause to the query.
                template<typename Closure>
                self_t &where_not_exists(Closure _callback, string _boolean = "and") {
                    return this->where_exists(_callback, _boolean, true);
                }

                // Add a where not exists clause to the query.
                template<typename Closure>
                self_t &or_where_not_exists(Closure _callback) {
                    return this->or_where_exists(_callback, true);
                }

                // Add an exists clause to the query.
                self_t &add_where_exists_query(query_builder _query, string _boolean = "and", bool _not = false);

                // Handles dynamic "where" clauses to the query.
                self_t &dynamic_where(string _method, vector<string> _parameters) {
                    string _finder = _method.substr(5);
                    std::vector<std::string> _segments = utils::preg_split("/(And|Or)(?={{}A-Z})/", _finder, false, true);

                    // The connector variable will determine which connector will be used for the
                    // query condition. We will change it as we come across new boolean values
                    // in the dynamic method strings, which could contain a number of these.
                    string _connector = "and";

                    int _index = 0;

                    for (string &_segment :_segments) {
                        // If the segment is not a boolean connector, we can assume it is a column"s name
                        // and we will add it to the query as a new constraint as a where clause, then
                        // we can keep iterating through the dynamic method string"s segments again.
                        if (_segment != "And" && _segment != "Or") {
                            this->add_dynamic(_segment, _connector, _parameters, _index);
                            _index++;
                        }
                            // Otherwise, we will store the connector so we know how the next where clause we
                            // find in the query should be connected to the previous ones, meaning we will
                            // have the proper boolean connector to connect the next where clause found.
                        else {
                            _connector = _segment;
                        }
                    }

                    return *this;
                }

                // Add a single dynamic where clause statement to the query.
                void add_dynamic(string _segment, string _connector, vector<string> _parameters, int _index) {
                    // Once we have parsed out the columns and formatted the boolean operators we
                    // are ready to add it to this query as a where clause just like any other
                    // clause on the query. Then we"ll increment the parameter index values.
                    string _bool = utils::strtolower(_connector);

                    this->where(utils::snake(_segment), "=", _parameters[_index], _bool);
                }

                // Add a "group by" clause to the query.
                self_t &group_by(vector<string> _groups) {
                    this->_groups.insert(this->_groups.end(), _groups.begin(), _groups.end());
                    return *this;
                }

                // Add a "group by" clause to the query.
                self_t &group_by(vector<vector<string>> _groups) {
                    for (vector<string> &_group: _groups) {
                        this->_groups.insert(this->_groups.end(), _group.begin(), _group.end());
                    }
                    return *this;
                }

                self_t &having(string _column, string _value = ""){
                    string _operator = "=";
                    this->having(_column, _operator, _value, "and");
                    return *this;
                }

                // Add a "having" clause to the query.
                self_t &having(string _column, string _operator, string _value, string _boolean = "and");

                // Add a "or having" clause to the query.
                self_t &or_having(string _column, string _operator = "", string _value = "") {
                    return this->having(_column, _operator, _value, "or");
                }

                // Add a raw having clause to the query.
                self_t &having_raw(string _sql, vector<string> _bindings = {}, string _boolean = "and");

                // Add a raw or having clause to the query.
                self_t &or_having_raw(string _sql, vector<string> _bindings = {}) {
                    return this->having_raw(_sql, _bindings, "or");
                }

                // Add an "order by" clause to the query.
                self_t &order_by(string _column, string _direction = "asc");

                // Add a descending "order by" clause to the query.
                self_t &order_by_desc(string _column) {
                    return this->order_by(_column, "desc");
                }

                // Add an "order by" clause for a timestamp to the query.
                self_t &latest(string _column = "created_at") {
                    return this->order_by(_column, "desc");
                }

                // Add an "order by" clause for a timestamp to the query.
                self_t &oldest(string _column = "created_at") {
                    return this->order_by(_column, "asc");
                }

                // Put the query"s results in random order.
                self_t &in_random_order(string _seed = "");

                // Add a raw "order by" clause to the query.
                self_t &order_by_raw(string _sql, vector<string> _bindings = {});

                // Alias to set the "offset" value of the query.
                self_t &skip(int _value) {
                    return this->offset(_value);
                }

                // Set the "offset" value of the query.
                self_t &offset(int _value) {
                    if (!this->_unions.empty()) {
                        this->_union_offset = std::max(0, _value);
                    } else {
                        this->_offset = std::max(0, _value);
                    }

                    return *this;
                }

                // Alias to set the "limit" value of the query.
                self_t &take(int _value) {
                    return this->limit(_value);
                }

                // Set the "limit" value of the query.
                self_t &limit(int _value) {
                    if (!this->_unions.empty()) {
                        this->_union_limit = _value;
                    } else {
                        this->_limit = _value;
                    }
                    return *this;
                }

                // Set the limit and offset for a given page.
                self_t &for_page(int _page, int _per_page = 15) {
                    return this->skip((_page - 1) * _per_page).take(_per_page);
                }

                // Constrain the query to the next "page" of results after a given ID.
                self_t &for_page_after_id(int _per_page = 15, int _last_id = 0, string _column = "id") {
                    this->_orders = this->remove_existing_orders_for(_column);
                    return this->where(_column, ">", _last_id).order_by(_column, "asc").take(_per_page);
                }

                // Get an vector<string> orders with all orders for an given column removed.
                vector<order_properties> remove_existing_orders_for(string _column);

                // Add a union statement to the query.
                self_t &union_statement(query_builder _query, bool _all = false);

                template<typename Closure>
                self_t &union_statement(Closure _closure_query, bool _all = false);

                // Add a union all statement to the query.
                template<typename CLOSURE_OR_QUERY_BUILDER>
                self_t &union_all(CLOSURE_OR_QUERY_BUILDER _query) {
                    return this->union_statement(_query, true);
                }

                // Lock the selected rows in the table.
                self_t &lock(string _value) {
                    this->_lock = _value;
                    if (this->_lock.empty()) {
                        this->use_write_pdo();
                    }
                    return *this;
                }

                self_t &lock(bool _value = true) {
                    this->_lock = _value;
                    return *this;
                }

                // Lock the selected rows in the table for updating.
                self_t &lock_for_update() {
                    return this->lock(true);
                }

                // Share lock the selected rows in the table.
                self_t &shared_lock() {
                    return this->lock(false);
                }

                // Get the SQL representation of the query.
                string to_sql();

                // Execute a query for a single record by ID.
                wpp::db::row find(int _id, vector<string> _columns = {"*"}) {
                    return this->where(string("id"), string("="), _id).first(_columns);
                }

                // Get a single column's value from the first result of a query.
                wpp::db::field value(string _column) {
                    wpp::db::row r = this->first({_column});
                    //return (!r.empty()) ? r.front() : wpp::db::field();
                    return r.front();
                }

            public:
                // Execute the query as a "select" statement.
                wpp::db::result get(vector<string> columns = {"*"}) {
                    vector<string> original = this->_columns;

                    if (original.empty()) {
                        this->_columns = columns;
                    }

                    wpp::db::result results = this->_processor->process_select(*this, this->run_select());

                    this->_columns = original;

                    return results;
                }

            protected:
                // Run the query as a "select" statement against the connection.
                vector<string> run_select();

            public:
                // Paginate the given query into a simple paginator.
                length_aware_paginator
                paginate(int per_page = 15, vector<string> columns = {"*"}, string page_name = "page", int page = -1) {
                    page = (page > 0) ? page : paginator::resolve_current_page(page_name);

                    int total = this->get_count_for_pagination(columns);

                    wpp::db::result results = total > 0 ? this->for_page(page, per_page).get(columns) : wpp::db::result();

                    return length_aware_paginator(results, total, per_page, page, {{"path",      paginator::resolve_current_path()}, {"page_name", page_name}});
                }

                // Get a paginator only supporting simple next and previous links.
                paginator simple_paginate(int per_page = 15,
                                          vector<string> columns = {"*"},
                                          string page_name = "page",
                                          int page = -1) {
                    page = page == -1 ? page : paginator::resolve_current_page(page_name);

                    this->skip((page - 1) * per_page).take(per_page + 1);

                    return paginator(this->get(columns), per_page, page,{{"path",      paginator::resolve_current_path()},{"page_name", page_name}});
                }

                // Get the count of the total records for the paginator.
                int get_count_for_pagination(vector<string> columns = {"*"}) {
                    wpp::db::result results = this->run_pagination_count_query(columns);

                    // Once we have run the pagination count query, we will get the resulting count and
                    // take into account what type of query it was. When there is a group by we will
                    // just return the count of the entire results set since that will be correct.
                    if (!this->_groups.empty()) {
                        return results.size();
                    } else if (results.empty()) {
                        return 0;
                    } else {// if (string(results[0]["aggregate"].c_str()) != "") {
                        return std::stoi(string(results[0]["aggregate"].c_str()));
                    } // else {
                        //return (int) array_change_key_case({results[0]})["aggregate"];
                    //}
                }

            protected:
                // Run a pagination count query.
                wpp::db::result run_pagination_count_query(vector<string> columns = {"*"}) {
                    return this->clone_without({"columns", "orders", "limit", "offset"})
                               .clone_without_bindings({"select", "order"})
                               .set_aggregate("count", this->without_select_aliases(columns))
                               .get();
                    //.all();
                }

            protected:
                // Remove the column aliases since they will break count queries.
                vector<string> without_select_aliases(vector<string> columns) {
                    for (string &column :columns) {
                        string lcolumn = utils::strtolower(column);
                        size_t alias_position = lcolumn.find(" as ");
                        column = (alias_position != string::npos) ? column.substr(0, alias_position) : column;
                    }
                    return columns;
                }

            public:
                // Get a generator for the given query.
                generator cursor();

            public:
                // Chunk the results of a query by comparing numeric IDs.
                template<typename callable>
                bool chunk_by_id(int count, callable callback, string column = "id", string alias = "") {
                    alias = alias.empty() ? alias : column;

                    int last_id = 0;

                    size_t count_results;

                    do {
                        query_builder clone = *this;

                        // We'll execute the query for the given page and get the results. If there are
                        // no results we can just break and return from here. When there are results
                        // we will call the callback with the current chunk of these results here.
                        wpp::db::result results = clone.for_page_after_id(count, last_id, column).get();

                        count_results = results.size();

                        if (count_results == 0) {
                            break;
                        }

                        // On each chunk result set, we will pass them to the callback and then let the
                        // developer take care of everything within the callback, which allows us to
                        // keep the memory low for spinning through large result sets for working.
                        if (!callback(results)) {
                            return false;
                        }

                        last_id = std::stoi(string(results.back()[alias].c_str()));

                    } while (count_results == count);

                    return true;
                }

            protected:
                // Throw an exception if the query doesn"t have an order_by clause.
                void enforce_order_by() {
                    if (this->_orders.empty() && this->_union_orders.empty()) {
                        throw std::string("You must specify an order_by clause when using this function.");
                    }
                }

            public:
                // Get an array with the values of a given column.
                vector<field> pluck(string column) {
                    wpp::db::result results = this->get({column});
                    // If the columns are qualified with a table or have an alias, we cannot use
                    // those directly in the "pluck" operations since the results from the DB
                    // are only keyed by the column itself. We"ll strip the table out here.
                    string pluck_value = this->strip_table_for_pluck(column);
                    return results.pluck(pluck_value);
                }

                // Get an array with the values of a given column.
                vector<pair<field,field>> pluck(string column, string key) {
                    wpp::db::result results = this->get({column,key});
                    // If the columns are qualified with a table or have an alias, we cannot use
                    // those directly in the "pluck" operations since the results from the DB
                    // are only keyed by the column itself. We"ll strip the table out here.
                    string pluck_value = this->strip_table_for_pluck(column);
                    string pluck_key = this->strip_table_for_pluck(key);
                    return results.pluck(pluck_value, pluck_key);
                }

            protected:
                // Strip off the table name or alias from a column identifier.
                string strip_table_for_pluck(string column = "") {
                    if (column.empty()) {
                        return column;
                    } else {
                        vector<string> columns = utils::preg_split("~\\.| ~", column);
                        return columns.back();
                    }
                }

            public:
                // Concatenate values of a given column as a string.
                string implode(string column, string glue = "") {
                    vector<field> v = this->pluck(column);
                    return utils::implode<field>(glue,v);
                }

                // Determine if any rows exist for the current query.
                bool exists();

                // Retrieve the "count" result of the query.
                int count(string columns = "*") {
                    return this->aggregate("count", {columns}).as<int>();
                }

                // Retrieve the minimum value of a given column.
                wpp::db::field min(string column) {
                    return this->aggregate("min", {column});
                }

                wpp::db::field max(string column) {
                    return this->aggregate("max", {column});
                }

                // Retrieve the sum of the values of a given column.
                wpp::db::field sum(string column) {
                    return this->aggregate("sum", {column});
                }

                // Retrieve the average of the values of a given column.
                wpp::db::field avg(string column) {
                    return this->aggregate("avg", {column});
                }

                // Alias for the "avg" method.
                wpp::db::field average(string column) {
                    return this->avg(column);
                }

                // Execute an aggregate function on the database.
                wpp::db::field aggregate(string function, vector<string> columns = {"*"}) {
                    wpp::db::result results = this->clone_without({"columns"})
                                                  .clone_without_bindings({"select"})
                                                  .set_aggregate(function, columns)
                                                  .get(columns);

                    if (!results.empty()) {
                        return results[0].change_key_case()["aggregate"];
                    } else {
                        return field();
                    }
                }

                // Execute a numeric aggregate function on the database.
                string numeric_aggregate(string function, vector<string> columns = {"*"}) {
                    wpp::db::field result = this->aggregate(function, columns);

                    // If there is no result, we can obviously just return 0 here. Next, we will check
                    // if the result is an integer or float. If it is already one of these two data
                    // types we can just return the result as-is, otherwise we will convert this.
                    if (result.empty()) {
                        return 0;
                    }

                    if (utils::is_int(result) || utils::is_double(result)) {
                        return result;
                    }
                    return "";
                }

            protected:
                // Set the aggregate property without running the query.
                self_t &set_aggregate(string function, vector<string> columns) {
                    this->_aggregate = {{"function", {function}},
                                        {"columns",  columns}};

                    if (this->_groups.empty()) {
                        this->_orders.clear();

                        this->_bindings["order"] = {};
                    }

                    return *this;
                }

            public:
                // Insert a new record into the database.
                bool insert(map<string, string> values);

                // Insert a new record into the database.
                bool insert(pair<string, string> value) {
                    return this->insert({value});
                }

                // Insert a new record and get the value of the primary key.
                int insert_get_id(vector<string> values, string sequence = "");

                // Update a record in the database.
                int update(vector<pair<string,string>> values);

                // Insert or update a record matching the attributes, and fill it with values.
                bool update_or_insert(vector<pair<string, string>> attributes, vector<pair<string, string>> values = {}) {
                    if (!this->where(attributes).exists()) {
                        map<string,string> m(values.begin(),values.end());
                        m.insert(attributes.begin(),attributes.end());
                        return this->insert(m);
                    }

                    return (bool) this->take(1).update(values);
                }

                // Increment a column's value by a given amount.
                int increment(string column, int amount = 1, vector<string> extra = {});

                // Decrement a column's value by a given amount.
                int decrement(string column, int amount = 1, vector<string> extra = {});

                // Delete a record from the database.
                template<typename ID_TYPE>
                int delete_entry(ID_TYPE id = -1);

                // Run a truncate statement on the table.
                void truncate();

                // Get a new instance of the query builder.
                query_builder new_query() {
                    return query_builder(this->_connection, this->_grammar, this->_processor);
                }

                // Create a raw database expression.
                template<typename MIXED>
                string raw(MIXED value);

                // Get the current query value bindings in a flattened array.
                vector<string> get_bindings() {
                    return utils::flatten<flat_map<string, vector<string>>,std::string>(this->_bindings);
                }

                // Get the raw array of bindings.
                flat_map<string, vector<string>> get_raw_bindings() {
                    return this->_bindings;
                }

                // Set the bindings on the query builder.
                self_t &set_bindings(vector<string> bindings, string type = "where") {
                    this->_bindings[type] = bindings;
                    return *this;
                }

                // Add a binding to the query.
                self_t &add_binding(vector<string> value, string type = "where") {
                    this->_bindings[type].insert(this->_bindings[type].end(),value.begin(),value.end());
                    return *this;
                }

                template<typename T>
                self_t &add_binding(T value, string type = "where") {
                    this->_bindings[type].push_back(value);
                    return *this;
                }

                // Merge an array of bindings into our bindings.
                self_t &merge_bindings(query_builder query) {
                    for (pair<string,vector<string>>& binding: this->_bindings) {
                        binding.second.insert(binding.second.end(),query._bindings[binding.first].begin(),query._bindings[binding.first].end());
                    }
                    return *this;
                }

            protected:
                // Remove all of the expressions from a list of bindings.
                // There are no expressions in our implementation
                vector<string> clean_bindings(vector<string> bindings) {
                    return bindings;
                }

            public:
                // Get the database connection instance.
                connection get_connection();

                // Get the database query processor instance.
                processor& get_processor() {
                    return *this->_processor;
                }

                std::shared_ptr<processor> get_processor_ptr() {
                    return this->_processor;
                }

                // Get the query grammar instance.
                query_grammar get_grammar();

                // Use the write pdo for query.
                self_t &use_write_pdo() {
                    this->_use_write_pdo = true;

                    return *this;
                }

                // Clone the query without the given properties.
                query_builder clone_without(vector<string> except) {
                    query_builder clone = *this;
                    for (auto &property: except) {
                        if (property == "wheres") {
                            clone._wheres.clear();
                        }
                        // ... and so on
                    }
                    return clone;
                }

                // Clone the query without the given bindings.
                query_builder clone_without_bindings(vector<string> except) {
                    query_builder clone = *this;
                    for (auto &type: except) {
                        clone._bindings[type] = {};
                    }
                    return clone;
                }

        };

        struct where_properties {
            string type;
            string column;
            string operator_;
            vector<string> values;
            string value;
            string boolean;
            string first;
            string second;
            string sql;
            query_builder query;
            bool not_;
        };

        struct having_properties {
            string type;
            string column;
            string operator_;
            string value;
            string boolean;
            string sql;
        };

        struct order_properties {
            string column;
            string direction;
            string type;
            string sql;
        };

        struct union_properties{
            query_builder query;
            bool all;
        };
    }


}
#endif //WPP_DB_QUERY_BUILDER_H
