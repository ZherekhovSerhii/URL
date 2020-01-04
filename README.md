url_parser 

uses curl-7.67.0

include:
curl.h
curlver.h
easy.h
mprintf.h
multi.h
stdcheaders.h
system.h
typecheck-gcc.h
urlapi.h

lib:
libcurl_a_debug.lib

additional dependencies:
Normaliz.lib;
Ws2_32.lib;
Wldap32.lib;
Crypt32.lib;
advapi32.lib;
