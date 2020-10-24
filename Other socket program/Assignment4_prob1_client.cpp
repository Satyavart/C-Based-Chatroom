#include<bits/stdc++.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
using namespace std;

int Buffer_size = 512;
void error(char *msg){
    perror(msg);
    exit(1);

}

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
        if(n==-1) error("File Not exist");  
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
        if(strcmp(a,"!!!!")==0) {cout<<"File noT Exist"; return ;}
        recieved += n;
        fwrite(a,1,sizeof(a),filename);
        
    }
    fclose(filename);

}

int main(int argc, char** argv){
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    //getting values
    char* IP=argv[1];
    int port=atoi(argv[2]);
    char file[100];
    strcpy(file,argv[4]);

    /*for(int i=0;i<argc;i++){
        cout<<argv[i]<<": ";
        for(int j=0;j<8;j++){
            cout<<int(argv[i][j])<<" ";
        }
        cout<<endl;
    }*/

    int net_socket;
    //creating socket
    net_socket=socket(AF_INET,SOCK_STREAM,0);

    //Error #1
    if (net_socket < 0) error("ERROR opening socket");

    //defining address
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(8095);
    //server_address.sin_addr.s_addr=INADDR_ANY;
    
    //any IP
    if(strcmp(IP,"INADDR_ANY")==0)  server_address.sin_addr.s_addr=INADDR_ANY;
    //specific IP
    else server_address.sin_addr.s_addr=inet_addr(IP);

    //connecting
    int status = connect(net_socket,(struct sockaddr*)&server_address,sizeof(struct sockaddr_in));
    if(status == -1) {printf("\nConeection error \n"); return 0;}

    cout<<"\nConnected \n";

    char a[5];
    strcpy(a,argv[3]);
    send(net_socket,a,sizeof(a),0); //sending download or upload info
    send(net_socket,file,sizeof(file),0);  //sending file name

    //Uploading on server
    if(strcmp(argv[3],"put")==0){
        cout<<"Uploading file";
        sendfile(file,net_socket);
        cout<<"\nFile Uploaded";
    }
    if(strcmp(argv[3],"get")==0){
        cout<<"Downloadinf file";
        recivefile(net_socket,file);
        cout<<"\nFile Downloaded";
    }

}