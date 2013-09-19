CPP_FLAGS= -std=c++11

all:
	clang++ ${CPP_FLAGS} main.cpp

check-syntax:
	clang++ ${CPP_FLAGS} -fsyntax-only -fno-color-diagnostics ${CHK_SOURCES}

print-cflags:
	echo ${CPP_FLAGS}
