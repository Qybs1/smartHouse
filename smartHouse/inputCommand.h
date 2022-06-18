#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <wiringSerial.h>

struct inputCommander
{
	char commandName[128];
	char command[32];
	char log[1024];
	char deviceName[128];
	char port[12];
	char ipAddress[32];

	int fd;
	int sfd;
	int (*Init)(struct inputCommander *voicectl, char *ipAdress, char *port);
	int (*getCommand)(struct inputCommander *voicectl);
	struct inputCommander *next;
};

struct inputCommander* addVoiceCommandToLink(struct inputCommander *phead);
struct inputCommander* addSocketToLink(struct inputCommander *phead);

