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

    // authencticating user
    char *pass; char *result;
    printf("Enter password : ")
    scanf("%s",pass);
    send(net_socket,&pass,sizeof(pass),0);
    recv(net_socket,&result,sizeof(result),0);
    if(result=='-1'){
        printf("Wrong Password");
        close(net_socket);
        return -1;
    }

    //task
    char *mess_send="Hi"; char *mess_recived;
    send(net_socket,&mess_send,sizeof(mess_send),0);
    recv(net_socket,&mess_recived,sizeof(mess_recived),0);
    printf("%s",mess_recived);

    //closing connection
    close(net_socket);
    
    return 0;
}