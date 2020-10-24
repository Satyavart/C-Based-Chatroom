#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
    int net_socket;

    //creating socket
    net_socket=socket(AF_INET,SOCK_STREAM,0)
    
    //specifing server address
    struct sock_add server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    //connnecting
    int status=connect(net_socket,(struct sockaddr *)&server_addr,sizeof(struct sock_add));

    //verifying connection 
    if(status==-1){
        printf("Connection Unavialabe\n");
        return -1;
    }

    //Task
    while(1){
        char *ip; char *out;
        printf("Type 'exit' to leave the connectioN \n");
        printf("Enter IPv6 address: ");

        //closing connection
        if(ip=="exit"){
            ip="exit";
            send(net_socket,&ip,sizeof(ip),0);
            close(net_socket);
            return 0;
        }
        
        scanf("%s",ip);
        send(net_socket,&ip,sizeof(ip),0);
        recv(net_socket,&out,sizeof(out),0);
        printf("IP : %s",out);
    }
   
}