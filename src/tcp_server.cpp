
#include "tcp_server.h"


using namespace std;

tcp_server::tcp_server(int listen_port) {

        if(( socket_fd = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0 ){
                throw "socket() failed";
        }

        memset(&myserver,0,sizeof(myserver));
        myserver.sin_family = AF_INET;
        myserver.sin_addr.s_addr = htonl(INADDR_ANY);
        myserver.sin_port = htons(listen_port);

        if( bind(socket_fd,(sockaddr*) &myserver,sizeof(myserver)) < 0 ) {
                throw "bind() failed";
        }

        if( listen(socket_fd,10) < 0 ) {
                throw "listen() failed";
        }
}


int tcp_server::recv_msg() {

        while( 1 ) {

                socklen_t sin_size = sizeof(struct sockaddr_in);
                if(( accept_fd = accept(socket_fd,(struct sockaddr*) &remote_addr,&sin_size)) == -1 )
                {
                        throw "Accept error!";
                        continue;
                }
        //        printf("Received a connection from %s\n",(char*) inet_ntoa(remote_addr.sin_addr));
                cout<<"Received a connection from"<<(char*) inet_ntoa(remote_addr.sin_addr)<<endl;
            /*
                if( !fork() ) {
                        char buffer[MAXSIZE];
                        memset(buffer,0,MAXSIZE);
                        if( ( read(accept_fd,buffer,MAXSIZE)) < 0 ) {
                                throw("Read() error!");
                        } else {
                               // printf("Received message: %s\n",buffer);
                                cout<<"Received message:"<<buffer<<endl;
                                break;
                        }
                        exit(0);
                }
                */
                char buffer[MAXSIZE];
                n = recv(accept_fd,buffer,MAXSIZE,0);
                buffer[n] = '\0';


                close(accept_fd);
        }
        return 0;
}



int tcp_server::recv_msg(mysql_act ma,int colnum)
{
    cout<<"listening...... "<<endl;
    while(1) {

            socklen_t sin_size = sizeof(struct sockaddr_in);
            if(( accept_fd = accept(socket_fd,(struct sockaddr*) &remote_addr,&sin_size)) == -1 )
            {
                    throw "Accept error!";
                    continue;
            }
        //        printf("Received a connection from %s\n",(char*) inet_ntoa(remote_addr.sin_addr));
            cout<<"Received a connection from"<<(char*) inet_ntoa(remote_addr.sin_addr)<<endl;
            /*
                if( !fork() ) {
                        char buffer[MAXSIZE];
                        memset(buffer,0,MAXSIZE);
                        if( ( read(accept_fd,buffer,MAXSIZE)) < 0 ) {
                                throw("Read() error!");
                        } else {
                               // printf("Received message: %s\n",buffer);
                                cout<<"Received message:"<<buffer<<endl;
                                break;
                        }
                        exit(0);
                }
                */
            cout<<"connect socket!"<<endl;
            char buffer[MAXSIZE];
            n = recv(accept_fd,buffer,MAXSIZE,0);
            buffer[n] = '\0';
            cout<<*buffer<<endl;
            ma.mysql_search(buffer,colnum);
            string mares = ma.res_str;
            cout<<"mares:"<<mares<<endl;
           // const char* pstr = mares.c_str();
            char* sl= new char[mares.size()];
            for(int k = 0; k<mares.size();++k)
            {
                sl[k]=mares.at(k);
            }
            //cout<<"pstr:"<<sl<<endl;
            send_buff(accept_fd,sl,ma.res_str.length());
            close(accept_fd);
        }
    return 0;
}

int tcp_server::send_buff(int socketi,char* buff,int sendlen)
{
    int len = 0;
    int one = 1024;
    do
    {
        if(sendlen-len >1024)
        {
            one = 1024;
        }
        else
        {
            one = sendlen-len;
        }
        send(socketi,buff,one,0);
        len += one;
        buff += one;
    }while(len<sendlen);
    return len;
}
