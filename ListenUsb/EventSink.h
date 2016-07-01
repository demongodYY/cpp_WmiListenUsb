#pragma once
#ifndef EVENTSINK_H
#define EVENTSINK_H

#define _WIN32_DCOM

class EventSink:public IWbemObjectSink
{
	LONG m_lRef;
	bool bDone;
public:
	EventSink(void){
		m_lRef = 0;
	};
	~EventSink(void){
		bDone=true;
	};

	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,void** ppv);
	virtual HRESULT STDMETHODCALLTYPE Indicate(
			LONG lObjectCount,
			IWbemClassObject __RPC_FAR *__RPC_FAR *apObjectArray
		);
	virtual HRESULT STDMETHODCALLTYPE SetStatus(
			LONG lFlags,
			HRESULT hResult,
			BSTR strParam,
			IWbemClassObject __RPC_FAR *pObjParam
		);
};

#endif
