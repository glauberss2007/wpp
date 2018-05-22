//
// Created by Alan de Freitas on 23/11/2017.
//

#ifndef WPP_JOIN_CLAUSE_HPP
#define WPP_JOIN_CLAUSE_HPP

namespace wpp {
    namespace db{
        join_clause::join_clause(query_builder parent_query, string type, string table)
                :query_builder(parent_query.get_connection(), parent_query.get_grammar(), parent_query.get_processor())
        {
            this->_type = type;
            this->_table = table;
            this->_parent_query = parent_query;
        }

    }
}



#endif //WPP_JOIN_CLAUSE_HPP
