//
// Created by Alan de Freitas on 19/11/2017.
//

#ifndef WPP_PROCESSOR_HPP
#define WPP_PROCESSOR_HPP

namespace wpp {
    namespace db {
        wpp::db::result processor::process_select(db::query_builder& query, vector<string> results){
            return results;
        }

        // Process an  "insert get ID" query.
        int processor::process_insert_get_id(db::query_builder& query, string sql, vector<string> values, string sequence = "")
        {
            query.get_connection()->insert(sql, values);

            string id = query->get_connection()->get_pdo()->last_insert_id(sequence);

            int int_id;
            if (!utils::is_int(id) && utils::is_double(id)){
                int_id = (int) stod(id);
            } else if (utils::is_int(id)){
                int_id = stoi(id);
            }

            return int_id;
        }

    }
}

#endif //WPP_PROCESSOR_HPP
