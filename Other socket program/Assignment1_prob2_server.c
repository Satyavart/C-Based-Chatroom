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

    while(1){
        //task
        char *ip_res; char *ip_send=""; 
        recv(client_socket,&ip_res,sizeof(ip_res),0);

        //closing connection
        if(ip_res=="exit"){
            close(ser_socket);
            return 0;
        }

        //algo
        if(sizeof(ip_res)==39){
            int prev=0,ind=0; char *ans="";
            for(int i=38;i>=4;i--){
                if(ip_res[i]=="0"&&ip_res[i-1]=="0"&&ip_res[i-2]=="0"&&ip_res[i-3]=="0"){
                    if(prev==0){
                        prev++;
                        i=i-4; ans+=":";
                    }
                    if(prev==1) { i=i-4; ans+=":"; }
                }
                else{
                    ans+=ip[i]; prev=0;
                }
            }
            for(int i=sizeof(ans)-1;i>=0;i--) ip_send+=ans[i];
        }
        else{
            int col=0,in=0;
            for(int i=0;i<sizeof(ip_res),i++){
                if(ip_res[i]==":") col++;
            }
            col=7-col+1;
            for(int i=0;i<sizeof(ip_res);i++){
                if(ip_res[i]=="0"&&ip_res[i+1]==":"&&in<2){
                    ip_send+="0000";
                }
                else{
                    ip_send+=ip_res[i]; in++;
                }
                if(ip_res[i]==":"){ ip_send+=":"; in=0;}
                if(ip_res[i]==":"&&ip_res[i+1]==":"){
                    while(col--){
                        ip_send+="0000:";
                    }
                    in=0; i++;
                }
            }
        }

        send(client_socket,&ip_send,sizeof(ip_send),0);
    }
}