// ListenUsb.cpp : �������̨Ӧ�ó������ڵ㡣
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

