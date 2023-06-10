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
	EXECUTABLE := .exe
	LTO :=  
	DLL_LIB := -lws2_32
	ifeq ($(BUILD_TYPE),debug)
		STRIP := REM
	endif

else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
	SHARED_EXTENSION := dyn
	EXECUTABLE := .app
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

WEBUI-SHARED := $(OUTDIR)/webui-$(VERSION)-x$(BIT).$(SHARED_EXTENSION)
WEBUI-STATIC := $(OUTDIR)/libwebui-$(VERSION)-static-x$(BIT).a

all: $(WEBUI-SHARED) $(WEBUI-STATIC)

folder:
	mkdir -p $(OUTDIR)
	mkdir -p $(OUTDIR)/examples

$(OUTDIR)/civetweb-%.o: src/civetweb/civetweb.c | folder
	$(CC) -c $< -o $@ -DNDEBUG -DNO_CACHING -DNO_CGI -DNO_SSL -DUSE_WEBSOCKET $(CFLAGS) $(LTO) -$(subst $(OUTDIR)/civetweb-,,$*) 

$(WEBUI-STATIC): src/webui.c include/webui.h $(OUTDIR)/civetweb-Os.o 
	$(CC) -c src/webui.c -o $(OUTDIR)/static-webui.o -Iinclude $(CFLAGS) $(LTO) $(Os)
	$(AR) rc $@ $(OUTDIR)/static-webui.o $(OUTDIR)/civetweb-Os.o
	$(RAN) $@

$(WEBUI-SHARED): src/webui.c include/webui.h $(OUTDIR)/civetweb-O3.o
	$(CC) -c src/webui.c -o $(OUTDIR)/shared-webui.o -Iinclude $(CFLAGS) $(LTO) $(O3)
	$(CC) -shared -o $@ $(OUTDIR)/shared-webui.o $(OUTDIR)/civetweb-O3.o $(LTO) $(DLL_LIB)
	$(STRIP) --strip-unneeded $@

CEXAMPLE_DIRS := call_c_from_js call_js_from_c minimal serve_a_folder
CEXAMPLE_BINS := $(patsubst %,$(OUTDIR)/examples/C/%/$(notdir $(EXECUTABLE)),$(CEXAMPLE_DIRS))

$(OUTDIR)/examples/C/%/$(notdir $(EXECUTABLE)): $(WEBUI-STATIC)
	mkdir -p $(OUTDIR)/examples/C/$*
	cp -r examples/C/$*/* $(OUTDIR)/examples/C/$*
	$(CC) $(OUTDIR)/examples/C/$*/main.c -o $@/$*$(EXECUTABLE) -Iinclude $(CFLAGS) $(LTO) $(Os) $(WEBUI-STATIC)
	rm $(OUTDIR)/examples/C/$*/main.c

C++EXAMPLE_DIRS := call_cpp_from_js call_js_from_cpp minimal serve_a_folder
C++EXAMPLE_BINS := $(patsubst %,$(OUTDIR)/examples/C++/%/$(notdir $(EXECUTABLE)),$(C++EXAMPLE_DIRS))

$(OUTDIR)/examples/C++/%/$(notdir $(EXECUTABLE)): $(WEBUI-STATIC)
	mkdir -p $(OUTDIR)/examples/C++/$*
	cp -r examples/C++/$*/* $(OUTDIR)/examples/C++/$*
	$(CXX) $(OUTDIR)/examples/C++/$*/main.cpp -o $@/$*$(EXECUTABLE) -Iinclude $(CXXFLAGS) $(LTO) $(Os) $(WEBUI-STATIC) -std=c++17
	rm $(OUTDIR)/examples/C++/$*/main.cpp

examples: $(CEXAMPLE_BINS) $(C++EXAMPLE_BINS)

.PHONY: clear
clear:
	rm -rf $(OUTDIR)
