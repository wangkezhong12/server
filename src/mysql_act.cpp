#include "mysql_act.h"


using namespace std;

mysql_act::mysql_act()
{
    //ctor
}

mysql_act::~mysql_act()
{
    //dtor
}

mysql_act::mysql_act(const char* host,const char* mysql_uname,const char* mysql_upwd,const char* dbname,unsigned int mysql_port)
{
    mysql_init(&mysql);
    if(mysql_real_connect(&mysql,host,mysql_uname,mysql_upwd,dbname,mysql_port,NULL,0))
    {
        cout<<"connect success!"<<endl;
    }
    else
    {
        cout<<mysql_error(&mysql)<<endl;
        cout<<"connect failed!"<<endl;
    }

}


string mysql_act::mysql_search(const char* query)
{
    const char * sql = query;
    string st = "";
     cout<<"sql:"<<sql<<endl;
        if(mysql_query(&mysql,sql))
        {
            cout<<"select error!"<<endl;
        }
        else
        {
            if(!(mres=mysql_store_result(&mysql)))
            {
                cout<<"Couldn`t get result from "<<mysql_error(&mysql)<<endl;
            }
            else
            {
                char* str_field[32];
                MYSQL_FIELD* mf;

                while(column = mysql_fetch_row(mres))
                {
                    for(int i = 0;i < mysql_num_fields(mres); i++)
                    {

                        if(mysql_num_fields(mres)!= (i+1))
                        {
                            st += column[i];
                            st += ",";
                        }
                        else
                        {
                            st += column[i];
                            st += "\n";
                        }

                    }

                }
                cout<<st<<endl;
                mysql_free_result(mres);

            }
        }
    return st;

}




void mysql_act::freeMysql()
{
    mysql_close(&mysql);
}
