#include <iostream>
#include "tcp_server.h"
#include "mysql_act.h"
#include <string>

#define PORT 8009

using namespace std;

int main(int argc,char*argv[])
{



    //const char* host = "localhost";
    //const char* mysql_uname = "root";
    //const char* mysql_upwd = "111111";
    //const char* dbname   = "kezon";
    //unsigned int mysql_port = 3306;
   // string sql = "select * from kezon;";
    const char* host = argv[1];
    const char* mysql_uname = argv[2];
    const char* mysql_upwd = argv[3];
    const char* dbname   = argv[4];
    unsigned int mysql_port = atoi(argv[5]);

    tcp_server ts(PORT);
    mysql_act ma(host,mysql_uname,mysql_upwd,dbname,mysql_port);
    ts.recv_msg(ma,atoi(argv[6]));
    //ma.mysql_search(sql.c_str());
    //cout<<ma.res_str;
    ma.freeMysql();

    return 0;
}
