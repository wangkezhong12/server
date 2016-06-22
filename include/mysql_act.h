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
        string res_str = "";
        mysql_act();
        virtual ~mysql_act();

        mysql_act(const char* host,const char* mysql_uname,const char* mysql_upwd,const char* dbname,unsigned int mysql_port);
        bool mysql_search( const char* query,int colnum);
        string getResStr(MYSQL_ROW mysql_row);
        void freeMysql();

    protected:
    private:
     //   const string host = "localhost";
    //    const string mysql_uname = "root" ;
    //    const string mysql_upwd = "111111";
    //    const string dbname = "crypt" ;
        MYSQL mysql;
        MYSQL_RES *mres;
        MYSQL_ROW column;
        vector<MYSQL_FIELD* > mfield_v;


};

#endif // MYSQL_ACT_H
