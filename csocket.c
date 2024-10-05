#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/socket.h>

#define PORT 9999

int main(int argc, char const* argv[]){
//		Creating a socket() 			        //
/////////////////////////////////////////////////////////////////
//	Defining necessary variables before creating a socket //
	int server_fd, new_socketfd;
	ssize_t valread;
	struct sockaddr_in server;
	int opt=1;
	socklen_t serverlen = sizeof(server);
	char buffer[2048] = {0};
	char* hello = "Hey are you trying to connected to server ?";
	
	//Creating a socket
	if((server_fd = socket(AF_INET,SOCK_STREAM,0))<0){
		perror("socket connection failed");
		exit(EXIT_FAILURE);
	}

	//Reusing or forcefully using the same IP and port again
	if(setsockopt(server_fd,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		perror("SETSOCKOPT ERROR");
		exit(EXIT_FAILURE);
	
	}
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
/////////////////////////////////////////////////////////////////////////////////////
			//BIND//


	if(bind(server_fd, (struct sockaddr*)&server, sizeof(server))<0){
		perror("Binding failed");
		exit(EXIT_FAILURE);
	}
	printf("Listening on %d\n",PORT);
	////////////LISTEN////////////
	if(listen(server_fd,5) < 0){
		perror("Listening failed");
		exit(EXIT_FAILURE);
	}
	while(1){	
	////////ACCEPT CONNECTION FROM CLIENT//////////
	if((new_socketfd = accept(server_fd, (struct sockaddr*)&server,&serverlen))<0){
			printf("\n%d\n",new_socketfd);
			perror("Connection cannot be established\n ");
			exit(EXIT_FAILURE);
	}
	//	Reading  the bytes send by client //
	valread = read(new_socketfd, buffer, 2048-1);
	printf("%s\n", buffer);
	// sending the response to client //
	send(new_socketfd,hello, strlen(hello),0);
	printf("Sent successfully\n\a");
	close(new_socketfd);}
	
return 0;
}
