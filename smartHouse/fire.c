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

int fireIforNotInit(int pinNum)
{
	pinMode(pinNum,INPUT);
	digitalWrite(pinNum,HIGH);
}
int fireReadStatus(int pinNum)
{
	return digitalRead(pinNum);
}

struct ctlDevices fireIforNot = {

	.deviceName = "fireIforNot",
	.pinNum = 25,
	.deviceInit = fireIforNotInit,
	.readStatus = fireReadStatus
};

struct ctlDevices* addFireToLink(struct ctlDevices *phead)
{
	if(phead == NULL){
		return &fireIforNot;
	}else{
		fireIforNot.next = phead;
		phead = &fireIforNot;
	}	
}

