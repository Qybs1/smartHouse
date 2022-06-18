#include "ctlDevices.h"
#include <stdlib.h>
int diningroomLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int diningroomLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
}
int diningroomLightCloseInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
}
int diningroomLightCloseStatus(int status)
{

}


struct ctlDevices diningroomLight = {

	.deviceName = "diningroomLight",
	.open = diningroomLightOpen,
	.pinNum = 24,
	.close = diningroomLightClose,
	.deviceInit = diningroomLightCloseInit,
	.changeStatus =diningroomLightCloseStatus
};

struct ctlDevices* addDiningroomLightToLink(struct ctlDevices *phead)
{
	if(phead == NULL){
		return &diningroomLight;
	}else{
		diningroomLight.next = phead;
		phead = &diningroomLight;
	}	
}

