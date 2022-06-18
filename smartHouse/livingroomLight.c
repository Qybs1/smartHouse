#include "ctlDevices.h"
int livingLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int livingLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
}
int livingLightCloseInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
}
int livingLightCloseStatus(int status)
{

}


struct ctlDevices livingLight = {

	.deviceName = "livingLight",
	.open = livingLightOpen,
	.pinNum = 23,
	.close = livingLightClose,
	.deviceInit = livingLightCloseInit,
	.changeStatus =livingLightCloseStatus
};

struct ctlDevices* addLivingroomLightToLink(struct ctlDevices *phead)
{
	if(phead == NULL){
		return &livingLight;
	}else{
		livingLight.next = phead;
		phead = &livingLight;
	}	
}

