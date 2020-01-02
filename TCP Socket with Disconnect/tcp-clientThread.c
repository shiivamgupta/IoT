#include <stdio.h>
#include<pthread.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <netinet/in.h>  //Structure
#include <arpa/inet.h>  //inet_addr
#include <unistd.h> // read and write
#include <stdlib.h> //exit
#include <strings.h>  //bzero
#include <string.h> 
#define BUFFER_SIZE 1024  //buffer for read and write operations
#define PORT 4000   //port number of SERVER, is listening
char sendbuffer[1024];
char recvbuffer[1024];
int sockfd;
pthread_t t1,t2;
/*-----------fork system call return type---*/


/*
Error Handler/routine
*/
void error(char *msg)
{
	perror(msg);
	exit(1);
}

void *sender(void *arg);	
void *receiver(void *arg);

int main(int argc, char *argv[])
{
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE];
	/*
	detailed information about
	Socket Structure - Refer:
	man 7 ip
	*/
	//Creation of Socket
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
{
	error("Socket creation failed");
}
else
{
	printf("socket Created Successfully\n");
}

//clear/flush the strucrure memory
bzero(&serv_addr, sizeof(serv_addr));

/*Assigning IP address and PORT */
serv_addr.sin_family = AF_INET;
/*
man 3 inet_addr
inet_addr : converts IPV4 dotted decimal format
into binary (network byte order)
*/

serv_addr.sin_addr.s_addr = inet_addr("192.168.75.244");

serv_addr.sin_port = htons(PORT);

/*
connect the client socket to the server Socket
*/

int retcon = connect(sockfd, (struct sockaddr*)
&serv_addr, sizeof(serv_addr));
if(retcon < 0 )
{
	error("Connection to server Socket Failed");
}
else
{
	printf("Connected to Server successfully \n");
}

	int t_stat1 = pthread_create(&t1, NULL, sender, NULL);
	
	if(t_stat1){
		perror("Thread:Sender creation failure!");
		exit(1);
	}
	else
	{
		printf("Thread_1:Sender created successfully\n");
	}
	
	int t_stat2 = pthread_create(&t2, NULL, receiver, NULL);
	if(t_stat2){
		perror("Thread 2:Receiver creation failure!");
		exit(1);
	}
	else
	{
		printf("Thread_2:Receiver created successfully\n");
	}
	

	void *stat1,*stat2;
	pthread_join(t1, stat1);
	pthread_join(t2, stat2);

	//close the socket file descriptor
	close(sockfd);
}

void *sender(void *arg){	
	while(1){
		bzero(&sendbuffer, sizeof(sendbuffer));
		// Send the data from from client to server
        	printf("Enter the message : ");
		fgets(sendbuffer,1024,stdin);
		send(sockfd,sendbuffer,strlen(sendbuffer)+1,0);
	}

}


void *receiver(void *arg){
	while(1){
		bzero(&recvbuffer, sizeof(recvbuffer));
		// Receive the data from client and print 
		recv(sockfd,recvbuffer,sizeof(recvbuffer),0);
    	   	printf("Server Msg: %s\t",recvbuffer);
	}	
}


