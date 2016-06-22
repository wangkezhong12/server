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


bool mysql_act::mysql_search(const char* query,int colnum)
{
    const char * sql = query;
    if(NULL != sql)
    {
        cout<<"sql:"<<sql<<endl;
        if(mysql_query(&mysql,sql))
        {
            cout<<"select error!"<<endl;
            return false;
        }
        else
        {
            if(!(mres=mysql_store_result(&mysql)))
            {
                cout<<"Couldn`t get result from "<<mysql_error(&mysql)<<endl;
                return false;
            }
            else
            {
                char* str_field[32];
                MYSQL_FIELD* mf;

                string st = "";
                while(!(mf = mysql_fetch_field(mres)))
                {
                    mfield_v.push_back(mf);
                }
                for (vector<MYSQL_FIELD*>::size_type it = 0;it != mfield_v.size() ; ++it)
                {
                    str_field[it] = mfield_v[it]->name;
                    cout<<"str_field["<<it<<"] is: "<<str_field[it];
                }

                while(column = mysql_fetch_row(mres))
                {
                    //st = column[0]+","+column[1]+","column[2]+","column[3]+","column[4]+"\n";
                   // st = column[0]+","+column[1]+"\n";
                    for(int j = 0;j < colnum;j++)
                    {

                        if(j != (colnum-1))
                        {
                            st.append(column[j]);
                            st.append(",");
                        }
                        else
                        {
                            st.append(column[j]);
                            st.append("\n");
                        }

                    }

                   // cout<<column[0]<<"  "<<column[1]<<st<<endl;
                }
              //  cout<<st<<endl;
                res_str = st;
                mysql_free_result(mres);
                return true;
            }

        }
    }
    else
    {
        return false;
    }
}






void mysql_act::freeMysql()
{
    mysql_close(&mysql);
}
