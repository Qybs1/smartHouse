#include "ctlDevices.h"
/*
struct ctlDevices
{
	char deviceName[128];

	int status;
	int (*open)(int pinNum);
	int (*close)(int pinNum);
	int (*deviceInit)(int pinNum);
	int pinNum;
	int (*readStatus)();
	int (*changeStatus)(int status);

	struct ctlDevices *next;
};
*/
int bathroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int bathroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
}
int bathroomLightCloseInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
}
int bathroomLightCloseStatus(int status)
{

}


struct ctlDevices bathroomLight = {

	.deviceName = "bathroomLight",
	.open = bathroomLightOpen,
	.pinNum = 22,
	.close = bathroomLightClose,
	.deviceInit = bathroomLightCloseInit,
	.changeStatus = bathroomLightCloseStatus
};

struct ctlDevices* addBathroomLightToLink(struct ctlDevices *phead)
{
	if(phead == NULL){
		return &bathroomLight;
	}else{
		bathroomLight.next = phead;
		phead = &bathroomLight;
	}	
}
