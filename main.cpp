#include <iostream>
#include <string>

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

static int writer(char *data, size_t size, size_t nmemb,
                  std::string *writerData) {
  if (writerData == NULL)
    return 0;

  writerData->append(data, size * nmemb);

  return size * nmemb;
}

int main(int argc, char *argv[]) {
  if (argc == 0 || argc == 1)
    return 0;

  if (argc >= 2) {

    Site s(URL(0, argv[1], true));

    std::string content;

    CURL *curl = nullptr;
    curl = curl_easy_init();
    if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, s.getURL());
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s.data);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
      CURLcode code = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
    }

    std::cout << s.data;

    s.search_for_inner_urls();

    std::cin.get();
    return 0;
  }
}