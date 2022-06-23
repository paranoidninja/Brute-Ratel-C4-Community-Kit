#include <windows.h>
#include "badger_exports.h"

DECLSPEC_IMPORT BOOL Kernel32$MoveFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName);
DECLSPEC_IMPORT DWORD Kernel32$GetLastError();

void coffee(char** argv, int argc, WCHAR** dispatch) {
    if (argc < 2) {
        BadgerDispatch(dispatch, "[+] Need atleast 2 arguments\n");
    }
    BadgerDispatch(dispatch, "[+] Renaming file: %s => %s\n", argv[0], argv[1]);
    
    if (Kernel32$MoveFileA(argv[0], argv[1])) {
        BadgerDispatch(dispatch, "[+] File Moved\n");
    } else {
        BadgerDispatch(dispatch, "[-] Error: %lu\n", Kernel32$GetLastError());
    }
}