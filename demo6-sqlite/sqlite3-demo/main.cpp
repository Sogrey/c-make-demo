#include <iostream>
#include "sqlite3.h"

int main()
{
    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);
    if( rc )
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    const char* sql = "CREATE TABLE COMPANY("
                     "ID INT PRIMARY KEY     NOT NULL,"
                     "NAME           TEXT    NOT NULL,"
                     "AGE            INT     NOT NULL,"
                     "ADDRESS        CHAR(50),"
                     "SALARY         REAL );";
    char* errMsg;
    rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if( rc != SQLITE_OK )
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}
