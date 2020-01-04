#include <iostream>
#include <regex>
#include <string>
#include <vector>

#define CURL_STATICLIB
#include "nlohmann\json.hpp"

#ifdef _DEBUG
#pragma comment(lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment(lib, "curl/libcurl_a.lib")
#endif

#include "curl\curl.h"
#include "Parser.hpp"

Parser::~Parser() { curl_easy_cleanup(curl); }

static int get_content(char *data, size_t size, size_t nmemb,
                       std::string *writerData) {
  if (writerData == NULL)
    return 0;

  writerData->append(data, size * nmemb);

  return size * nmemb;
}

void Parser::init(std::string url) {
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_content);
    load(url);
  }
}

void Parser::load(std::string url) {
  data.clear();
  std::cout << url << std::endl;
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  code = curl_easy_perform(curl);
  if (code != CURLcode::CURLE_OK) {
    std::cout << "\nCURL_EASY_PERFORM ERROR\n";
  } else {
    loaded_storage.push_back(url);
  }
}

void Parser::parsing() {

  std::smatch m;
  std::regex e(R"((http:\/\/|https:\/\/){1}.[^\" <]*)");

  while (std::regex_search(data, m, e)) {
    const char *begin = m[1].str().c_str();

    if (*(begin + 4) == 's') {
      https_storage.emplace_back(std::string(m[0]));
      std::cout << m[0] << std::endl;
    }
    if (*(begin + 4) == ':') {
      http_storage.emplace_back(std::string(m[0]));
      std::cout << m[0] << std::endl;
    }
    data = m.suffix().str();
  }

  for (auto url : https_storage) {
    if (std::none_of(loaded_storage.begin(), loaded_storage.end(),
                     [&url](const std::string &str) {
                       return strcmp(url.c_str(), str.c_str()) == 0;
                     })) {
      load(url);
      parsing();
    }
  }
}