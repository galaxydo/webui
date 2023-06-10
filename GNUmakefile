BIT ?= 64
CFLAGS ?= -fPIC -m$(BIT)
VERSION ?= 2
OUTDIR ?= build

ifeq ($(CC),clang)
	LTO := -flto=full
	RAN := ranlib
endif
LTO ?= -flto=auto

ifeq ($(OS),Windows_NT)
	CC := gcc
	AR := ar
	SHARED_EXTENSION := dll
	LTO :=  
	DLL_LIB := -lws2_32
	ifeq ($(BUILD_TYPE),debug)
		STRIP := REM
	endif

else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
	SHARED_EXTENSION := dyn
	STRIP := \#
	RAN := ranlib
    endif
endif

RAN ?= gcc-ranlib
SHARED_EXTENSION ?= so

ifeq ($(BUILD_TYPE),debug)
	O3 := -Og -g
	Os := -Og -g
	STRIP ?= \#
endif

O3 ?= -O3
Os ?= -Os
STRIP ?= strip

all: $(OUTDIR)/libwebui-$(VERSION)-static-x$(BIT).a $(OUTDIR)/webui-$(VERSION)-x$(BIT).$(SHARED_EXTENSION)

folder:
	mkdir -p $(OUTDIR)

$(OUTDIR)/civetweb-%.o: src/civetweb/civetweb.c | folder
	$(CC) -c $< -o $@ -DNDEBUG -DNO_CACHING -DNO_CGI -DNO_SSL -DUSE_WEBSOCKET $(CFLAGS) $(LTO) -$(subst $(OUTDIR)/civetweb-,,$*) 

$(OUTDIR)/libwebui-$(VERSION)-static-x$(BIT).a: src/webui.c include/webui.h $(OUTDIR)/civetweb-Os.o 
	$(CC) -c src/webui.c -o $(OUTDIR)/static-webui.o -Iinclude $(CFLAGS) $(LTO) $(Os)
	$(AR) rc $@ $(OUTDIR)/static-webui.o $(OUTDIR)/civetweb-Os.o
	$(RAN) $@

$(OUTDIR)/webui-$(VERSION)-x$(BIT).$(SHARED_EXTENSION): src/webui.c include/webui.h $(OUTDIR)/civetweb-O3.o
	$(CC) -c src/webui.c -o $(OUTDIR)/shared-webui.o -Iinclude $(CFLAGS) $(LTO) $(O3)
	$(CC) -shared -o $@ $(OUTDIR)/shared-webui.o $(OUTDIR)/civetweb-O3.o $(LTO) $(DLL_LIB)
	$(STRIP) --strip-unneeded $@

.PHONY: clear
clear:
	rm -rf $(OUTDIR)
