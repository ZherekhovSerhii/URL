#include "Parser.hpp"
#include <iostream>
#include <string>
#include <vector>

#define CURL_STATICLIB
#include "curl\curl.h"
#include "nlohmann\json.hpp"

#ifdef _DEBUG
#pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment(lib, "curl/libcurl_a.lib")
#endif

static int get_content(char *data, size_t size, size_t nmemb,
                       std::string *writerData) {
  if (writerData == NULL)
    return 0;

  writerData->append(data, size * nmemb);

  return size * nmemb;
}

void parsing(const char *url) {
  Parser p;
  CURL *curl = nullptr;
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &p.data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_content);
    CURLcode code = curl_easy_perform(curl);
    if (code != CURLcode::CURLE_OK) {
      std::cout << "\nCURL_EASY_PERFORM ERROR\n";
    }
    curl_easy_cleanup(curl);
  }
  p.parsing();
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "To start parcing write the URL after the name of programm"
              << std::endl;
    return 0;
  }

  if (argc >= 2) {

    parsing(argv[1]);

    std::cin.get();

    return 0;
  }
}