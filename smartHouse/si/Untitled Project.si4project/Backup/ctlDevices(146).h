#include <wiringPi.h>

struct ctlDevices
{
	char deviceName[128];
	int pinNum;
	int status;
	
	int (*open)(int pinNum);
	int (*close)(int pinNum);
	int (*deviceInit)(int pinNum);
	
	int (*readStatus)();
	int (*changeStatus)(int status);

	struct ctlDevices *next;
};
struct Devices* addBathroomLightToLink(struct Devices *phead)

