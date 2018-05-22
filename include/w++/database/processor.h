//
// Created by Alan de Freitas on 19/11/2017.
//

#ifndef WPP_PROCESSOR_H
#define WPP_PROCESSOR_H

namespace wpp {
    namespace db {
        class query_builder;

        class processor
        {
            public:
                // Process the results of a "select" query.
                wpp::db::result process_select(db::query_builder& query, vector<string> results);

                // Process the results of a column listing query.
                vector<string> process_column_listing(vector<string> results);
        };
    }
}



#endif //WPP_PROCESSOR_H
