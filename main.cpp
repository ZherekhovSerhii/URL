#include <iostream>
#include <set>
#include <string>
#include <vector>

#define CURL_STATICLIB
#include "nlohmann\json.hpp"

#ifdef _DEBUG
#pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment(lib, "curl/libcurl_a.lib")
#endif

#include "Parser.hpp"
#include "curl\curl.h"

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "To start parcing write the URL after the name of programm"
              << std::endl;
    return 0;
  }

  if (argc >= 2) {

    Parser p;
    p.init(argv[1]);
    p.parsing();

    std::cin.get();

    return 0;
  }
}