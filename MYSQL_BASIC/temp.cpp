/*================================================================
* Filename:temp.cpp
* Author: KCN_yu
* Createtime:Sun 21 Mar 2021 04:47:35 PM CST
================================================================*/

#include <iostream>
#include <mysql/mysql.h>
using namespace std;

int main(int argc, char *argv[])
{
    MYSQL mysql;
    MYSQL_RES *result;
    mysql_init(&mysql);
    mysql_real_connect(
        &mysql,
        "localhost",
        "root",
        "123123",
        "gradesystem",
        3306,
        NULL,
        0
    );
    string sql = "select * from mark";
    mysql_query(&mysql, sql.c_str());
    result = mysql_store_result(&mysql);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL){
        cout << row[0] << row[1] << endl;
    }
    mysql_close(&mysql);
    return 0;
}
