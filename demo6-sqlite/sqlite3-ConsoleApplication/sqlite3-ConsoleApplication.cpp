// sqlite3-ConsoleApplication.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "sqlite3/sqlite3.h"
#include<stdlib.h>
#include<string.h>
using namespace std;

bool test(sqlite3* db){
    sqlite3_stmt* stmt = NULL;
    if (sqlite3_prepare_v2(db,
        "create table if not exists files("
        "id int primary key not null, "
        "name string unique not null, "
        "size int not null, "
        "data blob not null)",
        512, &stmt, NULL) != SQLITE_OK)
        return false;
    if (sqlite3_step(stmt) != SQLITE_DONE)
        return false;

    if (sqlite3_finalize(stmt) != SQLITE_OK)
        return false;

    if (sqlite3_prepare_v2(db,
        "insert into files values(last_insert_rowid() + 1, ?, 0, ?)",
        512, &stmt, NULL) != SQLITE_OK)
        return false;

    if (sqlite3_reset(stmt) != SQLITE_OK)
        return false;

    if (sqlite3_bind_text(stmt, 1, "http://dearymz.blog.163.com", -1, NULL) != SQLITE_OK)
        return false;

    if (sqlite3_bind_text(stmt, 2, "http://dearymz.blog.163.com", -1, NULL) != SQLITE_OK)
        return false;

    if (sqlite3_step(stmt) != SQLITE_DONE)
        return false;

    if (sqlite3_finalize(stmt) != SQLITE_OK)
        return false;

    if (sqlite3_prepare_v2(db,
        "select count(*) from files",
        512, &stmt, NULL) != SQLITE_OK)
        return false;

    if (sqlite3_step(stmt) != SQLITE_ROW)
        return false;

    cout << sqlite3_column_int(stmt, 0) << endl;

    if (sqlite3_finalize(stmt) != SQLITE_OK)
        return false;

    return true;
}

void test()
{
    int len = sizeof(int) * 8;
    printf("sizeof(int)=%d\n", len);

    len = sizeof(int*) * 8;
    printf("sizeof(int*)=%d\n", len);

#ifdef _MSC_VER
    printf("_MSC_VER is defined\n");
#endif

#ifdef __GNUC__
    printf("__GNUC__ is defined\n");
#endif

#ifdef __INTEL__ 
    printf("__INTEL__  is defined\n");
#endif

#ifdef __i386__ 
    printf("__i386__  is defined\n");
#endif

#ifdef __x86_64__ 
    printf("__x86_64__  is defined\n");
#endif

#ifdef _WIN32 
    printf("_WIN32 is defined\n");
#endif

#ifdef _WIN64 
    printf("_WIN64 is defined\n");
#endif


#ifdef __linux__ 
    printf("__linux__ is defined\n");
#endif

#ifdef __LP64__ 
    printf("__LP64__ is defined\n");
#endif


#ifdef __amd64 
    printf("__amd64 is defined\n");
#endif
}

int main()
{
    std::cout << "Hello World!\n";

    test();

    sqlite3* db = NULL;
    if (sqlite3_open("test.db", &db) == 0) {
        if (test(db))
            cout << "OK" << endl;
        else
            cout << "Error!" << endl;
    }
    cout << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);

    system("pause");
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
