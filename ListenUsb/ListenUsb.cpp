// ListenUsb.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GetWmiInfo.h"


int _tmain(int argc, _TCHAR* argv[])
{
	GetWmiInfo wmiInfo;
	wmiInfo.wmiInit();
	wmiInfo.ListenUSBdeviceStatu();
	wmiInfo.wmiRelease();
	return 0;
}

