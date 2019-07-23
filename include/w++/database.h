//
// Created by Alan de Freitas on 16/11/2017.
//

#ifndef WPP_DATABASE_UTILS_H
#define WPP_DATABASE_UTILS_H

/////////////////////////////////////////////
//        Definition / Implementation      //
/////////////////////////////////////////////
// Classes to keep database results
#include "database/result.h"
// Database abstraction
#include "database/data_object.h"
#include "database/pgsql_data_object.h"
//#include "database/mysql_driver.h"
//#include "database/sqlite_driver.h"
// Base classes
#include "database/datatype_alias.h"
#include "database/processor.h"
// Paginators
#include "database/paginator.h"
#include "database/length_aware_paginator.h"
// Building queries (interdependent)
#include "database/query_builder.h"
#include "database/join_clause.h"
#include "database/base_grammar.h"
#include "database/query_grammar.h"
// Building schemas (interdependent)
#include "database/blueprint.h"
#include "database/schema_grammar.h"
#include "database/schema_builder.h"
// Wrapper of connection to database
#include "database/connection.h"

/////////////////////////////////////////////
// Implementation of forward declarations  //
/////////////////////////////////////////////
#include "database/processor.hpp"
#include "database/blueprint.hpp"
#include "database/query_builder.hpp"
#include "database/query_grammar.hpp"

#endif //WPP_DATABASE_UTILS_H

