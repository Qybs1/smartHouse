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

int voiceGetCommand(struct inputCommander *voicectl)
{
	int nread = 0;
	
	nread = read(voicectl->fd,voicectl->command,sizeof(voicectl->command));

	return nread;
	
}

int voiceInit(struct inputCommander *voicectl, char *ipAdress, char *port)
{
	int fd;

	if((fd = serialOpen(voicectl->deviceName, 9600)) == -1){
		exit(-1);
	}

	voicectl->fd = fd;
	printf("fd =%d vfd =%d \n",fd,voicectl->fd);
	return fd;
}

struct inputCommander voicectl = {
	.commandName = "voice",
	.deviceName = "/dev/ttyAMA0",	
	.command = {'\0'},
	.Init = voiceInit,
	.getCommand = voiceGetCommand,
	.log = {'\0'},
	.next = NULL
};

struct inputCommander* addVoiceCommandToLink(struct inputCommander *phead)
{
	if(phead == NULL){
		return &voicectl;
	}else{
		voicectl.next = phead;
		phead = &voicectl;
	}	
}

