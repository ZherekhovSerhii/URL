#include<iostream>
#include<string>
#include<regex>
#include<vector>
#include"URL_TYPE.hpp"
#include "URL.hpp"
#include "Site.hpp"

Site::Site(URL U) : url{U} {}

Site::~Site() {
  for (URL *url : storage)
    delete url;
}

const char *Site::getURL() { return url.getAddress(); }

void Site::search_for_inner_urls() { parcing(data.c_str()); }

void Site::print_inner_urls() {
  for (URL *url : storage) {
    url->print();
  }
}

//////private:

URL_TYPE Site::check_url_type(const char *s) {
  if (*(s) == 'h' && *(s + 1) == 't' && *(s + 2) == 't' && *(s + 3) == 'p') {
    if (*(s + 4) == ':' && *(s + 5) == '/' && *(s + 6) == '/')
      return URL_TYPE::HTTP;

    if (*(s + 4) == 's' && *(s + 5) == ':' && *(s + 6) == '/' &&
        *(s + 7) == '/')
      return URL_TYPE::HTTPS;
  } else
    return URL_TYPE::NO;
}

const char *Site::search_for_end_of_url(const char *s) {
  for (size_t i = 0;; ++i) {
    if (*(s + i) == '?' || *(s + i) == '\"' || *(s + i) == '\'' ||
        *(s + i) == ' ' || *(s + i) == '\0')
      return s + i;
  }
}

void Site::parcing(const char *s) {
  for (size_t i = 0; *(s + i) != '\0'; ++i) {
    URL_TYPE url_type = check_url_type(s + i);

    if (url_type == URL_TYPE::NO)
      continue;

    if (url_type == URL_TYPE::HTTP || url_type == URL_TYPE::HTTPS) {
      const char *begin = (s + i);
      const char *end = search_for_end_of_url(s + i);
      storage.push_back(new URL(0, std::string(begin, end), url_type));
      parcing(end);
      return;
    }
  }
}
