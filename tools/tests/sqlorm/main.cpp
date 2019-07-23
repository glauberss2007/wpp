#include <iostream>
#include <string>
#include <thread>

#include "w++/database.h"
#include "environment.h"

int main() {
    using namespace std;
    // We first implement the db::connector
    // Then we implement the db_query_builder
    // At last we implement the model base class

    // Create DB
    // initdb -D /Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/tools/website/model/data/
    // Start server
    // postgres -D

    wpp::db::connector db({{"db_name","smartlao"},{"data_folder","/Users/alandefreitas/Sync/Computação/Code/C++/Web/wpp/tools/website/model/data/"}});

    if (!db.is_open()){
        return 1;
    }

    wpp::db::result R = db.select("SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE table_schema = 'public'");
    if (!db.error()) {
        for (wpp::db::row row: R){
            for (wpp::db::field &&field : row) {
                std::cout << field.name() << ": ";
                if (!field.is_null()){
                    std::cout << field.c_str() << "\t";
                }
            }
            std::cout << std::endl;
        }
    } else {
        std::cerr << db.error_string() << std::endl;
    }

    R = db.select("SELECT * FROM information_schema.columns WHERE table_name = 'company'");
    if (!db.error()) {
        for (wpp::db::row row: R){
            for (wpp::db::field &&field : row) {
                std::cout << field.name() << ": ";
                if (!field.is_null()){
                    std::cout << field.c_str() << "\t";
                }
            }
            std::cout << std::endl;
        }
    } else {
        std::cerr << db.error_string() << std::endl;
    }

    db.statement("CREATE TABLE IF NOT EXISTS COMPANY("  \
          "ID             INT     PRIMARY KEY     NOT NULL," \
          "NAME           TEXT    NOT NULL," \
          "AGE            INT     NOT NULL," \
          "ADDRESS        CHAR(50)," \
          "SALARY         REAL );");
    if (db.error()) {
        std::cerr << db.error_string() << std::endl;
    }

    //db.table("COMPANY").insert({"NAME","AGE","ADDRESS","SALARY"},{"'Paul'", "32", "'California'", "20000.00" });
    //db.table("COMPANY").insert({"NAME","AGE","ADDRESS","SALARY"},{"'Allen'", "25", "'Texas'", "15000.00" });
    //db.table("COMPANY").insert({"NAME","AGE","ADDRESS","SALARY"},{"'Teddy'", "23", "'Norway'", "20000.00" });
    //db.table("COMPANY").insert({"NAME","AGE","ADDRESS","SALARY"},{"'Mark'", "25", "'Rich-Mond'", "65000.00" });
    //if (db.error()) {
    //    std::cerr << db.error_string() << std::endl;
    //}
    //
    //R = db.table("employee").get();
    //if (!db.error()) {
    //    std::cout << "Found " << R.size() << " employees:" << std::endl;
    //    for (auto row: R){
    //        std::cout << "Employee " << row["id"] << ": ";
    //        for (auto &&field : row) {
    //            if (!field.is_null()){
    //                std::cout << field.c_str() << " ";
    //            }
    //        }
    //        std::cout << std::endl;
    //    }
    //    std::cout << std::endl;
    //} else {
    //    std::cerr << db.error_string() << std::endl;
    //}

    if (!R.empty() && R[0]["salary"].as<double>() < 10000){
        std::cout << "Doubling all employees' salaries..." << std::endl;
        db.update("update employee set salary = $1",{"salary*2"});
    } else {
        std::cout << "Reducing all employees' salaries..." << std::endl;
        db.update("update employee set salary = $1",{"salary/2"});
    }
    if (db.error()) {
        std::cerr << db.error_string() << std::endl;
    }

    db.prepare("find","SELECT * FROM employee WHERE name = $1 AND salary > $2");
    string name = "João";
    R = db.run("find",name,10);
    if (db.error()) {
        for (auto row: R){
            std::cout << "Employee " << row["id"] << ": ";
            for (auto &&field : row) {
                if (!field.is_null()){
                    std::cout << field.c_str() << " ";
                }
            }
            std::cout << " (earns more than 10$)" << std::endl;
        }
        std::cout << std::endl;
    } else {
        std::cerr << db.error_string() << std::endl;
    }

    return 0;
}