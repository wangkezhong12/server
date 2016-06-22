#ifndef MYSQL_ACT_H
#define MYSQL_ACT_H

#include <string>
#include <iostream>
#include <mysql/mysql.h>
#include <vector>

using namespace std;

class mysql_act
{
    public:
        //string res_str = "";
        mysql_act();
        virtual ~mysql_act();

        mysql_act(const char* host,const char* mysql_uname,const char* mysql_upwd,const char* dbname,unsigned int mysql_port);
        //bool mysql_search( const char* query,int colnum);

        string mysql_search(const char* query);
        void freeMysql();

    protected:
    private:
        MYSQL mysql;
        MYSQL_RES *mres;
        MYSQL_ROW column;




};

#endif // MYSQL_ACT_H
