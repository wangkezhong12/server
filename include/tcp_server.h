#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "mysql_act.h"

#define MAXSIZE 4096

class tcp_server
{
private:
        int socket_fd,accept_fd;
        sockaddr_in myserver;
        sockaddr_in remote_addr;
        int n;

public:
        tcp_server(int listen_port);
        int recv_msg();
        int recv_msg(mysql_act ma);
        int send_buff(int socketi,char* buffer,int sendlen);
};
