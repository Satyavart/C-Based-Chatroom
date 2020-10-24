#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
    int ser_socket;

    //creating socket
    ser_socket=socket(AF_INET,SOCK_STREAM,0)
    
    //specifing server address
    struct sock_add server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8080);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    //binding
    bind(ser_socket,(struct sockaddr *)&server_addr,sizeof(struct sock_add));
    
    //listening
    listen(ser_socket,5);

    //accepting connection
    int client_socket;
    client_socket = accept(ser_socket,NULL,NULL);

    //Verifing user
    char *pass; char *out;
    recv(client_socket,&pass,sizeof(pass),0);
    if(pass!=password) out="-1";
    else out="Congrats!!! Successfully Logged in\n";
    send(client_socket,&out,sizeof(out),0);


    //task
    char *mess_recieved; char *mess_send="Hello";
    recv(client_socket,&mess_recived,sizeof(mess_recived),0);
    if(mess_recieved=="Hi"){
        send(client_socket,&mess_send,sizeof(mess_send),0);
    }
    

    //closing connection
    close(ser_socket);
    
    return 0;
}