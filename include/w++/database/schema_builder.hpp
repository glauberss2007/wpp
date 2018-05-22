//
// Created by Alan de Freitas on 23/11/2017.
//

#ifndef WPP_SCHEMA_BUILDER_HPP
#define WPP_SCHEMA_BUILDER_HPP

namespace wpp {
    namespace db {
        schema_builder::schema_builder(wpp::db::connection& connection) : _connection(connection) {
                this->_grammar = connection->get_schema_grammar();
        }

        bool schema_builder::has_table(string table) {
            table = this->_connection->get_table_prefix() + table;
            wpp::db::result select = this->_connection.select(this->_grammar.compile_table_exists(),{table});
            return !select.empty();
        }

        string schema_builder::get_column_type(string table, string column) {
            table = this->_connection->get_table_prefix() + table;
            return this->_connection->get_doctrine_column(table, column)->get_type()->get_name();
        }

        vector<string> schema_builder::get_column_listing(string table) {
            table = this->_connection.get_table_prefix() + table;

            wpp::db::result results = this->_connection.select(this->_grammar.compile_column_listing(table));

            return this->_connection->get_post_processor()->process_column_listing(results);
        }

        bool schema_builder::enable_foreign_key_constraints() {
            return this->_connection.statement(this->_grammar.compile_enable_foreign_key_constraints());
        }

        bool schema_builder::disable_foreign_key_constraints() {
            return this->_connection.statement(this->_grammar.compile_disable_foreign_key_constraints());
        }

        self_t& schema_builder::set_connection(wpp::db::connection& connection) {
            this->_connection = connection;

            return *this;
        }




    }
}

#endif //WPP_SCHEMA_BUILDER_HPP
