#include <stdio.h>
#include <string.h>
#include "ctlDevices.h"
int main()
{

	char *name;

	struct Devices *pdevicesHead = NULL;
	pdevicesHead = addBathroomLightToLink();

	//1.指令工厂初始化

	//2.设备控制工厂初始化

	//3.线程池建立
	//3.1语音线程

	//3.2socket线程

	//3.3摄像头线程
	
	//3.4火灾线程

	return 0;
}
