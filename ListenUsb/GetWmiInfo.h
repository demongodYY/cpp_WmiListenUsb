#pragma once

#include "EventSink.h"

class GetWmiInfo
{
public:
	GetWmiInfo(void);
	~GetWmiInfo(void);
	void wmiInit(void);
	void ListenUSBdeviceStatu(void);
	void wmiRelease(void);
private:
	HRESULT hres;
	IWbemLocator *pLoc;
	IWbemServices *pSvc;
};

