#include "inputCommand.h"
/*
struct inputCommander
{
	char commandName[128];
	char command[32];
	char log[1024];
	char deviceName[128];

	int fd;
	int (*Init)(char *name, char *ipAdress, char *port);
	int (*getCommand)(char *cmd);
	struct inputCommander *next;
};
*/

int socketGetCommand(struct inputCommander *socketMsg)
{
	int c_fd;
	int n_read;
	
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in));
	int clen = sizeof(struct sockaddr_in);
	//4.accept
	c_fd = accept(socketMsg->sfd,(struct sockaddr *)&c_addr,&clen);

	//5.read
	n_read = read(c_fd,socketMsg->command, sizeof(socketMsg->command));
	if(n_read == -1){
		perror("read");
	}else if(n_read > 0){
		printf("\nget: %d\n",n_read);
	}else{
		printf("client quit\n");
	}
	return n_read;
	
}

int socketInit(struct inputCommander *socketMsg, char *ipAdress, char *port)
{
	int s_fd;
	struct sockaddr_in s_addr;
	memset(&s_addr,0,sizeof(struct sockaddr_in));

	//1.socket
	s_fd = socket(AF_INET,SOCK_STREAM,0);
	if(s_fd == -1){
		perror("socket");
		exit(-1);
	}		
	
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(socketMsg->port));
	inet_aton(socketMsg->ipAddress,&s_addr.sin_addr);

	//2.bind
	bind(s_fd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));

	//3.listen
	listen(s_fd,10);
	printf("Socket Server listening......\n");

	socketMsg->sfd = s_fd;
	return s_fd;
}

struct inputCommander socketctl = {
	.commandName = "socketServer",
	.command = {'\0'},
	.ipAddress = "192.168.10.66",
	.port = "8088",
	.Init = socketInit,
	.getCommand = socketGetCommand,
	.log = {'\0'},
	.next = NULL
};

struct inputCommander* addSocketToLink(struct inputCommander *phead)
{
	if(phead == NULL){
		return &socketctl;
	}else{
		socketctl.next = phead;
		phead = &socketctl;
	}	
}


