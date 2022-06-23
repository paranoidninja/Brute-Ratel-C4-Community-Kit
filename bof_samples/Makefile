64:
	x86_64-w64-mingw32-gcc decltest.c -c -o decltest64.o -m64
	x86_64-w64-mingw32-gcc getdc.c -c -o getdc64.o -m64

86:
	i686-w64-mingw32-gcc decltest.c -c -o decltest86.o -m32
	i686-w64-mingw32-gcc getdc.c -c -o getdc86.o -m32

both:
	make 86
	make 64