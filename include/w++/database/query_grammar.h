//
// Created by Alan de Freitas on 20/11/2017.
//

#ifndef WPP_QUERY_GRAMMAR_H
#define WPP_QUERY_GRAMMAR_H

#include "base_grammar.h"
#include "query_builder.h"

namespace wpp {
    namespace db {

        class query_builder;

        class query_grammar
                : public base_grammar {
                /**
                 * The grammar specific operators.
                 *
                 * @var array
                 */
            protected:
                vector<string> _operators = {};

                /**
                 * The components that make up a select clause.
                 *
                 * @var array
                 */
            protected:
                vector<string> _select_components =
                        {
                                "aggregate",
                                "columns",
                                "from",
                                "joins",
                                "wheres",
                                "groups",
                                "havings",
                                "orders",
                                "limit",
                                "offset",
                                "unions",
                                "lock",
                        };

                /**
                 * Compile a select query into SQL.
                 *
                 * @param  query_builder&  _query
                 * @return string
                 */
            public:

                string compile_select(query_builder &_query);

                /**
                 * Compile the components necessary for a select clause.
                 *
                 * @param  query_builder&  _query
                 * @return array
                 */
            protected:

                vector<string> compile_components(query_builder &_query);

                /**
                 * Compile an aggregated select clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _aggregate
                 * @return string
                 */
            protected:

                string compile_aggregate(query_builder &_query, vector<string> _aggregate);

                /**
                 * Compile the "select *" portion of the query.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _columns
                 * @return string|null
                 */
            protected:

                string compile_columns(query_builder &_query, vector<string> _columns) {
                    // If the query is actually performing an aggregating select, we will let that
                    // compiler handle the building of the select clauses, as it will need some
                    // more syntax that is best handled by that function to keep things neat.
                    if (!_query._aggregate.empty()) {
                        return string();
                    }

                    std::string _select = _query._distinct ? "select distinct " : "select ";

                    return _select + this->columnize(_columns);
                }

                /**
                 * Compile the "from" portion of the query.
                 *
                 * @param  query_builder&  _query
                 * @param  string  _table
                 * @return string
                 */
            protected:

                string compile_from(query_builder &_query, string _table) {
                    return "from " + this->wrap_table(_table);
                }

                /**
                 * Compile the "join" portions of the query.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _joins
                 * @return string
                 */
            protected:

                string compile_joins(query_builder &_query, vector<join_clause> _joins) {
                    vector<string> collect_joins;
                    collect_joins.reserve(_joins.size());
                    for (join_clause &join: _joins) {
                        string table = this->wrap_table(join._table);
                        collect_joins.emplace_back(
                                utils::trim_copy(join._type + " join " + table + this->compile_wheres(join)));
                    }
                    return utils::implode(" ",collect_joins);
                }

                /**
                 * Compile the "where" portions of the query.
                 *
                 * @param  query_builder&  _query
                 * @return string
                 */
            protected:

                string compile_wheres(query_builder &_query) {
                    // Each type of where clauses has its own compiler function which is responsible
                    // for actually creating the where clauses SQL. This helps keep the code nice
                    // and maintainable since each clause has a very small method that it uses.
                    if (_query._wheres.empty()) {
                        return "";
                    }

                    // If we actually have some where clauses, we will strip off the first boolean
                    // operator, which is added by the query builders for convenience so we can
                    // avoid checking for the first clauses in each of the compilers methods.
                    vector<string> _sql = this->compile_wheres_to_array(_query);
                    if (!_sql.empty()) {
                        return this->concatenate_where_clauses(_query, _sql);
                    }

                    return "";
                }

                /**
                 * Get an array of all the where clauses for the query.
                 *
                 * @param  query_builder&  _query
                 * @return array
                 */
            protected:

                vector<string> compile_wheres_to_array(query_builder &_query) {
                    vector<string> where_strings;
                    where_strings.reserve(_query._wheres.size());
                    for (where_properties &where : _query._wheres) {
                        if (where.type == "date"){
                            where_strings.push_back(where.boolean + " " + this->where_date(_query,where));
                        } else if (where.type == "year"){
                            where_strings.push_back(where.boolean + " " + this->where_year(_query,where));
                        } else if (where.type == "time"){
                            where_strings.push_back(where.boolean + " " + this->where_time(_query,where));
                        } else if (where.type == "month"){
                            where_strings.push_back(where.boolean + " " + this->where_month(_query,where));
                        } else if (where.type == "day"){
                            where_strings.push_back(where.boolean + " " + this->where_day(_query,where));
                        } else if (where.type == "column"){
                            where_strings.push_back(where.boolean + " " + this->where_column(_query,where));
                        } else if (where.type == "basic"){
                            where_strings.push_back(where.boolean + " " + this->where_basic(_query,where));
                        } else if (where.type == "between"){
                            where_strings.push_back(where.boolean + " " + this->where_between(_query,where));
                        } else if (where.type == "exists"){
                            where_strings.push_back(where.boolean + " " + this->where_exists(_query,where));
                        } else if (where.type == "in"){
                            where_strings.push_back(where.boolean + " " + this->where_in(_query,where));
                        } else if (where.type == "in_sub"){
                            where_strings.push_back(where.boolean + " " + this->where_in_sub(_query,where));
                        } else if (where.type == "nested"){
                            where_strings.push_back(where.boolean + " " + this->where_nested(_query,where));
                        } else if (where.type == "not_exists"){
                            where_strings.push_back(where.boolean + " " + this->where_not_exists(_query,where));
                        } else if (where.type == "not_in"){
                            where_strings.push_back(where.boolean + " " + this->where_not_in(_query,where));
                        } else if (where.type == "not_in_sub"){
                            where_strings.push_back(where.boolean + " " + this->where_not_in_sub(_query,where));
                        } else if (where.type == "not_null"){
                            where_strings.push_back(where.boolean + " " + this->where_not_null(_query,where));
                        } else if (where.type == "raw"){
                            where_strings.push_back(where.boolean + " " + this->where_raw(_query,where));
                        } else if (where.type == "sub"){
                            where_strings.push_back(where.boolean + " " + this->where_sub(_query,where));
                        }
                    }
                    return where_strings;
                }

                /**
                 * Format the where clause statements into one string.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _sql
                 * @return string
                 */
            protected:

                string concatenate_where_clauses(query_builder _query, vector<string> _sql) {
                    string _conjunction = "where";
                    return _conjunction + " " + this->remove_leading_boolean(utils::implode(" ", _sql));
                }

                string concatenate_where_clauses(join_clause _query, vector<string> _sql) {
                    string _conjunction = "on";
                    return _conjunction + " " + this->remove_leading_boolean(utils::implode(" ", _sql));
                }

                /**
                 * Compile a raw where clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_raw(query_builder _query, where_properties _where) {
                    return _where.sql;
                }

                /**
                 * Compile a basic where clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_basic(query_builder _query, where_properties _where) {
                    string _value = this->parameter(_where.value);

                    return this->wrap(_where.column) + " " + _where.operator_ + " " + _value;
                }

                /**
                 * Compile a "where in" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_in(query_builder &_query, where_properties _where) {
                    if (!_where.values.empty()) {
                        return this->wrap(_where.column) + " in (" + this->parameterize(_where.values) + ")";
                    }
                    return "0 = 1";
                }

                /**
                 * Compile a "where not in" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_not_in(query_builder &_query, where_properties _where) {
                    if (!_where.values.empty()) {
                        return this->wrap(_where.column) + " not in (" + this->parameterize(_where.values) + ")";
                    }
                    return "1 = 1";
                }

                /**
                 * Compile a where in sub-select clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_in_sub(query_builder &_query, where_properties _where) {
                    return this->wrap(_where.column) + " in (" + this->compile_select(_where.query) + ")";
                }

                /**
                 * Compile a where not in sub-select clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_not_in_sub(query_builder &_query, where_properties _where) {
                    return this->wrap(_where.column) + " not in (" + this->compile_select(_where.query) + ")";
                }

                /**
                 * Compile a "where null" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_null(query_builder &_query, where_properties _where) {
                    return this->wrap(_where.column) + " is null";
                }

                /**
                 * Compile a "where not null" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_not_null(query_builder &_query, where_properties _where) {
                    return this->wrap(_where.column) + " is not null";
                }

                /**
                 * Compile a "between" where clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_between(query_builder &_query, where_properties _where) {
                    string _between = _where.not_ ? "not between" : "between";
                    return this->wrap(_where.column) + " " +  _between + " ? and ?";
                }

                /**
                 * Compile a "where date" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_date(query_builder &_query, where_properties _where) {
                    return this->date_based_where("date", _query, _where);
                }

                /**
                 * Compile a "where time" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_time(query_builder &_query, where_properties _where) {
                    return this->date_based_where("time", _query, _where);
                }

                /**
                 * Compile a "where day" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_day(query_builder &_query, where_properties _where) {
                    return this->date_based_where("day", _query, _where);
                }

                /**
                 * Compile a "where month" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_month(query_builder &_query, where_properties _where) {
                    return this->date_based_where("month", _query, _where);
                }

                /**
                 * Compile a "where year" clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_year(query_builder &_query, where_properties _where) {
                    return this->date_based_where("year", _query, _where);
                }

                /**
                 * Compile a date based where clause.
                 *
                 * @param  string  _type
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string date_based_where(string _type, query_builder &_query, where_properties _where) {
                    string _value = this->parameter(_where.value);
                    return _type + "("  + this->wrap(_where.column) + ") " + _where.operator_ + " " + _value;
                }

                /**
                 * Compile a where clause comparing two columns..
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_column(query_builder &_query, where_properties _where) {
                    return this->wrap(_where.first) + " " + _where.operator_ + " " + this->wrap(_where.second);
                }

                /**
                 * Compile a nested where clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_nested(query_builder &_query, where_properties _where) {
                    // Here we will calculate what portion of the string we need to remove. If this
                    // is a join clause query, we need to remove the "on" portion of the SQL and
                    // if it is a normal query we need to take the leading "where" of queries.
                    int _offset = 6;
                    string compiled_wheres = this->compile_wheres(_where.query);
                    return "(" + compiled_wheres.substr(_offset) + ")";
                }

                string where_nested(join_clause &_query, where_properties _where) {
                    // Here we will calculate what portion of the string we need to remove. If this
                    // is a join clause query, we need to remove the "on" portion of the SQL and
                    // if it is a normal query we need to take the leading "where" of queries.
                    int _offset = 3;
                    string compiled_wheres = this->compile_wheres(_where.query);
                    return "(" + compiled_wheres.substr(_offset) + ")";
                }

                /**
                 * Compile a where condition with a sub-select.
                 *
                 * @param  query_builder& _query
                 * @param  array   _where
                 * @return string
                 */
            protected:

                string where_sub(query_builder &_query, where_properties _where) {
                    string _select = this->compile_select(_where.query);
                    return this->wrap(_where.column) + " " + _where.operator_ + " (" + _select + ")";
                }

                /**
                 * Compile a where exists clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_exists(query_builder &_query, where_properties _where) {
                    return "exists (" + this->compile_select(_where.query) + ")";
                }

                /**
                 * Compile a where exists clause.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _where
                 * @return string
                 */
            protected:

                string where_not_exists(query_builder &_query, where_properties _where) {
                    return "not exists (" + this->compile_select(_where.query) + ")";
                }

                /**
                 * Compile the "group by" portions of the query.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _groups
                 * @return string
                 */
            protected:

                string compile_groups(query_builder &_query, vector<string> _groups) {
                    return "group by " + this->columnize(_groups);
                }

                /**
                 * Compile the "having" portions of the query.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _havings
                 * @return string
                 */
            protected:

                string compile_havings(query_builder &_query, vector<having_properties> _havings) {
                    vector<string> _having_strings;
                    _having_strings.reserve(_havings.size());
                    for (having_properties &having : _havings) {
                        _having_strings.emplace_back(this->compile_having(having));
                    }
                    string _sql = utils::implode(" ", _having_strings);
                    return "having " + this->remove_leading_boolean(_sql);
                }

                /**
                 * Compile a single having clause.
                 *
                 * @param  array   _having
                 * @return string
                 */
            protected:

                string compile_having(having_properties _having) {
                    // If the having clause is "raw", we can just return the clause straight away
                    // without doing any more processing on it. Otherwise, we will compile the
                    // clause into SQL based on the components that make it up from builder.
                    if (_having.type == "Raw") {
                        return _having.boolean + " " + _having.sql;
                    }

                    return this->compile_basic_having(_having);
                }

                /**
                 * Compile a basic having clause.
                 *
                 * @param  array   _having
                 * @return string
                 */
            protected:

                string compile_basic_having(having_properties _having) {
                    string _column = this->wrap(_having.column);

                    string _parameter = this->parameter(_having.value);

                    return _having.boolean + " " + _column +  " " + _having.operator_ + " " + _parameter;
                }

                /**
                 * Compile the "order by" portions of the query.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _orders
                 * @return string
                 */
            protected:

                string compile_orders(query_builder &_query, vector<order_properties> _orders) {
                    if (!_orders.empty()) {
                        return "order by " + utils::implode(", ", this->compile_orders_to_array(_query, _orders));
                    }
                    return "";
                }

                /**
                 * Compile the query orders to an array.
                 *
                 * @param  query_builder&
                 * @param  array  _orders
                 * @return array
                 */
            protected:

                vector<string> compile_orders_to_array(query_builder &_query, vector<order_properties> _orders) {
                    vector<string> order_strings;
                    for (order_properties& _order: _orders){
                        if (_order.sql.empty()){
                            order_strings.emplace_back(this->wrap(_order.column)+" " + _order.direction);
                        } else {
                            order_strings.emplace_back(_order.sql);
                        }
                    }
                    return order_strings;
                }

                /**
                 * Compile the random statement into SQL.
                 *
                 * @param  string  _seed
                 * @return string
                 */
            public:

                string compile_random(string _seed) {
                    return "RANDOM()";
                }

                /**
                 * Compile the "limit" portions of the query.
                 *
                 * @param  query_builder&  _query
                 * @param  int  _limit
                 * @return string
                 */
            protected:

                string compile_limit(query_builder &_query, int _limit) {
                    return "limit " + std::to_string(_limit);
                }

                /**
                 * Compile the "offset" portions of the query.
                 *
                 * @param  query_builder&  _query
                 * @param  int  _offset
                 * @return string
                 */
            protected:

                string compile_offset(query_builder &_query, int _offset) {
                    return "offset " + std::to_string(_offset);
                }

                /**
                 * Compile the "union" queries attached to the main query.
                 *
                 * @param  query_builder&  _query
                 * @return string
                 */
            protected:

                string compile_unions(query_builder &_query) {
                    string _sql = "";

                    for (union_properties& _union: _query._unions) {
                        _sql += this->compile_union(_union);
                    }

                    if (!_query._union_orders.empty()) {
                        _sql += " " + this->compile_orders(_query, _query._union_orders);
                    }

                    if (_query._union_limit > -1) {
                        _sql += " " + this->compile_limit(_query, _query._union_limit);
                    }

                    if (_query._union_offset > -1) {
                        _sql += " " + this->compile_offset(_query, _query._union_offset);
                    }

                    return utils::ltrim(_sql);
                }

                /**
                 * Compile a single union statement.
                 *
                 * @param  array  _union
                 * @return string
                 */
            protected:

                string compile_union(union_properties _union) {
                    string _conjuction = _union.all ? " union all " : " union ";
                    return _conjuction + _union.query.to_sql();
                }

                /**
                 * Compile an exists statement into SQL.
                 *
                 * @param  query_builder&  _query
                 * @return string
                 */
            public:

                string compile_exists(query_builder &_query) {
                    string _select = this->compile_select(_query);
                    return "select exists(" + _select + ") as " + this->wrap("exists");
                }

                /**
                 * Compile an insert statement into SQL.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _values
                 * @return string
                 */
            public:

                string compile_insert(query_builder &_query, vector<pair<string,string>> _value) {
                    return this->compile_insert(_query,{_value});
                }

                string compile_insert(query_builder &_query, vector<vector<pair<string,string>>> _values) {
                    // Essentially we will force every insert to be treated as a batch insert which
                    // simply makes creating the SQL easier for us since we can utilize the same
                    // basic routine regardless of an amount of records given to us to insert.
                    string _table = this->wrap_table(_query._from);

                    vector<string> array_keys;
                    for (pair<string,string> &insertion_pair : _values.front()) {
                        array_keys.emplace_back(insertion_pair.first);
                    }
                    string _columns = this->columnize(array_keys);

                    // We need to build a list of parameter place-holders of values that are bound
                    // to the query. Each insert should have the exact same amount of parameter
                    // bindings so we will loop through the record and parameterize them all.
                    vector<string> _parameters;
                    for (vector<pair<string,string>> &record : _values) {
                        _parameters.emplace_back( "(" + this->parameterize(record) + ")" );
                    }
                    return "insert into " + _table + "(" + _columns +") values "+utils::implode(", ",_parameters);
                }

                /**
                 * Compile an insert and get ID statement into SQL.
                 *
                 * @param  query_builder&  _query
                 * @param  array   _values
                 * @param  string  _sequence
                 * @return string
                 */
            public:

                string compile_insert_get_id(query_builder &_query, vector<pair<string,string>> _values, string _sequence) {
                    return this->compile_insert(_query, _values);
                }

                /**
                 * Compile an update statement into SQL.
                 *
                 * @param  query_builder&  _query
                 * @param  array  _values
                 * @return string
                 */
            public:

                string compile_update(query_builder &_query, vector<pair<string,string>> _values) {
                    string _table = this->wrap_table(_query._from);

                    // Each one of the columns in the update statements needs to be wrapped in the
                    // keyword identifiers, also a place-holder needs to be created for each of
                    // the values in the list of bindings so we can make the sets statements.
                    vector<string> _columns;
                    for (pair<string,string> &item : _values) {
                        string value = item.first;
                        string key = item.second;
                        _columns.emplace_back(this->wrap(key) + " = " + this->parameter(value));
                    }

                    // If the query has any "join" clauses, we will setup the joins on the builder
                    // and compile them so we can attach them to this update, as update queries
                    // can get join statements to attach to other tables when they"re needed.
                    string _joins = "";
                    if (!_query._joins.empty()) {
                        _joins = " " + this->compile_joins(_query, _query._joins);
                    }

                    // Of course, update queries may also be constrained by where clauses so we"ll
                    // need to compile the where clauses and attach it to the query so only the
                    // intended records are updated by the SQL statements we generate to run.
                    string _wheres = this->compile_wheres(_query);

                    return utils::trim("update " + _table + " " + _joins +" set "+utils::implode(", ",_columns) + " " + _wheres);
                }

                /**
                 * Prepare the bindings for an update statement.
                 *
                 * @param  array  _bindings
                 * @param  array  _values
                 * @return array
                 */
            public:

                vector<string> prepare_bindings_for_update(flat_map<string, vector<string>> _bindings, vector<string> _values) {
                    flat_map<string, vector<string>> _bindings_without_join = _bindings;
                    _bindings_without_join.erase("join");

                    vector<string> merged = _bindings["join"];
                    merged.insert(merged.end(),_values.begin(),_values.end());
                    vector<string> flatten_bindings = utils::flatten<flat_map<string, vector<string>>,std::string>(_bindings_without_join);
                    merged.insert(merged.end(),flatten_bindings.begin(),flatten_bindings.end());

                    return merged;
                }

                /**
                 * Compile a delete statement into SQL.
                 *
                 * @param  query_builder&  _query
                 * @return string
                 */
            public:

                string compile_delete(query_builder &_query) {
                    string _wheres = this->compile_wheres(_query);
                    return utils::trim("delete from " + this->wrap_table(_query._from) + " " + _wheres);
                }

                /**
                 * Compile a truncate table statement into SQL.
                 *
                 * @param  query_builder&  _query
                 * @return array
                 */
            public:

                vector<pair<string,vector<string>>> compile_truncate(query_builder &_query) {
                    return {{"truncate " + this->wrap_table(_query._from),{}}};
                }

                /**
                 * Compile the lock into SQL.
                 *
                 * @param  query_builder&  _query
                 * @param  bool|string  _value
                 * @return string
                 */
            protected:

                string compile_lock(query_builder &_query, string _value) {
                    return _value;
                }

                string compile_lock(query_builder &_query, bool _value) {
                    return "";
                }

                /**
                 * Determine if the grammar supports savepoints.
                 *
                 * @return bool
                 */
            public:

                bool supports_savepoints() {
                    return true;
                }

                /**
                 * Compile the SQL statement to define a savepoint.
                 *
                 * @param  string  _name
                 * @return string
                 */
            public:

                string compile_savepoint(string _name) {
                    return "SAVEPOINT " + _name;
                }

                /**
                 * Compile the SQL statement to execute a savepoint rollback.
                 *
                 * @param  string  _name
                 * @return string
                 */
            public:

                string compile_savepoint_roll_back(string _name) {
                    return "ROLLBACK TO SAVEPOINT " + _name;
                }

                /**
                 * Concatenate an array of segments, removing empties.
                 *
                 * @param  array   _segments
                 * @return string
                 */
            protected:

                string concatenate(vector<string> _segments) {
                    vector<string> concatenation;
                    concatenation.reserve(_segments.size());
                    for (auto &&_value : _segments) {
                        if (_value != ""){
                            concatenation.emplace_back(_value);
                        }
                    }
                    return utils::implode(" ",concatenation);
                }

                /**
                 * Remove the leading boolean from a statement.
                 *
                 * @param  string  _value
                 * @return string
                 */
            protected:

                string remove_leading_boolean(string _value) {
                    return utils::preg_replace("/and |or /i", "", _value, 1);
                }

                /**
                 * Get the grammar specific operators.
                 *
                 * @return array
                 */
            public:

                vector<string> get_operators() {
                    return this->_operators;
                }
        };
    }
}
#endif //WPP_QUERY_GRAMMAR_H
