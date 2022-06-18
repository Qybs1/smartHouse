#include <wiringPi.h>
#include <stdlib.h>
struct ctlDevices
{
	char deviceName[128];
	int pinNum;
	int status;
	
	int (*open)(int pinNum);
	int (*close)(int pinNum);
	int (*deviceInit)(int pinNum);
	
	int (*readStatus)(int pinNum);
	int (*changeStatus)(int status);

	struct ctlDevices *next;
};

struct ctlDevices* addBathroomLightToLink(struct ctlDevices *phead);
struct ctlDevices* addUpstairLightToLink(struct ctlDevices *phead);
struct ctlDevices* addLivingroomLightToLink(struct ctlDevices *phead);
struct ctlDevices* addDiningroomLightToLink(struct ctlDevices *phead);
struct ctlDevices* addFireToLink(struct ctlDevices *phead);

