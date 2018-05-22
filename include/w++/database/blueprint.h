//
// Created by Alan de Freitas on 20/11/2017.
//

#ifndef WPP_BLUEPRINT_H
#define WPP_BLUEPRINT_H

#include <string>

#include "utils/container/php_utils.h"

#include "datatype_alias.h"

namespace wpp {
    namespace db {
        // forward declaration
        class connection;
        class schema_grammar;

        class blueprint {
            public:
                using self_t = blueprint;



                struct column {
                    std::string name;
                    std::string type;
                    bool change;
                    bool nullable_;
                    bool primary_bool;
                    bool unique_bool;
                    bool index_bool;
                    std::string primary_string;
                    std::string unique_string;
                    std::string index_string;
                    flat_map<string,vector<string>> parameters;
                    column& nullable(){
                        this->nullable_ = true;
                        return *this;
                    };
                };

                struct command {
                    std::string name;
                    flat_map<string,vector<string>> parameters;
                    std::string index;
                    std::vector<std::string> columns;
                    std::string on;
                    std::vector<std::string> references;
                    std::string on_delete;
                    std::string on_update;
                };

            protected:
                /**
                  * The table the blueprint describes.
                  *
                  * @var std::string
                  */
                std::string _table;

            protected:
                /**
                  * The columns that should be added to the table.
                  *
                  * @var array
                  */

                vector<column> _columns = {};

            protected:
                /**
                  * The commands that should be run for the table.
                  *
                  * @var array
                  */

                vector<command> _commands = {};

            public:
                /**
                  * The storage engine that should be used for the table.
                  *
                  * @var std::string
                  */
                std::string _engine;

                /**
                 * The default character set that should be used for the table.
                 */

                std::string _charset;

                /**
                  * The collation that should be used for the table.
                  */
                std::string _collation;

                /**
                 * Whether to make the table temporary.
                 *
                 * @var bool
                 */

                bool _temporary = false;

            public:
                /**
                  * Create a new schema blueprint.
                  *
                  * @param  std::string  table
                  * @param  \Closure|null  callback
                  * @return void
                  */
                blueprint(std::string table) {
                    this->_table = table;
                }

                template<typename Closure>
                blueprint(std::string table, Closure callback) {
                    this->_table = table;
                    callback(*this);
                }

                /**
                  * Execute the blueprint against the database.
                  *
                  * @param  wpp::db::connection  connection
                  * @param  wpp::db::schema_grammar grammar
                  * @return void
                  */
                void build(wpp::db::connection& connection, wpp::db::schema_grammar grammar);

            public:
                /**
                  * Get the raw SQL statements for the blueprint.
                  *
                  * @param  wpp::db::connection  connection
                  * @param  wpp::db::schema_grammar  grammar
                  * @return array
                  */
                vector<string> to_sql(wpp::db::connection& connection, wpp::db::schema_grammar grammar);

            protected:
                /**
                  * Add the commands that are implied by the blueprint"s state.
                  *
                  * @return void
                  */
                void add_implied_commands() {
                    if (!this->get_added_columns().empty() && !this->creating()) {
                        utils::array_unshift(this->_commands, this->create_command("add"));
                    }

                    if (!this->get_changed_columns().empty() && !this->creating()) {
                        utils::array_unshift(this->_commands, this->create_command("change"));
                    }

                    this->add_fluent_indexes();
                }

            protected:
                /**
                  * Add the index commands fluently specified on columns.
                  *
                  * @return void
                  */
                void add_fluent_indexes() {
                    for (column& c: this->_columns) {
                        // Primary
                        // If the index has been specified on the given column, but is simply equal
                        // to "true" (boolean), no name has been specified for this index so the
                        // index method can be called without a name and it will generate one.
                        if (c.primary_bool && c.primary_string.empty()) {
                            this->primary(c.name);
                            continue;
                        }
                        // If the index has been specified on the given column, and it has a std::string
                        // value, we"ll go ahead and call the index method and pass the name for
                        // the index since the developer specified the explicit name for this.
                        else if (!c.primary_string.empty()) {
                            this->primary(c.name,c.primary_string);
                            continue;
                        }
                        // Unique
                        if (c.unique_bool && c.unique_string.empty()) {
                            this->unique(c.name);
                            continue;
                        }
                        else if (!c.unique_string.empty()) {
                            this->unique(c.name,c.unique_string);
                            continue;
                        }
                        // Index
                        if (c.index_bool && c.index_string.empty()) {
                            this->index(c.name);
                            continue;
                        }
                        else if (!c.index_string.empty()) {
                            this->index(c.name,c.index_string);
                            continue;
                        }
                    }
                }

            protected:
                /**
                  * Determine if the blueprint has a create command.
                  *
                  * @return bool
                  */
                bool creating() {
                    return std::find_if(this->_commands.begin(),this->_commands.end(),[](std::string& s){
                        return s == "create";
                    }) != this->_commands.end();
                }

            public:
                /**
                  * Indicate that the table needs to be created.
                  *
                  * @return Fluent
                  */
                command create() {
                    return this->add_command("create");
                }

            public:
                /**
                  * Indicate that the table needs to be temporary.
                  *
                  * @return void
                  */
                void temporary() {
                    this->_temporary = true;
                }

            public:
                /**
                  * Indicate that the table should be dropped.
                  *
                  * @return Fluent
                  */
                command drop() {
                    return this->add_command("drop");
                }

            public:
                /**
                  * Indicate that the table should be dropped if it exists.
                  *
                  * @return Fluent
                  */

                command drop_if_exists() {
                    return this->add_command("drop_if_exists");
                }

            public:
                /**
                  * Indicate that the given columns should be dropped.
                  *
                  * @param  array|mixed  columns
                  * @return Fluent
                  */
                template<typename... T>
                command drop_column(T... args) {
                    auto columns = utils::func_get_args(args...);
                    return this->add_command("drop_column", {{"columns",columns}});
                }

                command drop_column(vector<string> columns) {
                    return this->add_command("drop_column", {{"columns",columns}});
                }

            public:
                /**
                  * Indicate that the given columns should be renamed.
                  *
                  * @param  std::string  from
                  * @param  std::string  to
                  * @return Fluent
                  */
                command rename_column(std::string from, std::string to) {
                    return this->add_command("rename_column", {{"from",{from}},{"to",{to}}});
                }

            public:
                /**
                  * Indicate that the given primary key should be dropped.
                  *
                  * @param  std::string|array  index
                  * @return Fluent
                  */
                template<typename string_or_array>
                command drop_primary(string_or_array index = {}) {
                    return this->drop_index_command("drop_primary", "primary", index);
                }

            public:
                /**
                  * Indicate that the given unique key should be dropped.
                  *
                  * @param  std::string|array  index
                  * @return Fluent
                  */
                command drop_unique(std::string index) {
                    return this->drop_index_command("drop_unique", "unique", index);
                }

                command drop_unique(vector<string> index) {
                    return this->drop_index_command("drop_unique", "unique", index);
                }

            public:
                /**
                  * Indicate that the given index should be dropped.
                  *
                  * @param  std::string|array  index
                  * @return Fluent
                  */

                command drop_index(std::string index) {
                    return this->drop_index_command("drop_index", "index", index);
                }

                command drop_index(vector<string> index) {
                    return this->drop_index_command("drop_index", "index", index);
                }

            public:
                /**
                  * Indicate that the given foreign key should be dropped.
                  *
                  * @param  std::string|array  index
                  * @return Fluent
                  */

                command drop_foreign(std::string index) {
                    return this->drop_index_command("drop_foreign", "foreign", index);
                }

                command drop_foreign(vector<string> index) {
                    return this->drop_index_command("drop_foreign", "foreign", index);
                }

            public:
                /**
                  * Indicate that the timestamp columns should be dropped.
                  *
                  * @return void
                  */
                void drop_timestamps() {
                    this->drop_column("created_at", "updated_at");
                }

            public:
                /**
                  * Indicate that the timestamp columns should be dropped.
                  *
                  * @return void
                  */

                void drop_timestamps_tz() {
                    this->drop_timestamps();
                }

            public:
                /**
                  * Indicate that the soft delete column should be dropped.
                  *
                  * @return void
                  */

                void drop_soft_deletes() {
                    this->drop_column("deleted_at");
                }

            public:
                /**
                  * Indicate that the soft delete column should be dropped.
                  *
                  * @return void
                  */

                void drop_soft_deletes_tz() {
                    this->drop_soft_deletes();
                }

            public:
                /**
                  * Indicate that the remember token column should be dropped.
                  *
                  * @return void
                  */

                void drop_remember_token() {
                    this->drop_column("remember_token");
                }

            public:
                /**
                  * Rename the table to a given name.
                  *
                  * @param  std::string  to
                  * @return Fluent
                  */

                command rename(std::string to) {
                    return this->add_command("rename", {{"to",{to}}});
                }

            public:
                /**
                  * Specify the primary key(s) for the table.
                  *
                  * @param  std::string|array  columns
                  * @param  std::string  name
                  * @param  std::string|null  algorithm
                  * @return Fluent
                  */
                template<typename string_or_array>
                command primary(string_or_array columns, std::string name = "", std::string algorithm = "") {
                    return this->index_command("primary", columns, name, algorithm);
                }

            public:
                /**
                  * Specify a unique index for the table.
                  *
                  * @param  std::string|array  columns
                  * @param  std::string  name
                  * @param  std::string|null  algorithm
                  * @return Fluent
                  */
                template<typename string_or_array>
                command unique(string_or_array columns, std::string name = "", std::string algorithm = "") {
                    return this->index_command("unique", columns, name, algorithm);
                }

            public:
                /**
                  * Specify an index for the table.
                  *
                  * @param  std::string|array  columns
                  * @param  std::string  name
                  * @param  std::string|null  algorithm
                  * @return Fluent
                  */
                command index(string column, std::string name = "", std::string algorithm = "") {
                    return this->index(vector<string>{column}, name, algorithm);
                }

                command index(vector<string> columns, std::string name = "", std::string algorithm = "") {
                    return this->index_command("index", columns, name, algorithm);
                }


            public:
                /**
                  * Specify a foreign key for the table.
                  *
                  * @param  std::string|array  columns
                  * @param  std::string  name
                  * @return Fluent
                  */
                template<typename string_or_array>
                command foreign(string_or_array columns, std::string name = "") {
                    return this->index_command("foreign", columns, name);
                }

            public:
                /**
                  * Create a new auto-incrementing integer (4-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */
                column increments(std::string _column) {
                    return this->unsigned_integer(_column, true);
                }

            public:
                /**
                  * Create a new auto-incrementing tiny integer (1-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */
                column tiny_increments(std::string _column) {
                    return this->unsigned_tiny_integer(_column, true);
                }

            public:
                /**
                  * Create a new auto-incrementing small integer (2-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column small_increments(std::string _column) {
                    return this->unsigned_small_integer(_column, true);
                }

            public:
                /**
                  * Create a new auto-incrementing medium integer (3-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column medium_increments(std::string _column) {
                    return this->unsigned_medium_integer(_column, true);
                }

            public:
                /**
                  * Create a new auto-incrementing big integer (8-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column big_increments(std::string _column) {
                    return this->unsigned_big_integer(_column, true);
                }

            public:
                /**
                  * Create a new char column on the table.
                  *
                  * @param  std::string  column
                  * @param  int  length
                  * @return Fluent
                  */
                column character(column, int length = -1);

            public:
                /**
                  * Create a new std::string column on the table.
                  *
                  * @param  std::string  column
                  * @param  int  length
                  * @return Fluent
                  */
                column string_(string column, int length = -1);

            public:
                /**
                  * Create a new text column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column text(std::string _column) {
                    return this->add_column("text", _column);
                }

            public:
                /**
                  * Create a new medium text column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column medium_text(std::string _column) {
                    return this->add_column("medium_text", _column);
                }

            public:
                /**
                  * Create a new long text column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column long_text(std::string _column) {
                    return this->add_column("long_text", _column);
                }

            public:
                /**
                  * Create a new integer (4-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @param  bool  unsigned
                  * @return Fluent
                  */

                column integer(std::string _column, bool auto_increment = false, bool _unsigned = false) {
                    return this->add_column("integer", _column, {{"auto_increment",{(auto_increment ? "true" : "false")}}, {"unsigned",{(_unsigned ? "true" : "false")}}});
                }

            public:
                /**
                  * Create a new tiny integer (1-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @param  bool  unsigned
                  * @return Fluent
                  */

                column tiny_integer(std::string column, bool auto_increment = false, bool _unsigned = false) {
                    return this->add_column("tiny_integer", column, {{"auto_increment",{(auto_increment ? "true" : "false")}}, {"unsigned",{(_unsigned ? "true" : "false")}}});
                }

            public:
                /**
                  * Create a new small integer (2-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @param  bool  unsigned
                  * @return Fluent
                  */

                column small_integer(std::string column, bool auto_increment = false, bool _unsigned = false) {
                    return this->add_column("small_integer", column, {{"auto_increment",{(auto_increment ? "true" : "false")}}, {"unsigned",{(_unsigned ? "true" : "false")}}});
                }

            public:
                /**
                  * Create a new medium integer (3-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @param  bool  unsigned
                  * @return Fluent
                  */

                column medium_integer(std::string column, bool auto_increment = false, bool _unsigned = false) {
                    return this->add_column("medium_integer", column, {{"auto_increment",{(auto_increment ? "true" : "false")}}, {"unsigned",{(_unsigned ? "true" : "false")}}});
                }

            public:
                /**
                  * Create a new big integer (8-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @param  bool  unsigned
                  * @return Fluent
                  */

                column big_integer(std::string column, bool auto_increment = false, bool _unsigned = false) {
                    return this->add_column("big_integer", column, {{"auto_increment",{(auto_increment ? "true" : "false")}}, {"unsigned",{(_unsigned ? "true" : "false")}}});
                }

            public:
                /**
                  * Create a new unsigned integer (4-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @return Fluent
                  */
                column unsigned_integer(std::string _column, bool auto_increment = false) {
                    return this->integer(_column, auto_increment, true);
                }

            public:
                /**
                  * Create a new unsigned tiny integer (1-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @return Fluent
                  */

                column unsigned_tiny_integer(std::string column, bool auto_increment = false) {
                    return this->tiny_integer(column, auto_increment, true);
                }

            public:
                /**
                  * Create a new unsigned small integer (2-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @return Fluent
                  */

                column unsigned_small_integer(std::string column, bool auto_increment = false) {
                    return this->small_integer(column, auto_increment, true);
                }

            public:
                /**
                  * Create a new unsigned medium integer (3-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @return Fluent
                  */

                column unsigned_medium_integer(std::string column, bool auto_increment = false) {
                    return this->medium_integer(column, auto_increment, true);
                }

            public:
                /**
                  * Create a new unsigned big integer (8-byte) column on the table.
                  *
                  * @param  std::string  column
                  * @param  bool  auto_increment
                  * @return Fluent
                  */

                column unsigned_big_integer(std::string column, bool auto_increment = false) {
                    return this->big_integer(column, auto_increment, true);
                }

            public:
                /**
                  * Create a new float column on the table.
                  *
                  * @param  std::string  column
                  * @param  int     total
                  * @param  int     places
                  * @return Fluent
                  */

                column float_(std::string column, int total = 8, int places = 2)
                {
                    return this->add_column("float", column, {{"total",{std::to_string(total)}}, {"places",{std::to_string(places)}}});
                }

            public:
                /**
                  * Create a new double column on the table.
                  *
                  * @param  std::string   column
                  * @param  int|null    total
                  * @param  int|null places
                  * @return Fluent
                  */

                column double_(std::string column, int total = -1, int  places = -1)
{
                    return this->add_column("double", column, {{"total",{std::to_string(total)}}, {"places",{std::to_string(places)}}});
                }

            public:
                /**
                  * Create a new decimal column on the table.
                  *
                  * @param  std::string  column
                  * @param  int     total
                  * @param  int     places
                  * @return Fluent
                  */

                column decimal(std::string column, int total = 8, int places = 2) {
                    return this->add_column("decimal", column, {{"total",{std::to_string(total)}}, {"places",{std::to_string(places)}}});
                }

            public:
                /**
                  * Create a new boolean column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column boolean(std::string _column) {
                    return this->add_column("boolean", _column);
                }

            public:
                /**
                  * Create a new enum column on the table.
                  *
                  * @param  std::string  column
                  * @param  array   allowed
                  * @return Fluent
                  */
                column enumeration(std::string column, vector<std::string> allowed)
                {
                    return this->add_column("enum", column, {{"allowed",{allowed}}});
                }

            public:
                /**
                  * Create a new json column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column json(std::string _column) {
                    return this->add_column("json", _column);
                }

            public:
                /**
                  * Create a new jsonb column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column jsonb(std::string _column) {
                    return this->add_column("jsonb", _column);
                }

            public:
                /**
                  * Create a new date column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column date(std::string _column) {
                    return this->add_column("date", _column);
                }

            public:
                /**
                  * Create a new date-time column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column date_time(std::string _column) {
                    return this->add_column("date_time", _column);
                }

            public:
                /**
                  * Create a new date-time column (with time zone) on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column date_time_tz(std::string _column) {
                    return this->add_column("date_time_tz", _column);
                }

            public:
                /**
                  * Create a new time column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column time(std::string _column) {
                    return this->add_column("time", _column);
                }

            public:
                /**
                  * Create a new time column (with time zone) on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column time_tz(std::string _column) {
                    return this->add_column("time_tz", _column);
                }

            public:
                /**
                  * Create a new timestamp column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column timestamp(std::string _column) {
                    return this->add_column("timestamp", _column);
                }

            public:
                /**
                  * Create a new timestamp (with time zone) column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column timestamp_tz(std::string _column) {
                    return this->add_column("timestamp_tz", _column);
                }

            public:
                /**
                  * Add nullable creation and update timestamps to the table.
                  *
                  * @return void
                  */

                void timestamps() {
                    this->timestamp("created_at").nullable();

                    this->timestamp("updated_at").nullable();
                }

            public:
                /**
                  * Add nullable creation and update timestamps to the table.
                  *
                  * Alias for self::timestamps().
                  *
                  * @return void
                  */

                void nullable_timestamps() {
                    this->timestamps();
                }

            public:
                /**
                  * Add creation and update timestamp_tz columns to the table.
                  *
                  * @return void
                  */

                void timestamps_tz() {
                    this->timestamp_tz("created_at").nullable();

                    this->timestamp_tz("updated_at").nullable();
                }

            public:
                /**
                  * Add a "deleted at" timestamp for the table.
                  *
                  * @return Fluent
                  */

                column soft_deletes() {
                    return this->timestamp("deleted_at").nullable();
                }

            public:
                /**
                  * Add a "deleted at" timestamp_tz for the table.
                  *
                  * @return Fluent
                  */
                column soft_deletes_tz() {
                    return this->timestamp_tz("deleted_at").nullable();
                }

            public:
                /**
                  * Create a new binary column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column binary(std::string _column) {
                    return this->add_column("binary", _column);
                }

            public:
                /**
                  * Create a new uuid column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column uuid(std::string _column) {
                    return this->add_column("uuid", _column);
                }

            public:
                /**
                  * Create a new IP address column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column ip_address(std::string _column) {
                    return this->add_column("ip_address", _column);
                }

            public:
                /**
                  * Create a new MAC address column on the table.
                  *
                  * @param  std::string  column
                  * @return Fluent
                  */

                column mac_address(std::string _column) {
                    return this->add_column("mac_address", _column);
                }

            public:
                /**
                  * Add the proper columns for a polymorphic table.
                  *
                  * @param  std::string  name
                  * @param  std::string|null  index_name
                  * @return void
                  */

                void morphs(std::string name, std::string index_name = "") {
                    this->unsigned_integer(name + "_id");

                    this->string_(name + "_type");

                    this->index(vector<string>({name + "_id", name + "_type"}), index_name);
                }

            public:
                /**
                  * Add nullable columns for a polymorphic table.
                  *
                  * @param  std::string  name
                  * @param  std::string|null  index_name
                  * @return void
                  */

                void nullable_morphs(string name, string index_name = "") {
                    this->unsigned_integer(name + "_id").nullable();

                    this->string_(name + "_type").nullable();

                    this->index(vector<string>({name + "_id", name + "_type"}), index_name);
                }

            public:
                /**
                  * Adds the `remember_token` column to the table.
                  *
                  * @return Fluent
                  */

                column remember_token() {
                    return this->string_("remember_token", 100).nullable();
                }

            protected:
                /**
                  * Add a new index command to the blueprint.
                  *
                  * @param  std::string        type
                  * @param  std::string|array  columns
                  * @param  std::string        index
                  * @param  std::string|null   algorithm
                  * @return Fluent
                  */
                command index_command(std::string type, std::string column, std::string index = "", std::string algorithm = "") {
                    vector<std::string> columns = {column};
                    return this->index_command(type,columns,index,algorithm);
                }

                command index_command(std::string type, vector<std::string> columns, std::string index = "", std::string algorithm = "") {
                    // If no name was specified for this index, we will create one using a basic
                    // convention of the table name, followed by the columns, followed by an
                    // index type, such as primary or index, which makes the index unique.
                    if (index.empty()){
                        index = this->create_index_name(type, columns);
                    }
                    const flat_map<std::string,vector<std::string>> parameters = {{"index",{index}},{"columns",columns},{"algorithm",{algorithm}}};
                    return this->add_command(type, parameters);
                }

            protected:
                /**
                  * Create a new drop index command on the blueprint.
                  *
                  * @param  std::string  command
                  * @param  std::string  type
                  * @param  std::string|array  index
                  * @return Fluent
                  */

                command drop_index_command(std::string command, std::string type, std::string index) {
                    vector<std::string> columns = {};
                    return this->index_command(command, columns, index);
                }

                command drop_index_command(std::string command, std::string type, vector<std::string> index) {
                    vector<std::string> columns = index;

                    // If the given "index" is actually an array of columns, the developer means
                    // to drop an index merely by specifying the columns involved without the
                    // conventional name, so we will build the index name from the columns.
                    string index_name = this->create_index_name(type, columns);

                    return this->index_command(command, columns, index_name);
                }

            protected:
                /**
                  * Create a default index name for the table.
                  *
                  * @param  std::string  type
                  * @param  array   columns
                  * @return std::string
                  */

                std::string create_index_name(std::string type, vector<std::string> columns) {
                    std::string index = utils::strtolower(this->_table + "_" + utils::implode("_", columns) + "_" + type);
                    return utils::str_replace(vector<string>({"-", "."}), "_", index);
                }

            public:
                /**
                  * Add a new column to the blueprint.
                  *
                  * @param  std::string  type
                  * @param  std::string  name
                  * @param  array   parameters
                  * @return Fluent
                  */

                column add_column(std::string type, std::string name, flat_map<std::string,vector<std::string>> parameters = {}) {
                    column c;
                    c.name = name;
                    c.type = type;
                    c.parameters = parameters;
                    this->_columns.push_back(c);

                    return c;
                }

            public:
                /**
                  * Remove a column from the schema blueprint.
                  *
                  * @param  std::string  name
                  * @return this
                  */

                self_t& remove_column(string name) {
                    auto iter = std::remove_if(this->_columns.begin(),this->_columns.end(),[&name](column& c){
                        return c.name == name;
                    });
                    this->_columns.erase(iter,this->_columns.end());

                    return *this;
                }

            protected:
                /**
                  * Add a new command to the blueprint.
                  *
                  * @param  std::string  name
                  * @param  array  parameters
                  * @return Fluent
                  */
                command add_command(std::string name, flat_map<std::string,vector<std::string>> parameters = {}) {
                    command _command = this->create_command(name, parameters);
                    this->_commands.push_back(_command);
                    return _command;
                }

            protected:
                /**
                 * Create a new Fluent command.
                 *
                 * @param  std::string  name
                 * @param  array   parameters
                 * @return Fluent
                 */
                command create_command(std::string name, flat_map<std::string,vector<std::string>> parameters = {}) {
                    command c;
                    c.name = name;
                    c.parameters = parameters;
                    return c;
                }

            public:
                /**
                  * Get the table the blueprint describes.
                  *
                  * @return std::string
                  */
                std::string get_table() {
                    return this->_table;
                }

            public:
                /**
                * Get the columns on the blueprint.
                *
                * @return array
                */
                vector<column> get_columns() {
                    return this->_columns;
                }

            public:
                /**
                * Get the commands on the blueprint.
                *
                * @return array
                */
                vector<command> get_commands() {
                    return this->_commands;
                }

                /**
                  * Get the columns on the blueprint that should be added.
                  *
                  * @return array
                  */
                vector<column> get_added_columns() {
                    vector<column> c = this->_columns;
                    vector<column>::iterator iter = std::remove_if(c.begin(),c.end(),[](column& c){
                        return c.change;
                    });
                    c.erase(iter,c.end());
                    return c;
                }

            public:
                /**
                  * Get the columns on the blueprint that should be changed.
                  *
                  * @return array
                  */
                vector<column> get_changed_columns() {
                    vector<column> c = this->_columns;
                    vector<column>::iterator iter = std::remove_if(c.begin(),c.end(),[](column& cdata){
                        return !cdata.change;
                    });
                    c.erase(iter,c.end());
                    return c;
                }
        };
    }
}

#endif //WPP_BLUEPRINT_H
