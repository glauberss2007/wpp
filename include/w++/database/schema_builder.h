//
// Created by Alan de Freitas on 20/11/2017.
//

#ifndef WPP_SCHEMA_BUILDER_H
#define WPP_SCHEMA_BUILDER_H

#include "datatype_alias.h"
#include "blueprint.h"
#include "schema_grammar.h"

namespace wpp {
    namespace db {
        class connection;

        class schema_builder {
            public:
                using self_t = schema_builder;
                /**
                 * The database connection instance.
                 *
                 * @var wpp::db::connection
                 */
            protected:
                db::connection &_connection;

                /**
                 * The schema grammar instance.
                 *
                 * @var Grammar
                 */
            protected:
                schema_grammar _grammar;

                /**
                 * The Blueprint resolver callback.
                 *
                 * @var \Closure
                 */
            protected:
                function<blueprint(string,function<void(blueprint&)>)> _resolver;

                /**
                 * The default string length for migrations.
                 *
                 * @var int
                 */
            public:
                static int _default_string_length;

                /**
                 * Create a new database Schema manager.
                 *
                 * @param  wpp::db::connection  connection
                 * @return void
                 */
            public:
                schema_builder(wpp::db::connection& connection);

                /**
                 * Set the default string length for migrations.
                 *
                 * @param  int  length
                 * @return void
                 */
            public:
                static void default_string_length(size_t length) {
                    _default_string_length = length;
                }

                /**
                 * Determine if the given table exists.
                 *
                 * @param  string  table
                 * @return bool
                 */
            public:
                bool has_table(string table);

                /**
                 * Determine if the given table has a given column.
                 *
                 * @param  string  table
                 * @param  string  column
                 * @return bool
                 */
            public:
                bool has_column(string table, string column) {
                    return utils::in_array(utils::strtolower(column), utils::array_map(utils::strtolower, this->get_column_listing(table)));
                }

                /**
                 * Determine if the given table has given columns.
                 *
                 * @param  string  table
                 * @param  array   columns
                 * @return bool
                 */
            public:
                bool has_columns(string table, vector<string> columns) {
                    vector<string> table_columns = utils::array_map(utils::strtolower, this->get_column_listing(table));

                    for (string& col: columns) {
                        if (!utils::in_array(utils::strtolower(col), table_columns)) {
                            return false;
                        }
                    }

                    return true;
                }

                /**
                 * Get the data type for the given column name.
                 *
                 * @param  string  table
                 * @param  string  column
                 * @return string
                 */
            public:
                string get_column_type(string table, string column);

                /**
                 * Get the column listing for a given table.
                 *
                 * @param  string  table
                 * @return array
                 */
            public:
                vector<string> get_column_listing(string table);

                /**
                 * Modify a table on the schema.
                 *
                 * @param  string    table
                 * @param  \Closure  callback
                 * @return void
                 */
            public:
                template<typename Closure>
                void table(string table, Closure callback) {
                    this->build(this->create_blueprint(table, callback));
                }

                /**
                 * Create a new table on the schema.
                 *
                 * @param  string    table
                 * @param  \Closure  callback
                 * @return void
                 */
            public:
                template<typename Closure>
                void create(string table, Closure callback) {
                    blueprint t = this->create_blueprint(table);
                    t.create();
                    callback(t);
                    this->build(t);
                }

                /**
                 * Drop a table from the schema.
                 *
                 * @param  string  table
                 * @return void
                 */
            public:
                void drop(string table) {
                    blueprint t = this->create_blueprint(table);
                    t.drop();
                    this->build(t);
                }

                /**
                 * Drop a table from the schema if it exists.
                 *
                 * @param  string  table
                 * @return void
                 */
            public:
                void drop_if_exists(string table) {
                    blueprint t = this->create_blueprint(table);
                    t.drop_if_exists();
                    this->build(t);
                }

                /**
                 * Rename a table on the schema.
                 *
                 * @param  string  from
                 * @param  string  to
                 * @return void
                 */
            public:
                void rename(string from, string to) {
                    blueprint t = this->create_blueprint(from);
                    t.rename(to);
                    this->build(t);
                }

                /**
                 * Enable foreign key constraints.
                 *
                 * @return bool
                 */
            public:
                bool enable_foreign_key_constraints();

                /**
                 * Disable foreign key constraints.
                 *
                 * @return bool
                 */
            public:
                bool disable_foreign_key_constraints();

                /**
                 * Execute the blueprint to build / modify the table.
                 *
                 * @param  Blueprint  blueprint
                 * @return void
                 */
            protected:
                void build(blueprint _blueprint) {
                    _blueprint.build(this->_connection, this->_grammar);
                }

                /**
                 * Create a new command set with a Closure.
                 *
                 * @param  string  table
                 * @param  \Closure|null  callback
                 * @return Blueprint
                 */
            protected:
                template<typename Closure>
                blueprint create_blueprint(string table, Closure callback) {
                    if (this->_resolver) {
                        return this->_resolver(table, callback);
                    }

                    return blueprint(table, callback);
                }

                blueprint create_blueprint(string table) {
                    if (this->_resolver) {
                        return this->_resolver(table,nullptr);
                    }

                    return blueprint(table);
                }

                /**
                 * Get the database connection instance.
                 *
                 * @return wpp::db::connection
                 */
            public:
                wpp::db::connection& get_connection() {
                    return this->_connection;
                }

                /**
                 * Set the database connection instance.
                 *
                 * @param  wpp::db::connection  connection
                 * @return this
                 */
            public:
                self_t& set_connection(wpp::db::connection& connection);

                /**
                 * Set the Schema Blueprint resolver callback.
                 *
                 * @param  \Closure  resolver
                 * @return void
                 */
            public:
                template<typename Closure>
                void blueprint_resolver(Closure resolver) {
                    this->_resolver = resolver;
                }
        };

        int schema_builder::_default_string_length = 255;

    }
}

#endif //WPP_SCHEMA_BUILDER_H
