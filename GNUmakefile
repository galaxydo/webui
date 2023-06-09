BIT ?= 64
CFLAGS ?= -fPIC -m$(BIT)

ifeq ($(CC),clang)
	LTO := -flto=full
endif
LTO ?= -flto

ifeq ($(OS),Windows_NT)
	CC := gcc
	AR := ar
	SHARED_EXTENSION := dll
	LTO :=  
	ifeq ($(BUILD_TYPE),debug)
		STRIP := REM
	endif

else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
	SHARED_EXTENSION := dyn
	STRIP := \#
    endif
endif

SHARED_EXTENSION ?= so

ifeq ($(BUILD_TYPE),debug)
	O3 := -Og -g
	Os := -Og -g
	STRIP ?= \#
endif

O3 ?= -O3
Os ?= -Os
STRIP ?= strip

all: webui-shared webui-static

.PHONY: folders
folders:
	mkdir -p build

webui-static: src/webui.c include/webui.h src/civetweb/civetweb.c folders
	$(CC) -c src/civetweb/civetweb.c -o build/static-civetweb.o -DNDEBUG -DNO_CACHING -DNO_CGI -DNO_SSL -DUSE_WEBSOCKET $(CFLAGS) $(LTO) $(Os)
	$(CC) -c src/webui.c -o build/static-webui.o -Iinclude $(CFLAGS) $(LTO) $(Os)
	$(AR) rc build/libwebui-2-static-x$(BIT).a build/static-webui.o build/static-civetweb.o
	ranlib build/libwebui-2-static-x$(BIT).a
	$(STRIP) --strip-unneeded build/libwebui-2-static-x$(BIT).a
	rm build/static-*.o

webui-shared: src/webui.c include/webui.h src/civetweb/civetweb.c folders
	$(CC) -c src/civetweb/civetweb.c -o build/shared-civetweb.o -DNDEBUG -DNO_CACHING -DNO_CGI -DNO_SSL -DUSE_WEBSOCKET $(CFLAGS) $(LTO) $(O3)
	$(CC) -c src/webui.c -o build/shared-webui.o -Iinclude $(CFLAGS) $(LTO) $(O3)
	$(CC) -shared -o build/webui-2-x$(BIT).$(SHARED_EXTENSION) build/shared-webui.o build/shared-civetweb.o $(LTO)
	$(STRIP) --strip-unneeded build/webui-2-x$(BIT).$(SHARED_EXTENSION)
	rm build/shared-*.o

.PHONY: clear
clear:
	rm -rf build
