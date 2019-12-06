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

#include "Site.hpp"
#include "URL.hpp"
#include "URL_TYPE.hpp"

static int get_content(char *data, size_t size, size_t nmemb,
                       std::string *writerData) {
  if (writerData == NULL)
    return 0;

  writerData->append(data, size * nmemb);

  return size * nmemb;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "To start parcing write the URL after the name of programm"
              << std::endl;
    return 0;
  }

  if (argc >= 2) {

    Site s(URL(0, argv[1], URL_TYPE::HTTPS));

    std::string content;

    CURL *curl = nullptr;
    curl = curl_easy_init();
    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, s.getURL());
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s.data);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_content);
      CURLcode code = curl_easy_perform(curl);
      if (code != CURLcode::CURLE_OK) {
        std::cout << "\nCURL_EASY_PERFORM ERROR\n";
      }
      curl_easy_cleanup(curl);
    }

    s.search_for_inner_urls();
    s.print_inner_urls();

    std::cin.get();
    return 0;
  }
}