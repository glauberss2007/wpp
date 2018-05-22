//
// Created by Alan de Freitas on 20/11/2017.
//

#ifndef WPP_SCHEMA_GRAMMAR_H
#define WPP_SCHEMA_GRAMMAR_H

#include "base_grammar.h"

namespace wpp {
    namespace db {
        class schema_grammar
                : base_grammar {
                /**
                 * If this grammar supports schema changes wrapped in a transaction.
                 *
                 * @var bool
                 */
            protected:
                bool _transactions = false;

                /**
                 * Compile a rename column command.
                 *
                 * @param  blueprint  _blueprint
                 * @param  Fluent  _command
                 * @param  Connection  _connection
                 * @return array
                 */
            public:

                // This function requires Doctrine in PHP
                //function compile_rename_column(blueprint _blueprint, command _command, db::connection _connection) {
                //    return RenameColumn::compile(_this, _blueprint, _command, _connection);
                //}

                /**
                 * Compile a change column command into a series of SQL statements.
                 *
                 * @param  blueprint  _blueprint
                 * @param  Fluent  _command
                 * @param  Connection _connection
                 * @return array
                 *
                 * @throws \RuntimeException
                 */
            public:

                // This function requires Doctrine in PHP
                //function compile_change(blueprint _blueprint, Fluent _command, Connection _connection) {
                //    return ChangeColumn::compile(_this, _blueprint, _command, _connection);
                //}

                /**
                 * Compile a foreign key command.
                 *
                 * @param  blueprint  _blueprint
                 * @param  Fluent  _command
                 * @return string
                 */
            public:

                string compile_foreign(blueprint _blueprint, blueprint::command _command) {
                    // We need to prepare several of the elements of the foreign key definition
                    // before we can create the SQL, such as wrapping the tables and convert
                    // an array of columns to comma-delimited strings for the SQL queries.
                    string _sql = "alter table " + this->wrap_table(_blueprint) +" add constraint "+this->wrap(_command.index)+" ";

                    // Once we have the initial portion of the SQL statement we will add on the
                    // key name, table name, and referenced columns. These will complete the
                    // main portion of the SQL statement and this SQL will almost be done.
                    _sql += "foreign key ("+this->columnize(_command.columns)+") references "+this->wrap_table(_command.on)+" "+this->columnize(_command.references)+"";

                    // Once we have the basic foreign key creation statement constructed we can
                    // build out the syntax for what should happen on an update or delete of
                    // the affected columns, which will get something like "cascade", etc.
                    if (!_command.on_delete.empty()) {
                        _sql += " on delete " + _command.on_delete;
                    }

                    if (!_command.on_update.empty()) {
                        _sql += " on update " + _command.on_update;
                    }

                    return _sql;
                }

                /**
                 * Compile the blueprint's column definitions.
                 *
                 * @param  blueprint _blueprint
                 * @return array
                 */
            protected:

                vector<string> get_columns(blueprint _blueprint) {
                    vector<string> _columns = {};
                    for (blueprint::column &_column: _blueprint.get_added_columns()){
                        // Each of the column types have their own compiler functions which are tasked
                        // with turning the column definition into its SQL format for this platform
                        // used by the connection. The column's modifiers are compiled and added.
                        string _sql = this->wrap(_column.name) + " " + this->get_type(_column);

                        _columns.push_back(this->add_modifiers(_sql, _blueprint, _column));
                    }


                    return _columns;
                }

                /**
                 * Get the SQL for the column data type.
                 *
                 * @param  Fluent  _column
                 * @return string
                 */
            protected:

                string get_type(blueprint::column _column) {
                    return _column.type;
                }

                /**
                 * Add the column modifiers to the definition.
                 *
                 * @param  string  _sql
                 * @param  blueprint  _blueprint
                 * @param  Fluent  _column
                 * @return string
                 */
            protected:

                string add_modifiers(string _sql, blueprint _blueprint, blueprint::column _column) {
                    //for (auto _modifier: this->_modifiers) {
                    //if (method_exists(_this, _method = "modify{_modifier}")) {
                    //    _sql += this->{ _method }(_blueprint, _column);
                    //}
                    //}

                    return _sql;
                }

                /**
                 * Get the primary key command if it exists on the blueprint.
                 *
                 * @param  blueprint  _blueprint
                 * @param  string  _name
                 * @return Fluent|null
                 */
            protected:

                blueprint::command get_command_by_name(blueprint _blueprint, string _name) {
                    vector<blueprint::command> _commands = this->get_commands_by_name(_blueprint, _name);

                    if (!_commands.empty()) {
                        return _commands[0];
                    } else {
                        return blueprint::command();
                    }

                }

                /**
                 * Get all of the commands with a given name.
                 *
                 * @param  blueprint  _blueprint
                 * @param  string  _name
                 * @return array
                 */
            protected:

                vector<blueprint::command> get_commands_by_name(blueprint _blueprint, string _name) {
                    vector<blueprint::command> commands;
                    auto iter = std::remove_if(commands.begin(), commands.end(),[&_name](blueprint::command& _value){
                        return _value.name == _name;
                    });
                    commands.erase(iter, commands.end());
                    return commands;
                }

                /**
                 * Add a prefix to an array of values.
                 *
                 * @param  string  _prefix
                 * @param  array   _values
                 * @return array
                 */
            public:
                vector<string> prefix_array(string _prefix, vector<string> _values) {
                    return utils::array_map([&_prefix](string& _value){
                        return _prefix + " "  + _value;
                    }, _values);
                }

                /**
                 * Wrap a table in keyword identifiers.
                 *
                 * @param  mixed   _table
                 * @return string
                 */
            public:
                string wrap_table(string _table) {
                    return base_grammar::wrap_table(_table);
                }

                string wrap_table(blueprint _table) {
                    return base_grammar::wrap_table(_table.get_table());
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
                    return base_grammar::wrap(_value, _prefix_alias);
                }

                /**
                 * Format a value so that it can be used in "default" clauses.
                 *
                 * @param  mixed   _value
                 * @return string
                 */
            protected:

                string get_default_value(string _value) {
                    return _value;
                }

                string get_default_value(bool _value) {
                    return "'" + std::to_string((int) _value) + "'";
                }

                template<typename integer>
                string get_default_value(integer _value) {
                    return "'" + to_string(_value) + "'";
                }

                /**
                 * Create an empty Doctrine DBAL TableDiff from the blueprint.
                 *
                 * @param  blueprint  _blueprint
                 * @param  \Doctrine\DBAL\Schema\AbstractSchemaManager  _schema
                 * @return \Doctrine\DBAL\Schema\TableDiff
                 */
            public:

                //function get_doctrine_table_diff(blueprint _blueprint, SchemaManager _schema) {
                //    _table = this->get_table_prefix()._blueprint->get_table();
                //
                //    return tap(new TableDiff(_table), function(_table_diff)
                //    use(_schema, _table)
                //    {
                //        _table_diff->from_table = _schema->list_table_details(_table);
                //    });
                //}

                /**
                 * Check if this grammar supports schema changes wrapped in a transaction.
                 *
                 * @return bool
                 */
            public:

                bool supports_schema_transactions() {
                    return this->_transactions;
                }
        };
    }
}

#endif //WPP_SCHEMA_GRAMMAR_H
