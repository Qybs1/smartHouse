#include "ctlDevices.h"
/*
struct ctlDevices
{
	char deviceName[128];

	int status;
	int (*open)();
	int (*close)();
	int (*deviceInit)();

	int (*readStatus)();
	int (*changeStatus)(int status);

	struct ctlDevices *next;
};
*/
int bathroomLightOpen()
{

}
int bathroomLightClose()
{

}
int bathroomLightCloseInit()
{

}
int bathroomLightCloseStatus(int status)
{

}


struct Devices bathroomLight = {

	.name = "bathroomLight",
	.open = bathroomLightOpen,
	.close = bathroomLightClose,
	.deviceInit = bathroomLightCloseInit,
	.changeStatus = bathroomLightCloseStatus
}

struct Devices* addBathroomLightToLink(struct Devices *phead)
{
	if(phead == NULL){
		return &bathroomLight;
	}else{
		bathroomLight.next = phead;
		phead = bathroomLight;
	}	
}
