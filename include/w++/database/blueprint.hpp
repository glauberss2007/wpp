//
// Created by Alan de Freitas on 20/11/2017.
//

#ifndef WPP_BLUEPRINT_HPP
#define WPP_BLUEPRINT_HPP

namespace wpp {
    namespace db {
        void blueprint::build(wpp::db::connection& connection, wpp::db::schema_grammar grammar) {
            for (std::string& statement: this->to_sql(connection, grammar)) {
                connection.statement(statement);
            }
        }

        vector<string> blueprint::to_sql(wpp::db::connection& connection, wpp::db::schema_grammar grammar) {
            this->add_implied_commands();

            vector<string> statements = {};

            // Each type of command has a corresponding compiler function on the schema
            // grammar which is used to build the necessary SQL statements to build
            // the blueprint element, so we"ll just call that compilers function.
            for (command& _command: this->_commands) {
                if (_command.name == "rename_column"){
                    string sql = grammar.compile_rename_column(*this, _command, connection);
                    statements.push_back(sql);
                } else if (_command.name == "change") {
                    string sql = grammar.compile_change(*this, _command, connection);
                    statements.push_back(sql);
                } else if (_command.name == "foreign") {
                    string sql = grammar.compile_foreign(*this, _command, connection);
                    statements.push_back(sql);
                }
            }

            return statements;
        }

        column blueprint::character(column, int length = -1)
        {
            length = length > 0 ? length : query_builder::default_string_length;

            return this->add_column("char", column, {{"length",length}});
        }

        column blueprint::string_(string column, int length = -1) {
            length = length > 0 ? length : query_builder::default_string_length;

            return this->add_column("string", column, compact("length"));
        }



    }
}

#endif //WPP_BLUEPRINT_HPP
