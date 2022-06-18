

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
