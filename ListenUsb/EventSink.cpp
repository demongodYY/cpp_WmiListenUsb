#include "stdafx.h"
#include "EventSink.h"


ULONG EventSink::AddRef(){
	return InterlockedIncrement(&m_lRef);	
}

ULONG EventSink::Release(){
	LONG lRef = InterlockedDecrement(&m_lRef);
	if(lRef == 0){
		delete this;
	}
	return lRef;
}
HRESULT  EventSink::QueryInterface(REFIID riid,void** ppv){
	if(riid == IID_IUnknown || riid == IID_IWbemObjectSink){
		*ppv = (IWbemObjectSink *)this;
		AddRef();
		return WBEM_S_NO_ERROR;
	}
	else return E_NOINTERFACE;

} 
HRESULT EventSink::Indicate(
			LONG lObjectCount,
			IWbemClassObject __RPC_FAR *__RPC_FAR *apObjectArray
			){
	HRESULT hres = S_OK;
	for(int i =0;i<lObjectCount;i++){
		printf("Event occurred!\n");
	}
	return WBEM_S_NO_ERROR;


}
HRESULT  EventSink::SetStatus(
			LONG lFlags,
			HRESULT hResult,
			BSTR strParam,
			IWbemClassObject __RPC_FAR *pObjParam
			){
	if(lFlags == WBEM_STATUS_COMPLETE){
		printf("Call complete hResult = 0x%x\n",hResult);
	}
	else if (lFlags == WBEM_STATUS_PROGRESS){
		printf("Call in progress\n");
	}
	return WBEM_S_NO_ERROR;

}

