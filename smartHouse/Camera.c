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
int CameraOpen()
{

}
int CameraClose()
{

}
int CameraCloseInit()
{

}
int CameraCloseStatus(int status)
{

}


struct ctlDevices Camera = {
	.deviceName = "Camera",
	.open = CameraOpen,
	.close = CameraClose,
	.deviceInit = CameraCloseInit,
	.changeStatus = CameraCloseStatus
};

struct ctlDevices* addCameraToLink(struct ctlDevices *phead)
{
	if(phead == NULL){
		return &Camera;
	}else{
		Camera.next = phead;
		phead = &Camera;
	}	
}
