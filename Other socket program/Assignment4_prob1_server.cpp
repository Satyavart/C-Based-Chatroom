#include<bits/stdc++.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
using namespace std;
int Buffer_size = 512;


void sendfile(char *file,int socket){
    FILE *f = fopen(file, "rb");
    fseek(f, 0, SEEK_END);
    unsigned long filesize = ftell(f);
    send(socket,&filesize,sizeof(filesize),0);
    char *buffer = (char*)malloc(sizeof(char)*filesize);
    rewind(f);
    fread(buffer,sizeof(char),filesize,f);
    int sent=0;
    while(sent<filesize){
        unsigned long remaining = filesize-sent; int n;
        if(remaining<Buffer_size) n = send(socket,buffer,remaining,0);
        else n=send(socket,buffer+sent,Buffer_size-1,0);
        if(n==-1){char a[100]="!!!!";  send(socket,a,sizeof(a),0);}
        sent += n;
    }
    fclose(f);
    
}

void recivefile(int socket, char *file){
    unsigned filesize;
    recv(socket,&filesize,sizeof(filesize),0);
    int recieved=0,remaining=0;
    FILE *filename=fopen(file,"wb");
    while(recieved<filesize){
        remaining = filesize - recieved ;
        char a[1024]; int n;
        if(remaining < Buffer_size) n=recv(socket,a,remaining,0);
        else n=recv(socket,a,Buffer_size-1,0);
        recieved += n;
        fwrite(a,1,sizeof(a),filename);
        
    }
    fclose(filename);

}

int main(){
    int socket_server;
    socket_server =socket(AF_INET,SOCK_STREAM,0);

    //defining address
    struct sockaddr_in server_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(8095);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    //bind ip and port
    bind(socket_server,(struct sockaddr *)&server_addr,sizeof(struct sockaddr_in));

    //listening
    listen(socket_server,8);

    //accepting connection
    int client;
    client=accept(socket_server,NULL,NULL);

    char a[5],file[100];
    recv(client,a,sizeof(a),0); //recieving download or upload info
    recv(client,file,sizeof(file),0); //recieving file name

    //uploading on server
    if(strcmp(a,"put")==0){
        recivefile(client,file);
    }
    if(strcmp(a,"get")==0){
        sendfile(file,client);
    }


    int close(client);
    return 0;
}