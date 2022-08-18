all:
	make exe
	make dll

exe:
	x86_64-w64-mingw32-gcc shellcode.c -o shellcode.exe -lntdll -s

dll:
	x86_64-w64-mingw32-gcc shellcode.c -o shellcode.dll -lntdll -s -DBUILD_DLL -shared

clean:
	rm -rf *.exe *.dll *.bin