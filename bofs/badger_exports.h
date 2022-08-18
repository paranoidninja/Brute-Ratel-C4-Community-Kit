#include <windows.h>

void coffee(char** argv, int argc, WCHAR** dispatch);
DECLSPEC_IMPORT int BadgerDispatch(WCHAR** dispatch, const char *__format, ...);
DECLSPEC_IMPORT int BadgerDispatchW(WCHAR** dispatch, const WCHAR*__format, ...);
DECLSPEC_IMPORT size_t BadgerStrlen(CHAR* buf);
DECLSPEC_IMPORT size_t BadgerWcslen(WCHAR* buf);
DECLSPEC_IMPORT void *BadgerMemcpy(void *dest, const void *src, size_t len) ;
DECLSPEC_IMPORT void *BadgerMemset(void *dest, int val, size_t len);
DECLSPEC_IMPORT int BadgerStrcmp(const char *p1, const char *p2);
DECLSPEC_IMPORT int BadgerWcscmp(const wchar_t *s1, const wchar_t *s2);
DECLSPEC_IMPORT int BadgerAtoi(char* string);
DECLSPEC_IMPORT PVOID BadgerAlloc(SIZE_T length);
DECLSPEC_IMPORT VOID BadgerFree(PVOID *memptr);
DECLSPEC_IMPORT BOOL BadgerSetdebug();
DECLSPEC_IMPORT ULONG BadgerGetBufferSize(PVOID buffer);