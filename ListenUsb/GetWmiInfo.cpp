#include "stdafx.h"
#include "GetWmiInfo.h"


GetWmiInfo::GetWmiInfo(void){

}

void GetWmiInfo::wmiInit(){
	hres = CoInitializeEx(0,COINIT_MULTITHREADED);
	if (FAILED(hres))
	{
		cout << "Failed to init COM libray."
		<<"Error cod =0x"<<hex<<hres<<endl;
		return ;
	}
	hres = CoInitializeSecurity(
		NULL,
		-1,
		NULL,
		NULL,
		RPC_C_PROTECT_LEVEL_DEFAULT,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE,
		NULL
		);
	if (FAILED(hres))
	{
		cout << "Failed to init security."
		<<"Error cod =0x"<<hex<<hres<<endl;
		CoUninitialize();
		return ;
	}
	
	hres = CoCreateInstance(
			CLSID_WbemLocator,
			0,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator,
			(LPVOID *)&pLoc
		);
	if (FAILED(hres))
	{
		cout << "Failed to create IWbemLocator object."
		<<"Error cod =0x"<<hex<<hres<<endl;
		CoUninitialize();
		return ;
	}
	
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"),
		NULL,
		NULL,
		0,
		NULL,
		0,
		0,
		&pSvc
		);
	if (FAILED(hres))
	{
		cout << "Could not connct."
		<<"Error cod =0x"<<hex<<hres<<endl;
		pLoc->Release();
		CoUninitialize();
		return ;
	}
	hres = CoSetProxyBlanket(
		pSvc,
		RPC_C_AUTHN_WINNT,
		RPC_C_AUTHZ_NONE,
		NULL,
		RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL,
		EOAC_NONE
		);
	if (FAILED(hres))
	{
		cout << "Could not proxy blancket."
		<<"Error cod =0x"<<hex<<hres<<endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ;
	}
	cout<<"Connected!"<<endl;
}
void GetWmiInfo::wmiRelease(){
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return ;
}
void GetWmiInfo::ListenUSBdeviceStatu(){
	IUnsecuredApartment * pUnsecApp = NULL;
	hres  = CoCreateInstance(
		CLSID_UnsecuredApartment,
		NULL,
		CLSCTX_LOCAL_SERVER,
		IID_IUnsecuredApartment,
		(void**)&pUnsecApp);
	EventSink* pSink = new EventSink;
	pSink->AddRef();
	IUnknown * pStubUnk = NULL;
	pUnsecApp->CreateObjectStub(pSink,&pStubUnk);
	IWbemObjectSink *pStubSink = NULL;
	pStubUnk->QueryInterface(IID_IWbemObjectSink,(void**)&pStubSink);
	hres = pSvc->ExecNotificationQueryAsync(
		_bstr_t("WQL"),
		_bstr_t("SELECT*"
			"from Win32_DeviceChangeEvent"),
			WBEM_FLAG_SEND_STATUS,
			NULL,
			pStubSink
		);
	Sleep(10000);
	hres=pSvc->CancelAsyncCall(pStubSink);
	pUnsecApp->Release();
	pStubUnk->Release();
	pSink->Release();
	pStubSink->Release();
	return ;

}

GetWmiInfo::~GetWmiInfo(void){
}
