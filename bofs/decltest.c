#include <windows.h>
#include <stdio.h>
#include "badger_exports.h"

WINADVAPI WINBOOL WINAPI Advapi32$GetUserNameA(LPSTR lpBuffer, LPDWORD pcbBuffer);
WINADVAPI WINBOOL WINAPI Advapi32$GetUserNameW(LPWSTR lpBuffer, LPDWORD pcbBuffer);
WINBASEAPI int Msvcrt$printf(const char *__format, ...);
WINBASEAPI int Msvcrt$wprintf(const WCHAR *__format, ...);

void coffee(char** argv, int argc, WCHAR** dispatch) {
    CHAR username[MAX_PATH] = { 0 };
    DWORD usernameLength = MAX_PATH;
	Advapi32$GetUserNameA(username, &usernameLength);
    BadgerDispatch(dispatch, "[+] Char Username: %s\n", username);

    int usernamelen = BadgerStrlen(username);
    BadgerDispatch(dispatch, "[+] Username length: %d\n", usernamelen);

    if (argc > 0) {
    int retval = BadgerStrcmp(argv[0], username);
    if (retval) {
        BadgerDispatch(dispatch, "[+] Unequal values: %s\n", argv[0]);
    } else {
        BadgerDispatch(dispatch, "[+] Equal values: %s\n", argv[0]);
    }
    } else {
        BadgerDispatch(dispatch, "[+] No Args provided\n");
    }


    WCHAR usernameW[MAX_PATH] = { 0 };
    usernameLength = MAX_PATH;
	Advapi32$GetUserNameW(usernameW, &usernameLength);
    BadgerDispatchW(dispatch, L"[+] Wchar Username: %ls\n", usernameW);

    int usernamelenW = BadgerWcslen(usernameW);
    BadgerDispatchW(dispatch, L"[+] UsernameW length: %d\n", usernamelenW);

    WCHAR testW[] = L"somevalue\0";

    int retval = BadgerWcscmp(testW, usernameW);
    if (retval) {
        BadgerDispatchW(dispatch, L"[+] Unequal widechar strings\n");
    } else {
        BadgerDispatchW(dispatch, L"[+] Equal widechar strings\n");
    }

    char *intstr = "10";
    int converted = BadgerAtoi(intstr);
    BadgerDispatch(dispatch, "[+] Atoi: %d\n", converted);

    BadgerMemset(testW, 0, sizeof(testW));
    if (BadgerWcslen(testW) == 0) {
        BadgerDispatch(dispatch, "[+] Memset complete\n");
    }

    BadgerDispatch(dispatch, "[+] All Arguments:\n");
    for (int i = 0; i < argc; i++) {
        BadgerDispatch(dispatch, "  - arg[%d]: %s\n", i, argv[i]);
    }

    char* someBuffer = BadgerAlloc(20);
    if (someBuffer) {
        BadgerMemcpy(someBuffer, "[+] working\n", 12);
        BadgerDispatch(dispatch, "%s", someBuffer);
    }
    BadgerFree((PVOID*)&someBuffer);

    if (BadgerSetdebug()) {
        BadgerDispatch(dispatch, "[+] SeDebug Set:\n");
    }
}
