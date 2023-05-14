# WebUI Library
# Windows - Microsoft Visual C

all: release

debug:
#	TLS Dynamic with Debug info
	@echo Build WebUI Library (TLS MSVC Debug Dynamic)...
	@cl /Zi /Focivetweb.obj /c /MD /EHsc "../../../src/civetweb/civetweb.c" /I "../../../src/civetweb/" /I "../../../src/openssl/include" -DNDEBUG -DNO_CACHING -DNO_CGI -DNO_SSL_DL -DOPENSSL_API_1_1 -DUSE_WEBSOCKET
	@cl /Zi /Fowebui.obj /c /MD /EHsc /DWEBUI_LOG "../../../src/webui.c" /I "../../../include" /I "../../../src/" /I "../../../src/openssl/include" -DWEBUI_SSL
	@link /DLL /OUT:webui-2-x64.dll webui.obj civetweb.obj user32.lib Advapi32.lib crypt32.lib /LIBPATH:"../../../src/openssl/lib" libssl.lib libcrypto.lib
#	Clean
	@- del *.obj >nul 2>&1
	@echo Done.

release:
#	TLS Dynamic Release
	@echo Build WebUI Library (TLS MSVC Release Dynamic)...
	@cl /Focivetweb.obj /c /MD /EHsc "../../../src/civetweb/civetweb.c" /I "../../../src/civetweb/" /I "../../../src/openssl/include" -DNDEBUG -DNO_CACHING -DNO_CGI -DNO_SSL_DL -DOPENSSL_API_1_1 -DUSE_WEBSOCKET 1>NUL 2>&1
	@cl /Fowebui.obj /c /MD /EHsc "../../../src/webui.c" /I "../../../include" /I "../../../src/" /I "../../../src/openssl/include" -DWEBUI_SSL 1>NUL 2>&1
	@link /DLL /OUT:webui-2-x64.dll webui.obj civetweb.obj user32.lib Advapi32.lib crypt32.lib /LIBPATH:"../../../src/openssl/lib" libssl.lib libcrypto.lib 1>NUL 2>&1
#	Clean
	@- del *.obj >nul 2>&1
	@- del *.ilk >nul 2>&1
	@- del *.pdb >nul 2>&1
	@- del *.exp >nul 2>&1
	@echo Done.

clean:
	- del *.obj >nul 2>&1
	- del *.dll >nul 2>&1
	- del *.ilk >nul 2>&1
	- del *.pdb >nul 2>&1
	- del *.lib >nul 2>&1
	- del *.exp >nul 2>&1
