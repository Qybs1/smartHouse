#include "ctlDevices.h"
int upstairLightOpen(int pinNum)
{
	digitalWrite(pinNum,LOW);
}
int upstairLightClose(int pinNum)
{
	digitalWrite(pinNum,HIGH);
}
int upstairLightCloseInit(int pinNum)
{
	pinMode(pinNum,OUTPUT);
	digitalWrite(pinNum,HIGH);
}
int upstairLightCloseStatus(int status)
{

}


struct ctlDevices upstairLight = {

	.deviceName = "upstairLight",
	.open = upstairLightOpen,
	.pinNum = 21,
	.close = upstairLightClose,
	.deviceInit = upstairLightCloseInit,
	.changeStatus = upstairLightCloseStatus
};

struct ctlDevices* addUpstairLightToLink(struct ctlDevices *phead)
{
	if(phead == NULL){
		return &upstairLight;
	}else{
		upstairLight.next = phead;
		phead = &upstairLight;
	}	
}

