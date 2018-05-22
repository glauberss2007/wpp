//
// Created by Alan de Freitas on 20/11/2017.
//

#ifndef WPP_JOIN_CLAUSE_H
#define WPP_JOIN_CLAUSE_H

#include "datatype_alias.h"
#include "query_builder.h"

namespace wpp {

    namespace db {

        class connection;

        class query_grammar;

        class join_clause : public query_builder {
            using self_t = join_clause;

            public:
                string _type;
                string _table;

            private:
                query_builder& _parent_query;

            public:
                join_clause(query_builder parent_query, string type, string table);

                template<typename Closure>
                self_t& on(Closure first, string operator_ = "", string second = "", string boolean = "and")
                {
                    return this->where_nested(first, boolean);
                }

                template<typename Closure>
                self_t& on(string first, string operator_ = "", string second = "", string boolean = "and")
                {
                    return static_cast<self_t&>(this->where_column(first, operator_, second, boolean));
                }

                template<typename closure_or_string>
                self_t& or_on(closure_or_string first, string operator_ = "", string second = "")
                {
                    return this->on(first, operator_, second, "or");
                }

                /**
                 * Get a new instance of the join clause builder.
                 *
                 * @return \Illuminate\Database\Query\JoinClause
                 */
                self_t new_query()
                {
                    return join_clause(this->_parent_query, this->_type, this->_table);
                }
        };
    }
}

#endif //WPP_JOIN_CLAUSE_H
