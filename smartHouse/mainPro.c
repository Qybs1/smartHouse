#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "ctlDevices.h"
#include "inputCommand.h"

struct inputCommander *pcommandHead  = NULL;
struct ctlDevices     *pdevicesHead  = NULL;
struct inputCommander *socketHandler = NULL;
struct inputCommander *voiceHandler  = NULL;
int c_fd;

struct ctlDevices* findDevicesByName(char *name, struct ctlDevices *phead)
{
	struct ctlDevices *tmp = phead;
	
	if(phead == NULL){
		return NULL;
	}else{
		while(tmp != NULL){
			if(strcmp(tmp->deviceName,name) == 0){
				return tmp;
			}
			tmp = tmp->next;
		}
		return NULL;
	}
}

struct inputCommander* findCommandByName(char *name, struct inputCommander *phead)
{
	struct inputCommander *tmp = phead;
	
	if(phead == NULL){
		return NULL;
	}else{
		while(tmp != NULL){
			if(strcmp(tmp->commandName,name) == 0){
				return tmp;
			}
			tmp = tmp->next;
		}
		return NULL;
	}
}


void *voice_thread(void *arg)
{
	int nread;

	voiceHandler = findCommandByName("voice", pcommandHead);

	if(voiceHandler == NULL){
		printf("find voiceHandler error\n");
		pthread_exit(NULL);
	}else{
		if(voiceHandler->Init(voiceHandler,NULL,NULL) < 0){
			printf("voice init error\n");
			pthread_exit(NULL);
		}else{
			printf("%s init success\n",voiceHandler->commandName);
		}
		while(1){
			nread = voiceHandler->getCommand(voiceHandler);
			if(nread < 0){
				printf("no data from voice\n");
			}else{
				printf("do device control:%s\n",voiceHandler->command);
			}
			memset(voiceHandler->command,'\0',sizeof(voiceHandler->command));
		}
	}

}
void *read_thread(void *arg)
{
	int n_read = 0;
	while(1){
		memset(socketHandler->command, '\0',sizeof(socketHandler->command));
		n_read = read(c_fd,socketHandler->command, sizeof(socketHandler->command));
		if(n_read == -1){
			perror("read");
		}else if(n_read > 0){
			printf("\nget: %d,%s\n",n_read,socketHandler->command);
		}else{
			printf("client quit\n");
			break;
		}
	}
}

void *socket_thread(void *arg)
{
	socketHandler = findCommandByName("socketServer", pcommandHead);
	if(socketHandler == NULL){
		printf("find socketHandler error\n");
		pthread_exit(NULL);
	}else{
		printf("%s init success\n",socketHandler->commandName);
	}
	socketHandler->Init(socketHandler,NULL,NULL);
		
	pthread_t readThread;
	struct sockaddr_in c_addr;
	memset(&c_addr,0,sizeof(struct sockaddr_in));
	int clen = sizeof(struct sockaddr_in);
	
	while(1){
		//4.accept
		c_fd = accept(socketHandler->sfd,(struct sockaddr *)&c_addr,&clen);
		//5.read
		pthread_create(&readThread,NULL,read_thread,NULL);
	}
	
}

int main()
{

	char name[128];

	if(wiringPiSetup() == -1){
		return -1;
	}
	
	struct ctlDevices *tmp = NULL;
	pthread_t voiceThread;
	pthread_t socketThraed;

	//1.设备工厂初始化
	pdevicesHead = addBathroomLightToLink(pdevicesHead);
	pdevicesHead = addUpstairLightToLink(pdevicesHead);
	pdevicesHead = addLivingroomLightToLink(pdevicesHead);
	pdevicesHead = addDiningroomLightToLink(pdevicesHead);
	pdevicesHead = addFireToLink(pdevicesHead);


	//2.指令工厂初始化
	pcommandHead = addVoiceCommandToLink(pcommandHead);
	pcommandHead = addSocketToLink(pcommandHead);

	//int pthread_create(pthread_t *thread,const pthread_attr_t *attr,void *(*start_routine) (void *),void *arg);
	//3.1语音线程	
	pthread_create(&voiceThread,NULL,voice_thread,NULL);
	
	//3.2socket线程
	pthread_create(&socketThraed,NULL,socket_thread,NULL);

	pthread_join(voiceThread,NULL);
	pthread_join(socketThraed,NULL);

	return 0;
}
