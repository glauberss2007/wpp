//
// Created by Alan de Freitas on 16/11/2017.
//

#ifndef WPP_DB_CONNECTOR_H
#define WPP_DB_CONNECTOR_H

#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <ctime>

#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>

#include <pqxx/pqxx>

#include "datatype_alias.h"
#include "aux_data_types.h"
#include "data_object.h"
#include "query_grammar.h"

namespace wpp {

    namespace db {

        class connection {
            public:
                using self_t = connection;

                connection(flat_map<string, string> parameters) {
                    string connexion_data;
                    if (parameters.count("db_name")) {
                        connexion_data += "dbname=" + parameters["db_name"];
                        this->_database = parameters["db_name"];
                    } else {
                        _error = "The database name has to be specified";
                        return;
                    }
                    if (parameters.count("user")) {
                        connexion_data += " user=" + parameters["user"];
                    }
                    if (parameters.count("password")) {
                        connexion_data += " password=" + parameters["password"];
                    }
                    if (parameters.count("hostaddr")) {
                        connexion_data += " hostaddr=" + parameters["hostaddr"];
                    } else {
                        connexion_data += " hostaddr=127.0.0.1";
                    }
                    if (parameters.count("port")) {
                        connexion_data += " port=" + parameters["port"];
                    } else {
                        connexion_data += " port=5432";
                    }

                    _pdo.reset(new data_object(connexion_data));

                    if (!_pdo->is_open()) {
                        if (parameters.count("data_folder")) {
                            std::thread t([&parameters]() {
                                string command = string("postgres -D ") + parameters["data_folder"];
                                std::system(command.data());
                                std::this_thread::sleep_for(std::chrono::seconds(3));
                            });
                            _pdo.reset(new data_object(connexion_data));
                        }
                        if (!_pdo->is_open()) {
                            _error = "Can't open the database";
                            return;
                        }
                    }

                    if (parameters.count("table_prefix")) {
                        this->_table_prefix = parameters["port"];
                    }

                    this->_config = parameters;

                    // database abstractions
                    this->use_default_query_grammar();
                    this->use_default_post_processor();

                };

                ~connection() {
                    _pdo->disconnect();
                }

                string dbname() {
                    return this->_database;
                }

                bool is_open() {
                    return (_pdo->is_open() && _pdo->is_open());
                }

                bool error() {
                    return !this->_error.empty();
                }

                string error_string() {
                    return this->_error;
                }

                //wpp::db::result statement(string sql) {
                //    this->_error = "";
                //    try {
                //        wpp::work w(*_pdo);
                //        std::unique_ptr<wpp::db::invocation> w_invocation(new wpp::db::invocation(w.prepared(sql)));
                //        if (!w_invocation->exists()) {
                //            this->prepare(sql, sql);
                //            w_invocation.reset(new wpp::db::invocation(w.prepared(sql)));
                //        }
                //        apply_invocation_arguments(w_invocation, args...);
                //        wpp::db::result r = w_invocation->exec();
                //        w.commit();
                //        return r;
                //    } catch (const std::exception &e) {
                //        // _error = e.what();
                //    }
                //    return wpp::db::result();
                //}

                //template<typename... Args>
                //wpp::db::result statement(string sql, Args... args) {
                //    this->_error = "";
                //    try {
                //        wpp::db::work w(*_pdo);
                //        std::unique_ptr<wpp::db::invocation> w_invocation(new wpp::db::invocation(w.prepared(sql)));
                //        if (!w_invocation->exists()) {
                //            this->prepare(sql, sql);
                //            w_invocation.reset(new wpp::db::invocation(w.prepared(sql)));
                //        }
                //        apply_invocation_arguments(w_invocation, args...);
                //        wpp::db::result r = w_invocation->exec();
                //        w.commit();
                //        return r;
                //    } catch (const std::exception &e) {
                //        _error = e.what();
                //    }
                //    return wpp::db::result();
                //}

                //wpp::db::result select(string query) {
                //    return this->statement(query);
                //}
                //
                //// DB::insert('insert into users (id, name) values (?, ?)', [1, 'Dayle']);
                //self_t &insert(string query) {
                //    this->statement(query);
                //    return *this;
                //}
                //
                //// _affected = DB::update('update users set votes = 100 where name = ?', ['John']);
                //self_t &update(string query) {
                //    this->statement(query);
                //    return *this;
                //}
                //
                //// _deleted = DB::delete('delete from users');
                //self_t &delete_entry() {
                //    this->statement(query);
                //    return *this;
                //}

                self_t &prepare(string name, string query) {
                    _pdo->prepare(name, query);
                    return *this;
                }

                //template<typename... Args>
                //wpp::db::result run(string name, Args... args) {
                //    this->_error = "";
                //    try {
                //        wpp::db::work w(*_pdo);
                //        wpp::db::invocation w_invocation = w.prepared(name);
                //        apply_invocation_arguments(w_invocation, args...);
                //        wpp::db::result r = w_invocation.exec();
                //        w.commit();
                //        return r;
                //    } catch (const std::exception &e) {
                //        // _error = e.what();
                //        return wpp::db::result();
                //    }
                //
                //}

                // Set the query grammar to the default implementation.
                self_t &use_default_query_grammar() {
                    this->_query_grammar = this->get_default_query_grammar();
                    return *this;
                }

                // Set the schema grammar to the default implementation.
                self_t &use_default_schema_grammar() {
                    this->_schema_grammar.reset(new schema_grammar(this->get_default_schema_grammar()));
                    return *this;
                }


                // Set the query post processor to the default implementation.
                self_t &use_default_post_processor() {
                    this->_post_processor = this->get_default_post_processor();
                    return *this;
                }

                // Get a schema builder instance for the connection.
                schema_builder get_schema_builder() {
                    if (!this->_schema_grammar) {
                        this->use_default_schema_grammar();
                    }

                    return wpp::db::schema_builder(*this);
                }

                // Begin a fluent query against a database table.
                db::query_builder table(string table) {
                    return this->query().from(table);
                }

                // Get a new query builder instance.
                db::query_builder query() {
                    std::shared_ptr<query_grammar> qg(new query_grammar(this->get_query_grammar()));
                    std::shared_ptr<processor> pp(new processor(this->get_post_processor()));
                    return db::query_builder(*this, qg, pp);
                }

                // Run a select statement and return a single result.
                wpp::db::row
                select_one(string query, vector<pair<string, string>> bindings = {}, bool use_read_pdo = true) {
                    wpp::db::result records = this->select(query, bindings, use_read_pdo);
                    return utils::array_shift(records);
                }

                // Run a select statement against the database.
                wpp::db::result select_from_write_connection(string query, vector<pair<string, string>> bindings = {}) {
                    return this->select(query, bindings, false);
                }

                // Run a select statement against the database.
                wpp::db::result select(string query, vector<pair<string, string>> bindings = {}, bool use_read_pdo = true) {
                    return this->run(query, bindings, [&use_read_pdo, this](string query, vector<pair<string, string>> bindings) {
                        if (this->pretending()) {
                            return wpp::db::result();
                        }
                        data_object::statement statement = this->prepared(
                                this->get_pdo_for_select(use_read_pdo)->prepare(query));

                        this->bind_values(statement, this->prepare_bindings(bindings));

                        statement->execute();

                        return statement->fetch_all();
                    });
                }

                // Run a select statement against the database and returns a generator.
                generator
                cursor(string query, vector<pair<string, string>> bindings = {}, bool use_read_pdo = true) {
                    data_object::statement statement = this->run(query, bindings, [use_read_pdo, this](string query, bindings) {
                        if (this->pretending()) {
                            return {};
                        }

                        // First we will create a statement for the query.
                        // Then, we will set the fetch mode and prepare the bindings for the query.
                        // Once that's done we will be ready to execute the query against the database and return the cursor.
                        data_object::statement statement = this->prepared(
                                this->get_pdo_for_select(use_read_pdo)->prepare(query));

                        this->bind_values(statement, this->prepare_bindings(bindings));

                        // Next, we'll execute the query against the database and return the statement
                        // so we can return the cursor. The cursor will use a PHP generator to give
                        // back one row at a time without using a bunch of memory to render them.
                        statement->execute();

                        return statement;
                    });

                    while (wpp::db::row record = statement->fetch()) {
                        yield record;
                    }
                }


                // Run an insert statement against the database.
                bool insert(string query, vector<pair<string, string>> bindings = {}) {
                    return this->statement(query, bindings);
                }

                // Run an update statement against the database.
                int update(string query, vector<pair<string, string>> bindings = {}) {
                    return this->affecting_statement(query, bindings);
                }

                // Run a delete statement against the database.
                int delete_entry(string query, vector<pair<string, string>> bindings = {}) {
                    return this->affecting_statement(query, bindings);
                }

                // Execute an SQL statement and return the boolean result.
                bool statement(string query, vector<pair<string, string>> bindings = {}) {
                    return this->run(query, bindings, [this](string query, vector<pair<string, string>> bindings) {
                        if (this->pretending()) {
                            return true;
                        }

                        data_object::statement statement = this->get_pdo()->prepare(query);

                        this->bind_values(statement, this->prepare_bindings(bindings));

                        return statement->execute();
                    });
                }

                // Run an SQL statement and get the number of rows affected.
                int affecting_statement(string query, vector<pair<string, string>> bindings = {}) {
                    return this->run(query, bindings, [this](string query, vector<pair<string, string>> bindings) {
                        if (this->pretending()) {
                            return 0;
                        }

                        // For update or delete statements, we want to get the number of rows affected
                        // by the statement and return that back to the developer. We'll first need
                        // to execute the statement and then we'll use data_object to fetch the affected.
                        data_object::statement statement = this->get_pdo()->prepare(query);

                        this->bind_values(statement, this->prepare_bindings(bindings));

                        statement->execute();

                        return statement->row_count();
                    });
                }

                // Run a raw, unprepared query against the data_object connection.
                bool unprepared(string query) {
                    return this->run(query, {}, [this](string query) {
                        if (this->pretending()) {
                            return true;
                        }

                        return (bool) this->get_pdo()->exec(query);
                    });
                }

                // Execute the given callback in "dry run" mode.
                vector<string> pretend(function<query_log(connection &)> callback) {
                    return this->with_freshQueryLog([callback]() {
                        this->_pretending = true;

                        // Basically to make the database connection "pretend", we will just return
                        // the default values for all the query methods, then we will return a
                        // vector<string> of queries that were "executed" within the Closure callback.
                        callback(*this);

                        this->_pretending = false;

                        return this->_query_log;
                    });
                }


                // Bind values to their parameters in the given statement.
                self_t &bind_values(data_object::statement statement, vector<pair<string, string>> bindings) {
                    for (pair<string, string> &binding: bindings) {
                        string key = bindings.first;
                        string value = bindings.second;
                        statement->bind_value(is_string(key) ? key : key + 1, value,
                                              is_int(value) ? data_object::PARAM_INT
                                                            : data_object::PARAM_STR);
                    }
                }

                // Prepare the query bindings for execution.
                template<typename MIXED>
                vector<pair<string, MIXED>> prepare_bindings(vector<pair<string, MIXED>> bindings) {
                    grammar = this->get_query_grammar();
                    return bindings;
                }

                template<typename MIXED>
                vector<pair<string, MIXED>> prepare_bindings(vector<pair<string, std::time_t>> bindings) {
                    grammar = this->get_query_grammar();
                    vector<pair<string, string>> str_bindings;

                    for (pair<string, std::time_t> &binding: bindings) {
                        string key = bindings.first;
                        std::time_t value = bindings.second;
                        str_bindings[key] = value.format(grammar->get_dateFormat());
                    }
                    return str_bindings;
                }


                // Log a query in the connection's query log.
                template<typename MIXED>
                void log_query(string query, vector<pair<string, MIXED>> bindings, double time = 0) {
                    if (this->_logging_queries) {
                        this->_query_log.push_back({{"query",    query},
                                                    {"bindings", bindings},
                                                    {"time",     time}});
                    }
                }

                // Get a new raw query expression.
                string raw(string value) {
                    return string(value);
                }

                // Get the current data_object connection.
                data_object get_pdo() {
                    if (this->_pdo_closure) {
                        return this->_pdo = _pdo_closure();
                    }

                    return this->_pdo;
                }

                //Get the current data_object connection used for reading.
                data_object get_read_pdo() {
                    if (this->_transactions >= 1) {
                        return this->get_pdo();
                    }

                    if (this->_read_pdo_closure) {
                        return this->_read_pdo = _read_pdo_closure();
                    }

                    return this->_read_pdo ? this->_read_pdo : this->get_pdo();
                }

                // Set the data_object connection.
                self_t &set_pdo(data_object pdo) {
                    this->_transactions = 0;
                    this->_pdo = pdo;
                    this->_pdo_closure = nullptr;
                    return *this;
                }

                // Set the data_object connection used for reading.
                self_t &set_readPdo(data_object pdo) {
                    this->_read_pdo = pdo;
                    this->_read_pdo_closure = nullptr;
                    return *this;
                }

                // Set the reconnect instance on the connection.
                template<typename callable>
                self_t &set_reconnection(callable reconnection) {
                    this->_reconnection = reconnection;
                    return *this;
                }

                // Get the database connection name.
                string get_name() {
                    return this->get_config('name');
                }

                // Get an option from the configuration options.
                string get_config(string option = "") {
                    return this->_config[option];
                }

                // Get the data_object driver name.
                string get_driver_name() {
                    return this->get_config('driver');
                }

                // Get the query grammar used by the connection.
                query_grammar get_query_grammar() {
                    return this->_query_grammar;
                }

                // Set the query grammar used by the connection.
                void set_query_grammar(query_grammar g) {
                    this->_query_grammar = g;
                }

                // Get the schema grammar used by the connection.
                schema_grammar get_schema_grammar() {
                    return this->_schema_grammar;
                }

                // Set the schema grammar used by the connection.
                self_t &set_schema_grammar(schema_grammar g) {
                    this->_schema_grammar = g;
                }

                // Get the query post processor used by the connection.
                processor get_post_processor() {
                    return this->_post_processor;
                }

                // Set the query post processor used by the connection.
                void set_post_processor(processor p) {
                    this->_post_processor = p;
                }

                // Get the event dispatcher used by the connection.
                dispatcher get_eventdispatcher() {
                    return this->_events;
                }

                // Set the event dispatcher instance on the connection.
                void set_eventdispatcher(dispatcher events) {
                    this->_events = events;
                }

                // Determine if the connection in a "dry run".
                bool pretending() {
                    return this->_pretending;
                }

                // Get the connection query log.
                vector<string> get_queryLog() {
                    return this->_query_log;
                }

                // Clear the query log.
                void flush_query_log() {
                    this->_query_log.clear();
                }

                // Enable the query log on the connection.
                void enable_query_log() {
                    this->_logging_queries = true;
                }

                // Disable the query log on the connection.
                void disable_query_log() {
                    this->_logging_queries = false;
                }

                // Determine whether we're logging queries.
                bool logging() {
                    return this->_logging_queries;
                }

                // Get the name of the connected database.
                string get_database_name() {
                    return this->_database;
                }

                // Set the name of the connected database.
                string set_database_name(string database) {
                    this->_database = database;
                }

                // Get the table prefix for the connection.
                string get_tablePrefix() {
                    return this->_table_prefix;
                }

                // Set the table prefix in use by the connection.
                void set_table_prefix(string prefix) {
                    this->_table_prefix = prefix;

                    this->get_query_grammar()->set_table_prefix(prefix);
                }

                // Set the table prefix and return the grammar.
                template<typename grammar>
                grammar with_table_prefix(grammar g) {
                    g.set_table_prefix(this->_table_prefix);
                    return g;
                }

                // Register a connection resolver.
                template<typename Closure>
                static void resolver_for(string driver, Closure callback) {
                    ::resolvers[driver] = callback;
                }

                // Get the connection resolver for the given driver.
                template<typename resolver>
                static resolver get_resolver(string driver) {
                    if (_resolvers.count(driver)) {
                        _resolvers[driver];
                    } else {
                        return nullptr;
                    }
                }

            protected:

                // Get the elapsed time since a given starting point.
                double get_elapsedTime(int start) {
                    return utils::round((utils::microtime(true) - start) * 1000, 2);
                }

                // Handle a query exception.
                template<typename Closure>
                wpp::db::result handle_query_exception(std::exception e, string query, vector<string> bindings, Closure callback) {
                    if (this->_transactions >= 1) {
                        throw e;
                    }

                    return this->try_again_if_caused_by_lost_connection(
                            e, query, bindings, callback
                    );
                }

                // Handle a query exception that occurred during query execution.
                template<typename Closure, typename ClosureResult>
                ClosureResult
                try_again_if_caused_by_lost_connection(string exception, string query, flat_map<string,string> bindings, Closure callback) {
                    if (this->caused_byLostConnection(e->get_previous())) {
                        this->reconnect();
                        return this->run_query_callback(query, bindings, callback);
                    }

                    throw exception;
                }

                // Reconnect to the database.
                void reconnect() {
                    if (is_callable(this->_reconnection)) {
                        return this->_reconnection(*this);
                    }

                    throw new LogicException("Lost connection and no reconnection available.");
                }

                // Reconnect to the database if a data_object connection is missing.
                self_t &reconnect_if_missing_connection() {
                    if (is_null(this->_pdo)) {
                        this->reconnect();
                    }
                }

                // Disconnect from the underlying data_object connection.
                void disconnect() {
                    this->set_pdo(null)->set_readPdo(null);
                }

                // Register a database query listener with the connection.
                template<typename Closure>
                void listen(Closure callback) {
                    if (this->_events) {
                        this->_events->listen("Query Executed", callback);
                    }
                }

                // Fire an event for this connection.
                void fire_connectionEvent(string event) {
                    if (!isset(this->_events)) {
                        return;
                    }

                    if (event == "began_transaction") {
                        return this->_events->dispatch("Transaction Beginning");
                    } else if (event == "committed") {
                        return this->_events->dispatch("Transaction Committed");
                    } else if (event == "rolling_back") {
                        return this->_events->dispatch("Transaction RolledBack");
                    }
                }

                // Fire the given event if possible.
                template<typename MIXED>
                void event(MIXED event) {
                    if (isset(this->_events)) {
                        this->_events->dispatch(event);
                    }
                }

                // Run a SQL statement and log its execution context.
                template<typename Closure>
                wpp::db::result run(string query, vector<string> bindings, Closure callback) {
                    this->reconnect_if_missing_connection();

                    double start = microtime(true);

                    wpp::db::result _result;

                    // Here we will run this query. If an exception occurs we'll determine if it was
                    // caused by a connection that has been lost. If that is the cause, we'll try
                    // to re-establish connection and re-run the query with a fresh connection.
                    try {
                        _result = this->run_query_callback(query, bindings, callback);
                    } catch (string e) {
                        _result = this->handle_query_exception(e, query, bindings, callback);
                    }

                    // Once we have run the query we will calculate the time that it took to run and
                    // then log the query, bindings, and execution time so we will report them on
                    // the event that the developer needs them. We'll log time in milliseconds.
                    this->log_query(query, bindings, this->get_elapsedTime(start));

                    return _result;
                }

                // Run a SQL statement.
                template<typename Closure>
                wpp::db::result run_query_callback(string query, vector<string> bindings, Closure callback) {
                    // To execute the statement, we'll simply call the callback, which will actually
                    // run the SQL against the data_object connection. Then we can calculate the time it
                    // took to execute and log the query SQL, bindings and time in our memory.
                    try {
                        result = callback(query, bindings);
                    }
                    // If an exception occurs when attempting to run a query, we'll format the error
                    // message to include the bindings with SQL, which will make this exception a
                    // lot more helpful to the developer instead of just the database's errors.
                    catch (string e) {
                        _error = e;
                    }

                    return result;
                }

                // Execute the given callback in "dry run" mode.
                template<typename Closure>
                vector<string> with_freshQueryLog(Closure callback) {
                    bool logging_queries = this->_logging_queries;

                    // First we will back up the value of the logging queries property and then
                    // we'll be ready to run callbacks. This query log will also get cleared
                    // so we will have a new log of all the queries that are executed now.
                    this->enable_query_log();

                    this->_query_log = {};

                    // Now we'll execute this callback and capture the result. Once it has been
                    // executed we will restore the value of query logging and give back the
                    // value of hte callback so the original callers can have the results.
                    result = callback();

                    this->_logging_queries = logging_queries;

                    return result;
                }


                // Get the data_object connection to use for a select query.
                data_object get_pdo_for_select(bool use_read_pdo = true) {
                    return use_read_pdo ? this->get_read_pdo() : this->get_pdo();
                }


                // Configure the data_object prepared statement.
                data_object::statement prepared(data_object::statement statement) {
                    statement->set_fetchMode(this->_fetchMode);

                    this->event("StatementPrepared: "+ statement);

                    return statement;
                }


                // Get the default post processor instance.
                processor get_default_post_processor() {
                    return new processor;
                }

                //  Get the default schema grammar instance.
                schema_grammar get_default_schema_grammar() {
                    //
                }

                // Get the default query grammar instance.
                query_grammar get_default_query_grammar() {
                    return query_grammar();
                }

                // The active data_object connection.
                std::shared_ptr<data_object> _pdo;
                std::function<std::shared_ptr<data_object>()> _pdo_closure;

                // The active data_object connection used for reads.
                std::shared_ptr<data_object> _read_pdo;
                std::function<std::shared_ptr<data_object>()> _read_pdo_closure;

                // The name of the connected database.
                string _database;

                // The table prefix for the connection.
                string _table_prefix = "";

                // The database connection configuration options.
                flat_map<string, string> _config;

                // The reconnection instance for the connection.
                function<void(connection&)> _reconnection;

                // The query grammar implementation.
                query_grammar _query_grammar;

                // The schema grammar implementation.
                shared_ptr<schema_grammar> _schema_grammar;

                // The query post processor implementation.
                processor _post_processor;

                // The event dispatcher instance.
                dispatcher _events;

                // The default fetch mode of the connection.
                int _fetchMode = data_object::FETCH_OBJ;

                // The number of active transactions.
                int _transactions = 0;

                // All of the queries run against the connection.
                vector<string> _query_log = {};

                // Indicates whether queries are being logged.
                bool _logging_queries = false;

                // Indicates if the connection is in a "dry run".
                bool _pretending = false;

                // The instance of Doctrine connection.
                // _doctrineConnection;

                // The connection resolvers
                static vector<string> _resolvers;

                // The last error the occurred
                string _error;

                // apply variadic arguments to the invocation
                template<typename T>
                static void apply_invocation_arguments(wpp::db::invocation &w_inv, T t) {
                    w_inv(t);
                }

                template<typename T, typename... Args>
                static void
                apply_invocation_arguments(wpp::db::invocation &w_inv, T t, Args... args) // recursive variadic function
                {
                    w_inv(t);
                    apply_invocation_arguments(w_inv, args...);
                }

        };

        static vector<string> connection::_resolvers = {};

    }
}


/*
     * Allow different databases to SELECT statements, and another for INSERT, UPDATE, and DELETE statements
     * 'mysql' => [
    'read' => [
        'host' => '192.168.1.1',
    ],
    'write' => [
        'host' => '196.168.1.2'
    ],
    'sticky'    => true, // allow the immediate reading of records that have been written to the database
    'driver'    => 'mysql',
    'database'  => 'database',
    'username'  => 'root',
    'password'  => '',
    'charset' => 'utf8mb4',
    'collation' => 'utf8mb4_unicode_ci',
    'prefix'    => '',
    ],

    Other constructor options
    'sticky'    => true,
    'driver'    => 'mysql',
    'charset' => 'utf8mb4',
    'collation' => 'utf8mb4_unicode_ci',
    'prefix'    => '',


     */

// _users = DB::select('select * from users where active = ?', [1]);
// _results = DB::select('select * from users where id = :id', ['id' => 1]);
// parse this with boost::split(query," "), look for tokens that match ^:[A-Za-z0-9_]+_, replace by numbers, and keep it pre-processed
/*
 * DB::transaction(function () {
 *      DB::table('users')->update(['votes' => 1]);
 *      DB::table('posts')->delete();
 *  });
 *  // Manually Using Transactions
 *  DB::begin_transaction();
 *  DB::roll_back();
 *  DB::commit();
 */


#endif //WPP_DB_CONNECTOR_H

